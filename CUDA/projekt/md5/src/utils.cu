#include "md5.h"
#include "utils.h"
#include <stdint.h>

uint64_t get_file_size(FILE *file) {
  uint64_t pos = ftell(file);
  fseek(file, 0, SEEK_END);
  uint64_t size = ftell(file);
  fseek(file, pos, SEEK_SET);
  return size;
}

struct md5_state get_hash_from_file(FILE *input_file) {
  char buffer[33];
  if (fgets(buffer, sizeof(buffer), input_file) == NULL) {
    fprintf(stderr, "Failed to read hash from file.\n");
    exit(EXIT_FAILURE);
  }

  unsigned int hash[16];
  for (int i = 0; i < 16; i++) {
    sscanf(&buffer[i * 2], "%2x", &hash[i]);
  }
  struct md5_state state;
  state.a = (hash[0]) | (hash[1] << 8) | (hash[2] << 16) | (hash[3] << 24);
  state.b = (hash[4]) | (hash[5] << 8) | (hash[6] << 16) | (hash[7] << 24);
  state.c =
      (hash[8]) | (hash[9] << 8) | (hash[10] << 16) | (hash[11] << 24);
  state.d =
      (hash[12]) | (hash[13] << 8) | (hash[14] << 16) | (hash[15] << 24);
  return state;
}
