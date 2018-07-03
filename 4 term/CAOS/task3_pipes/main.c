#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define NO_MORE_ARGS NULL
int number_progs;
int ** fd;

void init_descriptor(int size) {
  number_progs = size;

  fd = (int **) malloc((size) * sizeof(int *));
  for (int i = 0; i < size; ++i) {
    fd[i] = (int *) malloc(2 * sizeof(int));
  }
  for (int i = 0; i < number_progs - 1; ++i) {
    pipe(fd[i]);
  }
}

int close_descriptor(int from, int to) {
  if (from <= to && to <= number_progs) {
    for (int i = from; i < to; ++i) {
      close(fd[i][0]);
      close(fd[i][1]);
    }
    return 0;
  }
  return 1;
}

void fork_prog(char * str, int program_counter) {
  pid_t id = fork();
  if (id != 0 || id < 0) {
    return;
  }

  dup2(fd[program_counter][1], 1);
  if (program_counter != 0) {
    dup2(fd[program_counter - 1][0], 0);
  }

  close_descriptor(0, number_progs - 1);

  execlp(str, str, NO_MORE_ARGS);
  perror(str);
  exit(1);
}

int free_() {
  for (int i = 0; i < number_progs; ++i) {
    free(fd[i]);
  }
  free(fd);
}

int wait_() {
  int status;
  for (int i = 0; i < number_progs; ++i) {
    wait(&status);
    /*if (status != 0)
      perror("WAIT ERROR");*/
  }
  return 0;
}

int main(int argc, char * argv[]) {
  init_descriptor(argc - 1);

  for (int i = 1; i < argc; ++i) {
    fork_prog(argv[i], i - 1);
  }

  close_descriptor(0, number_progs);
  wait_();
  free_();
  printf("\n %s \n", "DONE");
  return 0;
}
