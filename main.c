/*
  Code from https://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html
*/
#include <stdio.h>
#include <stdlib.h>

int match(char*, char*);
int matchhere(char*, char*);
int matchstar(int, char*, char*);

int match(char* regexp, char* text) {
  if (regexp[0] == '^') return matchhere(regexp + 1, text);
  do {
    if (matchhere(regexp, text)) return 1;
  } while (*text++ != '\0');
  return 0;
}

int matchhere(char* regexp, char* text) {
  if (regexp[0] == '\0') return 1;
  if (regexp[1] == '*') return matchstar(regexp[0], regexp+2, text);
  if (regexp[0] == '$' && regexp[1] == '\0') return *text == '\0';
  if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text)) return matchhere(regexp + 1, text + 1);
  return 0;
}

int matchstar(int c, char* regexp, char* text) {
  do {
    if (matchhere(regexp, text)) return 1;
  } while (*text != '\0' && (*text++ == c || c == '.'));
  return 0;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Invalig number of arguments\n");
    return EXIT_FAILURE;
  }

  FILE* fptr;
  fptr = fopen(argv[2], "r");

  if (fptr) {
    size_t counter = 0;
    char line[512];
    while (fgets(line, 512, fptr)) {
      ++counter;
      if (match(argv[1], line)) {
        fprintf(stdout, "%zu: %s", counter, line);
      }
    }

  } else {
    fprintf(stderr, "Unable to open file\n");
    return EXIT_FAILURE;
  }

  fclose(fptr);
  return EXIT_SUCCESS;
}
