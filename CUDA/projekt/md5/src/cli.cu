#include "cli.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

struct args_t parse_args(int argc, char *argv[]) {
  int opt;

  struct args_t args = {NULL, stdout, false, 'h', 10, 8, 0b1111};

  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},

      {"benchmark", no_argument, 0, 'b'},
      {"iterations", required_argument, 0, 'r'},

      {"checksum", no_argument, 0, 'c'},
      {"input", required_argument, 0, 'i'},
      {"output", required_argument, 0, 'o'},

      {"password", no_argument, 0, 'p'},
      {"pass_length", required_argument, 0, 'm'},
      {"numbers", no_argument, 0, 'n'},
      {"lowercase", no_argument, 0, 'l'},
      {"uppercase", no_argument, 0, 'u'},
      {"special", no_argument, 0, 's'},

      {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "hbr:ci:o:pm:nlus", long_options,
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

    case 'c':
      args.mode = 'c';
      printf("[Checksum]\n\n");
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

    case 'p':
      args.mode = 'p';
      printf("[Password Cracker]\n\n");
      break;

    case 'm':
      args.pass_length = atoi(optarg);
      break;

    case 'n':
      args.pass_type &= 0x1;
      break;

    case 'l':
      args.pass_type &= 0x2;
      break;

    case 'u':
      args.pass_type &= 0x4;
      break;

    case 's':
      args.pass_type &= 0x8;
      break;
    default:
      print_help(argv[0]);
    }
  }

  return args;
}

void print_help(const char *program_name) {
  printf(
      "Usage: %s [mode] [options]\n\n"
      "[modes]:\n"
      "  -h / --help\t\tDisplay this help message\n"
      "\n"
      "  -b / --benchmark\tRun in benchmark mode\n"
      "  [options]:\n"
      "    -r / --iterations [number]\tNumber of iterations (default: "
      "10)\n"
      "\n"
      "  -c / --checksum\t\tCalculate md5sum\n"
      "  [options]:\n"
      "    -i / --input [file]\tInput file to read data from\n"
      "    -o / --output [file]\tOutput file to write the md5sum to "
      "(default: stdout)\n"
      "\n"
      "  -p / --password\t\tRun in password cracking mode\n"
      "  [options]:\n"
      "    -i / --input [file]\tInput file containing md5 hash\n"
      "    -m / --pass_length [number]\tLength of the password to crack\n"
      "    -n / --numbers\t\tInclude numbers in the password\n"
      "    -l / --lowercase\tInclude lowercase letters in the password\n"
      "    -u / --uppercase\tInclude uppercase letters in the password\n"
      "    -s / --special\t\tInclude special characters in the password\n"
      "\n",
      program_name);

  exit(0);
}
