#include "cli.h"
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
  case 'b':
    // Call benchmark function (not implemented here)
    printf("Running benchmark with %d iterations and input length %d bytes.\n",
           args.iterations, args.length);
    break;
  case 's':
    if (args.input_file == NULL) {
      fprintf(stderr, "Input file is required for sum mode.\n");
      return 1;
    }
    printf("Calculating MD5 sum from input file and writing to output file.\n");
    calculate_md5_sum(args.input_file, args.output_file);
    break;
  }

  return 0;
}
