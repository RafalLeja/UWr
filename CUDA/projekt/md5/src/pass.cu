#include "md5.h"
#include "pass.h"
#include "utils.h"
#include <cstdio>

char *get_all_chars(int pass_type, int *len) {
  static char *chars = (char *)malloc(95);
  printf("Generating character set for pass_type: %d\n", pass_type);
  int index = 0;
  if (pass_type & 0x1) {
    for (char c = '0'; c <= '9'; c++) {
      chars[index++] = c;
    }
  }
  if (pass_type & 0x2) {
    for (char c = 'a'; c <= 'z'; c++) {
      chars[index++] = c;
    }
  }
  if (pass_type & 0x4) {
    for (char c = 'A'; c <= 'Z'; c++) {
      chars[index++] = c;
    }
  }
  if (pass_type & 0x8) {
    char special_chars[] = {'!', '"', '#', '$', '%', '&', '\'', '(',
                            ')', '*', '+', ',', '-', '.', '/',  ';',
                            ':', '<', '=', '>', '?', '@', '[',  '\\',
                            ']', '^', '_', '`', '{', '|', '}',  '~'};
    for (int i = 0; i < sizeof(special_chars); i++) {
      chars[index++] = special_chars[i];
    }
  }

  chars[index] = '\0';
  *len = index;
  return chars;
}

bool crack_len(struct md5_state target_hash, int pass_length,
               int all_chars_size, char *all_chars) {
  int base = all_chars_size;
  int indices[pass_length];
  char buffer[pass_length + 1];

  memset(indices, 0, sizeof(indices));
  buffer[pass_length] = '\0';

  while (1) {
    for (int i = 0; i < pass_length; i++) {
      buffer[i] = all_chars[indices[i]];
    }

    struct md5_state current_hash = md5_passwd(buffer, strlen(buffer));
    if (current_hash.a == target_hash.a &&
        current_hash.b == target_hash.b &&
        current_hash.c == target_hash.c &&
        current_hash.d == target_hash.d) {
      printf("Password found: %s\n", buffer);
      return true;
    }

    int pos = pass_length - 1;
    while (pos >= 0) {
      indices[pos]++;
      if (indices[pos] < base) {
        break;
      } else {
        indices[pos] = 0;
        pos--;
      }
    }
    if (pos < 0) {
      break;
    }
  }
  return false;
}

bool crack_len_gpu(struct md5_state target_hash, int pass_length,
                   int all_chars_size, char *all_chars) {
  int base = all_chars_size;
  int indices[pass_length];
  char buffer[pass_length + 1];
  const int blockSize = 1024;
  const int threadCount = 1024;
  int batch = 0;
  int passIdx = 0;
  bool last_batch = false;

  // GPU memory allocation
  char *passwd_h = (char *)malloc(pass_length * threadCount * blockSize);
  if (passwd_h == NULL) {
    fprintf(stderr, "Failed to allocate host memory for passwords.\n");
    return false;
  }
  char *passwd_d;
  cudaMalloc((void **)&passwd_d, pass_length * threadCount * blockSize);

  struct md5_state *target_hash_d;
  cudaMalloc((void **)&target_hash_d, sizeof(struct md5_state));
  cudaMemcpy(target_hash_d, &target_hash, sizeof(struct md5_state),
             cudaMemcpyHostToDevice);

  int *result_d;
  cudaMalloc((void **)&result_d, sizeof(int));
  cudaMemset(result_d, 0, sizeof(int));

  memset(indices, 0, sizeof(indices));
  memset(buffer, 0, sizeof(buffer));

  while (1) {
    for (int i = 0; i < pass_length; i++) {
      passwd_h[(passIdx * pass_length) + i] = all_chars[indices[i]];
    }
    // printf("passIdx: %d\n", passIdx);

    if (passIdx + 1 == blockSize * threadCount || last_batch) {
      batch++;
      // printf("Launching GPU kernel for batch %d\n", batch);
      cudaMemcpy(passwd_d, passwd_h, pass_length * threadCount * blockSize,
                 cudaMemcpyHostToDevice);
      md5_passwd_gpu<<<blockSize, threadCount>>>(passwd_d, pass_length,
                                                 target_hash_d, result_d);
      cudaDeviceSynchronize();
      int result_h;
      cudaMemcpy(&result_h, result_d, sizeof(int), cudaMemcpyDeviceToHost);
      if (result_h > 0) {
        printf("Password found in GPU batch %d.\n", batch);
        for (int j = 0; j < pass_length; j++) {
          buffer[j] = passwd_h[(result_h - 1) * pass_length + j];
        }
        printf("Password: %s", buffer);
        cudaFree(passwd_d);
        cudaFree(target_hash_d);
        cudaFree(result_d);
        free(passwd_h);
        return true;
      }
      if (last_batch) {
        break;
      }
      passIdx = 0;
    }

    int pos = pass_length - 1;
    while (pos >= 0) {
      indices[pos]++;
      if (indices[pos] < base) {
        break;
      } else {
        indices[pos] = 0;
        pos--;
      }
    }
    if (pos < 0) {
      // printf("Completed all combinations for length %d.\n",
      // pass_length);
      last_batch = true;
      // break;
    }
    passIdx += 1;
  }
  return false;
}

void crack_gpu(FILE *input_file, FILE *output_file, int pass_length,
               int pass_type, float *time) {
  struct md5_state target_hash = get_hash_from_file(input_file);
  int all_chars_size;
  char *all_chars = get_all_chars(pass_type, &all_chars_size);
  for (int len = 1; len <= 5; len++) {
    printf("Cracking passwords of length %d...\n", len);
    if (crack_len(target_hash, len, all_chars_size, all_chars)) {
      return;
    }
  }

  for (int len = 6; len <= pass_length; len++) {
    printf("Cracking passwords of length %d on GPU...\n", len);
    if (crack_len_gpu(target_hash, len, all_chars_size, all_chars)) {
      return;
    }
  }

  // char passwd_h[] = "abc";
  // char *passwd_d;
  // int result_h;
  // int *result_d;
  // struct md5_state *target_hash_d;
  // cudaMalloc((void **)&target_hash_d, sizeof(struct md5_state));
  // cudaMalloc((void **)&result_d, sizeof(int));
  // cudaMalloc((void **)&passwd_d, pass_length + 1);
  // cudaMemcpy(target_hash_d, &target_hash, sizeof(struct md5_state),
  //            cudaMemcpyHostToDevice);
  // cudaMemcpy(passwd_d, passwd_h, pass_length + 1,
  // cudaMemcpyHostToDevice);
  //
  // md5_passwd_gpu<<<1, 1>>>(passwd_d, pass_length, target_hash_d,
  // result_d);
  //
  // cudaDeviceSynchronize();
  // cudaMemcpy(&result_h, result_d, sizeof(int), cudaMemcpyDeviceToHost);
  // printf("Result: %d\n", result_h);
}

void crack(FILE *input_file, FILE *output_file, int pass_length,
           int pass_type, float *time) {
  struct md5_state target_hash = get_hash_from_file(input_file);
  int all_chars_size;
  char *all_chars = get_all_chars(pass_type, &all_chars_size);

  for (int len = 1; len <= pass_length; len++) {
    printf("Cracking passwords of length %d...\n", len);
    if (crack_len(target_hash, len, all_chars_size, all_chars)) {
      return;
    }
  }

  printf("Password not found.\n");
}
