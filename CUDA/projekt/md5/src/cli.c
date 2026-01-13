#include "cli.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

struct args_t parse_args(int argc, char *argv[]) {
  int opt;

  struct args_t args = {stdin, stdout, 'h', 10, 2048};

  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"benchmark", no_argument, 0, 'b'},
      {"interations", required_argument, 0, 'r'},
      {"length", required_argument, 0, 'l'},
      {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "hbr:l:", long_options, NULL)) != -1) {
    switch (opt) {
    case 'h':
      print_help(argv[0]);
      break;
    case 'b':
      args.mode = 'b';
      printf("[Benchmark]\n\n");
      break;
    case 'r':
      args.iterations = atoi(optarg);
      break;
    case 'l':
      args.length = atoi(optarg);
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
         "  -b / --benchmark\tRun in benchmark mode\n"
         "  [options]:\n"
         "    -r / --iterations [number]\tNumber of iterations (default: 10)\n"
         "    -l / --length [number]\tLength of the input data in bytes "
         "(default: 2048)\n"
         "\n",
         program_name);

  exit(0);
}
