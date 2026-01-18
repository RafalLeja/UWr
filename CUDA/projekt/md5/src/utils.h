#include <stdint.h>
#include <stdio.h>

struct md5_state get_hash_from_file(FILE *input_file);

uint64_t get_file_size(FILE *file);
