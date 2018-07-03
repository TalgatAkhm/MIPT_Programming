#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define TAB 4
#define ls_r(a, ...) ls_recursive( a, (0, ##__VA_ARGS__) )

void ls_recursive(const char * cur_path, int cur_tab) {

  if (cur_tab == 0) {
    printf("%s :\n", cur_path);
    cur_tab += TAB;
  }
  
  DIR *cur_dir = opendir(cur_path);
  if (cur_dir == NULL)
    return;

  struct dirent *entry;
  char next_path[250];
  while ((entry = readdir(cur_dir)) != NULL) {

    if (entry->d_type == DT_DIR) {
      if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        strcpy(next_path, cur_path);
        strcat(next_path, "/");
        strcat(next_path, entry->d_name);

        printf("%*s %s :\n", cur_tab, "", entry->d_name);
        ls_recursive(next_path, cur_tab + TAB);
      }
    }
    else
      printf("%*s-> %s\n", cur_tab, "", entry->d_name);
  }
  closedir(cur_dir);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    ls_r(".");
    return 0;
  }
  for (size_t i = 1; i < argc; ++i)
    ls_r(argv[i]);
  return 0;
}