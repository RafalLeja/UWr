char *somestr(void) {
  static char word[14] = "Hello, world!";
  return word;
  // return "Hello, world!";
}
