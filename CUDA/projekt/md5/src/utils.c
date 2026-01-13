#include "utils.h"
#include <stdint.h>

uint64_t get_file_size(FILE *file) {
  uint64_t pos = ftell(file);
  fseek(file, 0, SEEK_END);
  uint64_t size = ftell(file);
  fseek(file, pos, SEEK_SET);
  return size;
}
