#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>


void print_processes_from_file(char * filename) {
  int process_id;
  char cmd[250];
  int tty_nr = 0, tty_pgrp = 0, time1 = 0, time2 = 0;
  FILE * file = fopen(filename, "r");
  if (file == NULL) {
    printf("%s", "Cant open file\n");
    return;
  }
  int number = 0;
  char str[250];
  fscanf(file, "%d", &process_id);
  fscanf(file, "%s", cmd);
  fscanf(file, "%s", str);

  for (int i = 0; i < 3; ++i) {
    fscanf(file, "%d", &number);
  }

  fscanf(file, "%d", &tty_nr);
  fscanf(file, "%d", &tty_pgrp);
  for (int i = 0; i < 5; ++i) {
    fscanf(file, "%d", &number);
  }

  fscanf(file, "%d", &time1);
  fscanf(file, "%d", &time2);

  int time = (time1 + time2) / 100; // normal time
  int minute = time / 60;
  int second = time % 60;


  // delete () from str
  size_t lenStr = strlen(cmd);
  char process[250];
  for (size_t j = 1; j < lenStr - 1; ++j) {
    process[j - 1] = cmd[j];
  }
  strcpy(cmd, process);
  printf("%5.0d %-11.11s %2.2d:%2.2d   %-10.50s\n", process_id, "    ?", minute, second, cmd);
}

int main() {
  printf("process_id TTY     TIME     CMD\n");
  DIR * pr_dir = opendir("/proc");
  if (pr_dir != NULL) {
    struct dirent * dir_reader;
    while ((dir_reader = readdir(pr_dir)) != NULL) {
      // chose the direction, which names starts with numbers
      size_t lenStr = strlen(dir_reader->d_name);
      int is_number = 1;

      for (size_t i = 0; i < lenStr; ++i) {
        if (!isdigit(dir_reader->d_name[i])) {
          is_number = 0;
          break;
        }
      }
      if (is_number == 1) {
        char way[250] = "/proc/";
        strcat(way, dir_reader->d_name);
        strcat(way, "/stat");

        print_processes_from_file(way);
      }
    }
  }
  else{
    fprintf(stderr, "Unable to read the directory");
  }
  return 0;
}