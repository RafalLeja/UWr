#include <stdio.h>

void crack(FILE *input_file, FILE *output_file, int pass_length,
           int pass_type, float *time);

void crack_gpu(FILE *input_file, FILE *output_file, int pass_length,
               int pass_type, float *time);
