#include "cli.h"
#include "pass.h"
#include "sum.h"
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct args_t args = parse_args(argc, argv);

  switch (args.mode) {
  case 'h':
    print_help(argv[0]);
    break;
  case 'c':
    if (args.input_file == NULL) {
      fprintf(stderr, "Input file is required for sum mode.\n");
      return 1;
    }
    printf("Calculating MD5 sum from input file and writing to output "
           "file.\n");
    if (args.benchmark) {
      benchmark_md5_sum(args.input_file, args.output_file,
                        args.iterations);
    } else {
      calculate_md5_sum(args.input_file, args.output_file, NULL);
    }
    break;

  case 'p':
    if (args.input_file == NULL) {
      fprintf(stderr, "Input file is required for password mode.\n");
      return 1;
    }
    if (!args.benchmark) {
      fprintf(args.output_file, "[Password Cracking]\n");
    }
    crack_device(args.input_file, args.output_file, args.pass_length,
                 args.pass_type, args.device, args.benchmark);
  }

  return 0;
}
