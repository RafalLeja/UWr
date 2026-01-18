#include "md5.h"
#include "pass.h"
#include "utils.h"
#include <cstdio>

char *get_all_chars(int pass_type, int *len) {
  static char *chars = (char *)malloc(95);
  printf("Generating character set for pass_type: %d\n", pass_type);
  int index = 0;
  if (pass_type & 0x1) {
    for (char c = '0'; c <= '9'; c++) {
      chars[index++] = c;
    }
  }
  if (pass_type & 0x2) {
    for (char c = 'a'; c <= 'z'; c++) {
      chars[index++] = c;
    }
  }
  if (pass_type & 0x4) {
    for (char c = 'A'; c <= 'Z'; c++) {
      chars[index++] = c;
    }
  }
  if (pass_type & 0x8) {
    char special_chars[] = {'!', '"', '#', '$', '%', '&', '\'', '(',
                            ')', '*', '+', ',', '-', '.', '/',  ';',
                            ':', '<', '=', '>', '?', '@', '[',  '\\',
                            ']', '^', '_', '`', '{', '|', '}',  '~'};
    for (int i = 0; i < sizeof(special_chars); i++) {
      chars[index++] = special_chars[i];
    }
  }

  chars[index] = '\0';
  *len = index;
  return chars;
}

bool crack_len(struct md5_state target_hash, int pass_length,
               int all_chars_size, char *all_chars) {
  int base = all_chars_size;
  int indices[pass_length];
  char buffer[pass_length + 1];

  memset(indices, 0, sizeof(indices));
  buffer[pass_length] = '\0';

  while (1) {
    for (int i = 0; i < pass_length; i++) {
      buffer[i] = all_chars[indices[i]];
    }

    struct md5_state current_hash = md5_passwd(buffer, strlen(buffer));
    if (current_hash.a == target_hash.a &&
        current_hash.b == target_hash.b &&
        current_hash.c == target_hash.c &&
        current_hash.d == target_hash.d) {
      printf("Password found: %s\n", buffer);
      return true;
    }

    int pos = pass_length - 1;
    while (pos >= 0) {
      indices[pos]++;
      if (indices[pos] < base) {
        break;
      } else {
        indices[pos] = 0;
        pos--;
      }
    }
    if (pos < 0) {
      break;
    }
  }
  return false;
}

void crack(FILE *input_file, FILE *output_file, int pass_length,
           int pass_type, float *time) {
  struct md5_state target_hash = get_hash_from_file(input_file);
  int all_chars_size;
  printf("Generating character set...\n");
  char *all_chars = get_all_chars(pass_type, &all_chars_size);

  for (int len = 1; len <= pass_length; len++) {
    printf("Cracking passwords of length %d...\n", len);
    if (crack_len(target_hash, len, all_chars_size, all_chars)) {
      return;
    }
  }

  printf("Password not found.\n");
}
