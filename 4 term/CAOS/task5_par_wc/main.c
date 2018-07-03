#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define MAX_PATH_LEN 800
#define DEFAULT_FILES_NUMBER 100000
#define WC_PATH "/usr/bin/wc"

size_t files_capacity = DEFAULT_FILES_NUMBER;
char **files;
size_t files_number = 0;
int *files_open;
size_t num_proc = 1;
int *fd;
size_t sum_strings = 0, sum_words = 0, sum_letters = 0;
size_t strings = 0, words = 0, letters = 0;

void summurize(size_t a, size_t b, size_t c) {
  sum_strings += a;
  sum_words += b;
  sum_letters += c;
}

void scanf_res(FILE *fd_open) {
  fscanf(fd_open, "%zu", &strings);
  fscanf(fd_open, "%zu", &words);
  fscanf(fd_open, "%zu", &letters);
}


void init_files() {
  files = (char **) malloc(DEFAULT_FILES_NUMBER * sizeof(char *));
  for (size_t j = 0; j < DEFAULT_FILES_NUMBER; ++j) {
    files[j] = (char *) malloc(MAX_PATH_LEN * sizeof(char));
  }

}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("%s \n", "Usage: ./a.out number_of_threads file_name , f.e. ./a.out 16 names.txt");
    return 1;
  }

  num_proc = (size_t) atoll(argv[1]);
  FILE *file_open = fopen(argv[2], "r");
  // int file_open = open()
  if (!file_open) {
    printf("%s %s \n", "There is no such file or directory:", argv[2]);
    return 2;
  }

  init_files();

  char *name = (char *) malloc(MAX_PATH_LEN * sizeof(char));
  char c;

  size_t i = 0;
  size_t current_length = 0;
  while ((c = fgetc(file_open)) != EOF) {


    if (!isspace(c)) {
      files[i][current_length] = c;
      ++current_length;
    }
    else if(strlen(files[i]) > 0){
      files[i][current_length] = '\0';
      current_length = 0;
      ++files_number;
      ++i;
      if (i >= files_capacity - 2) {
        files_capacity *= 2;
        files = (char **) realloc(files, files_capacity * sizeof(*files));
        for (size_t j = i; j < files_capacity; ++j) {
          files[j] = (char *) malloc(MAX_PATH_LEN * sizeof(char));
        }
      }
    }
  }
  if (current_length > 0) {
    ++files_number;
    files[i][current_length] = '\0';
  }
  fd = (int *) malloc(files_number * sizeof(int));
  pid_t id;
  i = files_number;
  while (i--) {
  // for (size_t i = 0; i < files_number; ++i) {
    if (i >= num_proc) {
      wait(0);
    }
    char pattern_gen[] = "/tmp/fileXXXXXX";
    fd[i] = mkstemp(pattern_gen);
    id = fork();

    if (id == -1) {
      perror("FORK ERROR");
      exit(4);
    }
    else if (id == 0) {
      dup2(fd[i], 1);
      close(fd[i]);
      execlp(WC_PATH, "wc", files[i], NULL);
    }
    unlink(pattern_gen);
  }

  i = files_number;
  while (i--) {
  //for (size_t i = 0; i < files_number; ++i) {
    wait(0);
  }


  i = files_number;
  while (i--) {
  // for (size_t i = 0; i < files_number; ++i) {
    lseek(fd[i], 0, SEEK_SET);
    FILE *fd_open;
    fd_open = fdopen(fd[i], "r");
    scanf_res(fd_open);
    summurize(strings, words, letters);
    fclose(fd_open);
    // free(fd_open);
  }
  printf("%zu %zu %zu \n", sum_strings, sum_words, sum_letters);

  fclose(file_open);
  free(files);
  free(fd);

  return 0;
}
