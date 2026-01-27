#include "args.h"
#include "md5.h"
#include "pass.h"
#include "utils.h"
#include <cstdio>
#include <time.h>

char *get_all_chars(int pass_type, int *len, FILE *output_file) {
  static char *chars = (char *)malloc(95);
  fprintf(output_file, "Generating character set for pass_type: %d\n",
          pass_type);
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
               int all_chars_size, char *all_chars, FILE *output_file,
               bool benchmark) {
  int base = all_chars_size;
  int indices[pass_length];
  char buffer[pass_length + 1];
  unsigned long long hash_count = 0;
  clock_t start, end;

  memset(indices, 0, sizeof(indices));
  buffer[pass_length] = '\0';

  if (benchmark)
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
      fprintf(output_file, "Password found: %s\n", buffer);

      if (benchmark) {
        end = clock();
        fprintf(output_file, "Time taken: %.2f seconds\n",
                ((double)(end - start)) / CLOCKS_PER_SEC);
        fprintf(output_file, "Speed: %.2f million hashes/second\n",
                hash_count / (((double)(end - start)) / CLOCKS_PER_SEC) /
                    1e6);
      }

      printf("%d; %.6f; %.6f\n", pass_length,
             ((double)(end - start)) / CLOCKS_PER_SEC,
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
  if (benchmark) {
    end = clock();
    fprintf(output_file, "Time taken: %.2f seconds\n",
            ((double)(end - start)) / CLOCKS_PER_SEC);
    fprintf(output_file, "Speed: %.2f million hashes/second\n",
            hash_count / (((double)(end - start)) / CLOCKS_PER_SEC) / 1e6);
    printf("%d; %.6f; %.6f\n", pass_length,
           ((double)(end - start)) / CLOCKS_PER_SEC,
           hash_count / (((double)(end - start)) / CLOCKS_PER_SEC) / 1e6);
  }
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

unsigned long long crack_len_gpu(struct md5_state *target_hash_d,
                                 int pass_length, int all_chars_size,
                                 char *all_chars_d, FILE *output_file,
                                 bool benchmark) {
  int base = all_chars_size;

  cudaDeviceProp prop;
  cudaGetDeviceProperties(&prop, 0);
  const int threadCount = 256;
  const int blockCount = prop.multiProcessorCount * 256;

  const int CHECK_EVERY = 128;

  cudaStream_t stream;
  cudaStreamCreate(&stream);

  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  float elapsedTime;

  unsigned long long all_combinations = base;
  for (int i = 1; i < pass_length; i++) {
    all_combinations *= base;
  }

  unsigned long long *result_d;
  cudaMalloc((void **)&result_d, sizeof(unsigned long long));
  cudaMemsetAsync(result_d, 0, sizeof(unsigned long long), stream);

  unsigned long long result_h = 0;

  if (benchmark)
    cudaEventRecord(start, stream);

  const unsigned long long stride =
      (unsigned long long)blockCount * threadCount;

  int launch_count = 0;
  for (unsigned long long offset = 0; offset < all_combinations;
       offset += stride) {

    md5_passwd_gpu<<<blockCount, threadCount, 0, stream>>>(
        all_chars_d, base, pass_length, offset, target_hash_d, result_d);

    launch_count++;

    if (launch_count % CHECK_EVERY == 0) {
      cudaMemcpyAsync(&result_h, result_d, sizeof(unsigned long long),
                      cudaMemcpyDeviceToHost, stream);
      cudaStreamSynchronize(stream);

      if (result_h > 0) {
        if (benchmark) {
          cudaEventRecord(stop, stream);
          cudaEventSynchronize(stop);
          cudaEventElapsedTime(&elapsedTime, start, stop);
          printf("%d; %.6f; %.6f\n", pass_length, elapsedTime / 1000.0,
                 result_h / (elapsedTime / 1000.0) / 1e6);
          fprintf(output_file, "Time taken: %.2f seconds\n",
                  elapsedTime / 1000.0);
          fprintf(output_file, "Speed: %.2f million hashes/second\n\n",
                  result_h / (elapsedTime / 1000.0) / 1e6);
        }

        cudaFree(result_d);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
        cudaStreamDestroy(stream);
        return result_h;
      }
    }
  }

  // Final check
  cudaMemcpyAsync(&result_h, result_d, sizeof(unsigned long long),
                  cudaMemcpyDeviceToHost, stream);
  cudaStreamSynchronize(stream);

  if (benchmark) {
    cudaEventRecord(stop, stream);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTime, start, stop);
    printf("%d; %.6f; %.6f\n", pass_length, elapsedTime / 1000.0,
           all_combinations / (elapsedTime / 1000.0) / 1e6);
    fprintf(output_file, "Time taken: %.2f seconds\n",
            elapsedTime / 1000.0);
    fprintf(output_file, "Speed: %.2f million hashes/second\n\n",
            all_combinations / (elapsedTime / 1000.0) / 1e6);
  }

  cudaFree(result_d);
  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  cudaStreamDestroy(stream);

  return 0;
}

void crack_gpu(FILE *input_file, FILE *output_file, int pass_length,
               int pass_type, bool benchmark) {
  struct md5_state target_hash_h = get_hash_from_file(input_file);

  int all_chars_size;
  char *all_chars_h =
      get_all_chars(pass_type, &all_chars_size, output_file);

  char *all_chars_d;
  cudaMalloc((void **)&all_chars_d, all_chars_size);
  cudaMemcpy(all_chars_d, all_chars_h, all_chars_size,
             cudaMemcpyHostToDevice);

  struct md5_state *target_hash_d;
  cudaMalloc((void **)&target_hash_d, sizeof(struct md5_state));
  cudaMemcpy(target_hash_d, &target_hash_h, sizeof(struct md5_state),
             cudaMemcpyHostToDevice);

  for (int len = 1; len <= pass_length; len++) {
    if (pow(all_chars_size, len) < 1) {
      fprintf(output_file, "Cracking passwords of length %d...\n", len);
      if (crack_len(target_hash_h, len, all_chars_size, all_chars_h,
                    output_file, benchmark)) {
        return;
      }
    } else {
      fprintf(output_file, "Cracking passwords of length %d on GPU...\n",
              len);
      unsigned long long found =
          crack_len_gpu(target_hash_d, len, all_chars_size, all_chars_d,
                        output_file, benchmark);
      if (found > 0) {
        char passwd[len + 1];
        int_to_passwd(found - 1, len, all_chars_size, all_chars_h, passwd);
        fprintf(output_file, "Password found %s\n", passwd);
        break;
      }
    }
  }

  cudaFree(target_hash_d);
  cudaFree(all_chars_d);
}

void crack(FILE *input_file, FILE *output_file, int pass_length,
           int pass_type, bool benchmark) {
  struct md5_state target_hash = get_hash_from_file(input_file);
  int all_chars_size;
  char *all_chars = get_all_chars(pass_type, &all_chars_size, output_file);

  for (int len = 1; len <= pass_length; len++) {
    fprintf(output_file, "\nCracking passwords of length %d...\n", len);
    if (crack_len(target_hash, len, all_chars_size, all_chars, output_file,
                  benchmark)) {
      return;
    }
  }

  fprintf(output_file, "Password not found.\n");
}

void crack_device(FILE *input_file, FILE *output_file, int pass_length,
                  int pass_type, DeviceType device, bool benchmark) {
  if (device == CPU) {
    crack(input_file, output_file, pass_length, pass_type, benchmark);
  } else {
    crack_gpu(input_file, output_file, pass_length, pass_type, benchmark);
  }
}
