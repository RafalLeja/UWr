#include "cli.h"
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
  }

  return 0;
}
