#include "md5.h"
#include "pass.h"
#include "utils.h"
#include <cstdio>
#include <time.h>

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
  unsigned long long hash_count = 0;
  clock_t start, end;

  memset(indices, 0, sizeof(indices));
  buffer[pass_length] = '\0';

  start = clock();

  while (1) {
    hash_count++;
    for (int i = 0; i < pass_length; i++) {
      buffer[i] = all_chars[indices[i]];
    }

    struct md5_state current_hash = md5_passwd(buffer, strlen(buffer));
    if (current_hash.a == target_hash.a &&
        current_hash.b == target_hash.b &&
        current_hash.c == target_hash.c &&
        current_hash.d == target_hash.d) {
      end = clock();
      printf("Password found: %s\n", buffer);
      printf("Time taken: %.2f seconds\n",
             ((double)(end - start)) / CLOCKS_PER_SEC);
      printf("Speed: %.2f million hashes/second\n",
             hash_count / (((double)(end - start)) / CLOCKS_PER_SEC) /
                 1e6);
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
  end = clock();
  printf("Time taken: %.2f seconds\n",
         ((double)(end - start)) / CLOCKS_PER_SEC);
  printf("Speed: %.2f million hashes/second\n",
         hash_count / (((double)(end - start)) / CLOCKS_PER_SEC) / 1e6);
  return false;
}

void int_to_passwd(unsigned long long idx, int len, int base,
                   const char *all_chars, char *passwd) {
  for (int i = len - 1; i >= 0; i--) {
    passwd[i] = all_chars[idx % base];
    idx /= base;
  }
  passwd[len] = '\0';
}

bool crack_len_gpu(struct md5_state target_hash, int pass_length,
                   int all_chars_size, char *all_chars) {
  int base = all_chars_size;
  char buffer[pass_length + 1];
  const int blockSize = 1024 * 1024;
  const int threadCount = 1024;
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  float elapsedTime;

  unsigned long long all_combinations = base;
  for (int i = 1; i < pass_length; i++) {
    all_combinations *= base;
  }

  // GPU memory allocation
  char *all_chars_d;
  cudaMalloc((void **)&all_chars_d, all_chars_size);
  cudaMemcpy(all_chars_d, all_chars, all_chars_size,
             cudaMemcpyHostToDevice);

  struct md5_state *target_hash_d;
  cudaMalloc((void **)&target_hash_d, sizeof(struct md5_state));
  cudaMemcpy(target_hash_d, &target_hash, sizeof(struct md5_state),
             cudaMemcpyHostToDevice);

  unsigned long long *result_d;
  cudaMalloc((void **)&result_d, sizeof(unsigned long long));
  cudaMemset(result_d, 0, sizeof(unsigned long long));

  memset(buffer, 0, sizeof(buffer));

  cudaEventRecord(start);

  for (unsigned long long offset = 0; offset < all_combinations;
       offset += blockSize * threadCount) {
    printf("%llu%% combinations tried...\r",
           offset * 100 / all_combinations);
    md5_passwd_gpu<<<blockSize, threadCount>>>(
        all_chars_d, base, pass_length, offset, target_hash_d, result_d);
    cudaDeviceSynchronize();
    unsigned long long result_h;
    cudaMemcpy(&result_h, result_d, sizeof(unsigned long long),
               cudaMemcpyDeviceToHost);
    if (result_h > 0) {
      cudaEventRecord(stop);
      cudaEventSynchronize(stop);
      cudaEventElapsedTime(&elapsedTime, start, stop);

      printf("Password found at index %llu.\n", result_h - 1);
      int_to_passwd(result_h - 1, pass_length, base, all_chars, buffer);
      printf("Password: %s\n", buffer);

      printf("Time taken: %.2f seconds\n", elapsedTime / 1000.0);
      printf("Speed: %.2f million hashes/second\n",
             (result_h) / (elapsedTime / 1000.0) / 1e6);

      cudaFree(all_chars_d);
      cudaFree(target_hash_d);
      cudaFree(result_d);
      cudaEventDestroy(start);
      cudaEventDestroy(stop);
      return true;
    }
  }
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&elapsedTime, start, stop);
  printf("Time taken: %.2f seconds\n", elapsedTime / 1000.0);
  printf("Speed: %.2f million hashes/second\n",
         (all_combinations) / (elapsedTime / 1000.0) / 1e6);

  cudaFree(all_chars_d);
  cudaFree(target_hash_d);
  cudaFree(result_d);
  cudaEventDestroy(start);
  cudaEventDestroy(stop);

  return false;
}

void crack_gpu(FILE *input_file, FILE *output_file, int pass_length,
               int pass_type, float *time) {
  struct md5_state target_hash = get_hash_from_file(input_file);
  int all_chars_size;
  char *all_chars = get_all_chars(pass_type, &all_chars_size);
  for (int len = 1; len <= pass_length; len++) {
    if (pow(all_chars_size, len) < 100000) {
      printf("\nCracking passwords of length %d...\n", len);
      if (crack_len(target_hash, len, all_chars_size, all_chars)) {
        return;
      }
    } else {
      printf("\nCracking passwords of length %d on GPU...\n", len);
      if (crack_len_gpu(target_hash, len, all_chars_size, all_chars)) {
        return;
      }
    }
  }
}

void crack(FILE *input_file, FILE *output_file, int pass_length,
           int pass_type, float *time) {
  struct md5_state target_hash = get_hash_from_file(input_file);
  int all_chars_size;
  char *all_chars = get_all_chars(pass_type, &all_chars_size);

  for (int len = 1; len <= pass_length; len++) {
    printf("\nCracking passwords of length %d...\n", len);
    if (crack_len(target_hash, len, all_chars_size, all_chars)) {
      return;
    }
  }

  printf("Password not found.\n");
}
