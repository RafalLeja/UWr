#include <stdio.h>

struct args_t {
  FILE *input_file;
  FILE *output_file;
  char mode;
  int iterations;
  int length;
};

struct args_t parse_args(int argc, char *argv[]);

void print_help(const char *program_name);
