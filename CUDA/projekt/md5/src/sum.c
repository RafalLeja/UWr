#include "sum.h"
#include "md5.h"
#include "utils.h"

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

    fwrite(buffer, 1, 64, output_file);
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

    fwrite(&final_data[block * 64], 1, 64, output_file);

    state = md5_iter(state, M);
  }

  printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
         state.a & 0xff, (state.a >> 8) & 0xff, (state.a >> 16) & 0xff,
         (state.a >> 24) & 0xff, state.b & 0xff, (state.b >> 8) & 0xff,
         (state.b >> 16) & 0xff, (state.b >> 24) & 0xff, state.c & 0xff,
         (state.c >> 8) & 0xff, (state.c >> 16) & 0xff, (state.c >> 24) & 0xff,
         state.d & 0xff, (state.d >> 8) & 0xff, (state.d >> 16) & 0xff,
         (state.d >> 24) & 0xff);
}
