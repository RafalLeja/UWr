#include <stdio.h>

__attribute__((leaf))
size_t my_strlen(const char *s);
const char *my_index(const char *s, char v);

int main(){
  const char *a = "abc";
  a = my_index(a, 'a');
}

const char *my_index(const char *s, char v) {
  for (size_t i = 0; i < my_strlen(s); i++)
    if (s[i] == v)
      return &s[i];
  return 0;
}

static size_t my_strlen(const char *s){
  long length = 0;
  while (*s != '\0') {
    s++;
    length++;
  }
  return length;
}