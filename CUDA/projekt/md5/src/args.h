#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>

struct args_t {
  FILE *input_file;
  FILE *output_file;
  bool benchmark;
  char mode;
  int iterations;
  int pass_length;
  int pass_type;
};

#endif // ARGS_H
