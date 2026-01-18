#include <stdio.h>

void benchmark_md5_sum(FILE *input_file, FILE *output_file,
                       int iterations);

void calculate_md5_sum(FILE *input_file, FILE *output_file, float *time);

void calculate_md5_sum_gpu(FILE *input_file, FILE *output_file,
                           float *time);
