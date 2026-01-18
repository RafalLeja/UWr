#include "cli.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

struct args_t parse_args(int argc, char *argv[]) {
  int opt;

  struct args_t args = {
      NULL, stdout, false, 'h', 10,
  };

  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},

      {"benchmark", no_argument, 0, 'b'},
      {"iterations", required_argument, 0, 'r'},

      {"sum", no_argument, 0, 's'},
      {"input", required_argument, 0, 'i'},
      {"output", required_argument, 0, 'o'},

      {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "hbr:si:o:", long_options,
                            NULL)) != -1) {
    switch (opt) {
    case 'h':
      print_help(argv[0]);
      break;

    case 'b':
      args.benchmark = true;
      printf("[Benchmark]\n\n");
      break;
    case 'r':
      args.iterations = atoi(optarg);
      break;

    case 's':
      args.mode = 's';
      printf("[Sum]\n\n");
      break;
    case 'i':
      args.input_file = fopen(optarg, "rb");
      if (args.input_file == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
      }
      break;
    case 'o':
      args.output_file = fopen(optarg, "wb");
      if (args.output_file == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
      }
      break;
    default:
      print_help(argv[0]);
    }
  }

  return args;
}

void print_help(const char *program_name) {
  printf("Usage: %s [mode] [options]\n\n"
         "[modes]:\n"
         "  -h / --help\t\tDisplay this help message\n"
         "\n"
         "  -b / --benchmark\tRun in benchmark mode\n"
         "  [options]:\n"
         "    -r / --iterations [number]\tNumber of iterations (default: "
         "10)\n"
         "\n"
         "  -s / --sum\t\tCalculate md5sum\n"
         "  [options]:\n"
         "    -i / --input [file]\tInput file to read data from\n"
         "    -o / --output [file]\tOutput file to write the md5sum to "
         "(default: stdout)\n"
         "\n",
         program_name);

  exit(0);
}
