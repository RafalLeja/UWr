#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  // Declare variables to store the flag and its corresponding value
  int flag;
  char *value = NULL;

  // Use getopt to parse the command-line arguments
  while ((flag = getopt(argc, argv, "f:")) != -1) {
    switch (flag) {
      case '-':
        optarg++;
        break;
      case 'f':
        value = optarg;
        break;
      case '?':
        // Print an error message if an unknown flag is used
        fprintf(stderr, "Unknown option '-%c'\n", optopt);
        break;
    }
  }

  // Use the value of the flag to determine the desired behavior
  if (value != NULL) {
    if (strcmp(value, "option1") == 0) {
      // Do something for option1
      printf("Option 1 selected\n");
    } else if (strcmp(value, "option2") == 0) {
      // Do something for option2
      printf("Option 2 selected\n");
    } else {
      // Print an error message if the flag value is not recognized
      fprintf(stderr, "Invalid flag value '%s'\n", value);
    }
  } else {
    // Do the default behavior if no flag is provided
    printf("No flag provided\n");
  }

  return 0;
}
