#include "md5c.h"
#include "md5g.h"
#include "sum.h"
#include "utils.h"
#include <stdbool.h>
#include <stdint.h>

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

void calculate_md5_sum(FILE *input_file, FILE *output_file) {
  uint64_t file_size = get_file_size(input_file);
  printf("File size: %lu bytes\n", file_size);

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

  write_hash(state, output_file);
}

void calculate_md5_sum_gpu(FILE *input_file, FILE *output_file) {
  uint64_t file_size = get_file_size(input_file);
  printf("File size: %lu bytes\n", file_size);

  // TODO: alloc + cpy
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

  write_hash(state, output_file);

  cudaFree(state_d);
  cudaFree(M_d);
}
