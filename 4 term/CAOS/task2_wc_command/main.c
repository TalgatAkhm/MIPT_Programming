#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>

size_t strings, words, letters;
size_t sum_strings = 0, sum_words = 0, sum_letters = 0;

void wc(int file) {
  char c = 0;
  int is_cursor_in_word = 0;
  strings = words = letters = 0;

  while (read(file, &c, 1) > 0) {
    if (isspace(c) && is_cursor_in_word) {
      is_cursor_in_word = 0;
      ++words;
    }
    if (c == '\n') {
      ++strings;
    }
    else if (!isspace(c)) {
      is_cursor_in_word = 1;
    }
    ++letters;
  }

  is_cursor_in_word? ++words : 0;

  sum_strings += strings;
  sum_words += words;
  sum_letters += letters;
}

int main(int argc, char * argv[]) {
  int file_open = 0;

  if (argc == 1) {
    wc(file_open);
    printf("%d %d %d ", strings, words, letters);
  }
  else {
    for (int i = 1; i < argc; ++i) {
      file_open = open(argv[i], O_RDONLY);
      if (file_open == -1) {
        printf("НЕТ ТАКОГО ФАЙЛА ИЛИ КАТАЛОГА: %s\n", argv[i]);
        continue;
      }
        wc(file_open);
        printf("  %d %d %d %s\n", strings, words, letters, argv[i]);
    }
    argc > 2? printf("%d %d %d итого\n", sum_strings, sum_words, sum_letters) : 0;
  }
  return 0;
}