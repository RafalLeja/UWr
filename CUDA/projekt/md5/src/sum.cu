#include "md5.h"
#include "sum.h"
#include "utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

void write_hash(struct md5_state state, FILE *output_file) {
  fprintf(
      output_file,
      "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
      state.a & 0xff, (state.a >> 8) & 0xff, (state.a >> 16) & 0xff,
      (state.a >> 24) & 0xff, state.b & 0xff, (state.b >> 8) & 0xff,
      (state.b >> 16) & 0xff, (state.b >> 24) & 0xff, state.c & 0xff,
      (state.c >> 8) & 0xff, (state.c >> 16) & 0xff,
      (state.c >> 24) & 0xff, state.d & 0xff, (state.d >> 8) & 0xff,
      (state.d >> 16) & 0xff, (state.d >> 24) & 0xff);
}

void benchmark_md5_sum(FILE *input_file, FILE *output_file,
                       int iterations) {
  printf("Benchmarking enabled: %d iterations.\n", iterations);

  float cpu_elapsed_time = 0.0f;
  for (int i = 0; i < iterations; i++) {
    fseek(input_file, 0, SEEK_SET);

    float elapsed_time = 0.0f;
    calculate_md5_sum(input_file, output_file, &elapsed_time);
    cpu_elapsed_time += elapsed_time;

    printf("Iteration %d: Time taken: %.3f seconds\n", i + 1,
           elapsed_time);
  }
  cpu_elapsed_time /= iterations;

  float gpu_elapsed_time = 0.0f;
  for (int i = 0; i < iterations; i++) {
    fseek(input_file, 0, SEEK_SET);

    float elapsed_time = 0.0f;
    calculate_md5_sum_gpu(input_file, output_file, &elapsed_time);
    gpu_elapsed_time += elapsed_time;

    printf("GPU Iteration %d: Time taken: %.3f seconds\n", i + 1,
           elapsed_time);
  }
  gpu_elapsed_time /= iterations;

  printf("\nAverage CPU Time: %.3f seconds\n", cpu_elapsed_time);
  printf("Average GPU Time: %.3f seconds\n", gpu_elapsed_time);
}

void calculate_md5_sum(FILE *input_file, FILE *output_file, float *time) {
  uint64_t file_size = get_file_size(input_file);
  printf("File size: %lu bytes\n", file_size);

  clock_t start, end;
  if (time != NULL) {
    start = clock();
  }

  struct md5_state state = md5_init();
  char buffer[64];
  uint64_t total_bytes_processed = 0;
  int bytes_read;
  while ((bytes_read = fread(buffer, 1, 64, input_file)) == 64) {
    total_bytes_processed += bytes_read;
    uint32_t M[16];

    for (int i = 0; i < 16; i++) {
      M[i] = ((uint32_t)(uint8_t)buffer[i * 4]) |
             (((uint32_t)(uint8_t)buffer[i * 4 + 1]) << 8) |
             (((uint32_t)(uint8_t)buffer[i * 4 + 2]) << 16) |
             (((uint32_t)(uint8_t)buffer[i * 4 + 3]) << 24);
    }

    state = md5_iter(state, M);
  }

  total_bytes_processed += bytes_read;

  char padding[128] = {0};
  int pad_len;
  md5_padding(file_size, padding, &pad_len);

  char final_data[128] = {0};
  int final_data_len = bytes_read + pad_len;

  for (int i = 0; i < bytes_read; i++) {
    final_data[i] = buffer[i];
  }

  for (int i = 0; i < pad_len; i++) {
    final_data[bytes_read + i] = padding[i];
  }

  int blocks_to_process = (final_data_len + 63) / 64;

  for (int block = 0; block < blocks_to_process; block++) {
    uint32_t M[16];

    for (int i = 0; i < 16; i++) {
      int byte_idx = block * 64 + i * 4;
      M[i] = ((uint32_t)(uint8_t)final_data[byte_idx]) |
             (((uint32_t)(uint8_t)final_data[byte_idx + 1]) << 8) |
             (((uint32_t)(uint8_t)final_data[byte_idx + 2]) << 16) |
             (((uint32_t)(uint8_t)final_data[byte_idx + 3]) << 24);
    }

    state = md5_iter(state, M);
  }

  if (time != NULL) {
    end = clock();
    *time = (float)(end - start) / CLOCKS_PER_SEC;
  }

  write_hash(state, output_file);
}

void calculate_md5_sum_gpu(FILE *input_file, FILE *output_file,
                           float *time) {
  uint64_t file_size = get_file_size(input_file);
  printf("File size: %lu bytes\n", file_size);

  cudaEvent_t start, stop;
  if (time != NULL) {
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);
  }

  struct md5_state state = md5_init();
  struct md5_state *state_d;
  cudaMalloc((void **)&state_d, sizeof(struct md5_state));
  cudaMemcpy(state_d, &state, sizeof(struct md5_state),
             cudaMemcpyHostToDevice);
  uint32_t M[16];
  uint32_t *M_d;
  cudaMalloc((void **)&M_d, 16 * sizeof(uint32_t));

  char buffer[64];
  uint64_t total_bytes_processed = 0;
  int bytes_read;
  while ((bytes_read = fread(buffer, 1, 64, input_file)) == 64) {
    total_bytes_processed += bytes_read;

    for (int i = 0; i < 16; i++) {
      M[i] = ((uint32_t)(uint8_t)buffer[i * 4]) |
             (((uint32_t)(uint8_t)buffer[i * 4 + 1]) << 8) |
             (((uint32_t)(uint8_t)buffer[i * 4 + 2]) << 16) |
             (((uint32_t)(uint8_t)buffer[i * 4 + 3]) << 24);
    }

    cudaMemcpy(M_d, M, 16 * sizeof(uint32_t), cudaMemcpyHostToDevice);
    // state = md5_iter(state, M);
    md5_iter_gpu<<<1, 1>>>(state_d, M_d);
  }

  total_bytes_processed += bytes_read;

  char padding[128] = {0};
  int pad_len;
  md5_padding(file_size, padding, &pad_len);

  char final_data[128] = {0};
  int final_data_len = bytes_read + pad_len;

  for (int i = 0; i < bytes_read; i++) {
    final_data[i] = buffer[i];
  }

  for (int i = 0; i < pad_len; i++) {
    final_data[bytes_read + i] = padding[i];
  }

  int blocks_to_process = (final_data_len + 63) / 64;

  for (int block = 0; block < blocks_to_process; block++) {
    uint32_t M[16];

    for (int i = 0; i < 16; i++) {
      int byte_idx = block * 64 + i * 4;
      M[i] = ((uint32_t)(uint8_t)final_data[byte_idx]) |
             (((uint32_t)(uint8_t)final_data[byte_idx + 1]) << 8) |
             (((uint32_t)(uint8_t)final_data[byte_idx + 2]) << 16) |
             (((uint32_t)(uint8_t)final_data[byte_idx + 3]) << 24);
    }

    cudaMemcpy(M_d, M, 16 * sizeof(uint32_t), cudaMemcpyHostToDevice);
    md5_iter_gpu<<<1, 1>>>(state_d, M_d);
    // state = md5_iter(state, M);
  }

  cudaMemcpy(&state, state_d, sizeof(struct md5_state),
             cudaMemcpyDeviceToHost);

  if (time != NULL) {
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    float elapsed_time;
    cudaEventElapsedTime(&elapsed_time, start, stop);
    *time = elapsed_time / 1000.0f;

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
  }

  write_hash(state, output_file);

  cudaFree(state_d);
  cudaFree(M_d);
}
