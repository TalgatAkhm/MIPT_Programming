#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <jmorecfg.h>


#define NULLSTR 1
const char ENDSTR = '\0';


boolean cmp(const void * p1, const void * p2) {
  return strcmp(*(char * const *) p1, *(char * const *) p2);
}


int main() {
  int str_iter = 0, clmn_iter = 1;

  char ** strs = malloc(sizeof(char *));
  char c;

  while ((c = getchar()) != EOF) {
    if (isspace(c)) {
      clmn_iter = 1;
      continue;
    }

    if (clmn_iter == 1) {
      str_iter = str_iter + 1;
      strs = realloc(strs, str_iter * sizeof(char *));
      strs[str_iter - 1] = malloc(sizeof(char));
    }

    strs[str_iter - 1] = realloc(strs[str_iter - 1], clmn_iter + 1);

    if (!strs[str_iter - 1]) {
      perror(NULL);
      exit(NULLSTR);
    }
    strs[str_iter - 1][clmn_iter] = ENDSTR;
    strs[str_iter - 1][clmn_iter - 1] = c;

    clmn_iter = clmn_iter + 1;
  }

  qsort(strs, str_iter, sizeof(char *), cmp);

  for (int i = 0; i < str_iter; i = i + 1) {
    printf("\"%s\"", strs[i]);
    printf("\n");
    free(strs[i]);
  }

  free(strs);
  return 0;
}
