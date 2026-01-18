#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>

struct args_t {
  FILE *input_file;
  FILE *output_file;
  bool benchmark;
  char mode;
  int iterations;
};

#endif // ARGS_H
