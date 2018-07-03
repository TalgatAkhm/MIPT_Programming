#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define FIND_NEXT_LEFT_BY_I_DIV(num, i) (((num+i-1)/i)*i)
#define RANGE 4194304ULL
#define MAX_NUM 2147483647ULL
#define DEFAULT_THREAD_NUMBER 16
#define not_prime 0
#define prime 1

unsigned long long max_num;
char *is_prime;
unsigned long long current_len;
unsigned long long number_threads = DEFAULT_THREAD_NUMBER;

struct cadre {
  unsigned long long left;
  unsigned long long right;
};

void *eratosphen_sieve(void *args) {
  struct cadre *current_borders = (struct cadre *) args;
  unsigned long long i, j;
  for (/*unsigned long long */i = 2; i <= current_len; ++i) {
    if (is_prime[i]) {
      unsigned long long next_left = FIND_NEXT_LEFT_BY_I_DIV(current_borders->left, i);
      for (/*unsigned long long */j = next_left; j <= current_borders->right; j += i) {
        is_prime[j] = not_prime;
      }
    }
  }
}

void calc_cadres_borders(unsigned long long *cadre_border, unsigned long long end,
                         unsigned long long cur_threads_num, unsigned long long i, unsigned long long j){
  unsigned long long length_to_threads  = (end - i) / cur_threads_num;
  if (j < (end - i) % cur_threads_num)
    ++length_to_threads;
  *cadre_border += length_to_threads;
}

int main(int argc, const char *argv[]) {
  number_threads = (unsigned long long) atol(argv[1]);
  if (argc == 3) {
    max_num = (unsigned long long) atoll(argv[2]);
  } else if (argc == 2) {
    max_num = MAX_NUM;
  } else {
    exit(1);
  }
  is_prime = (char *) malloc(max_num * sizeof(char));

  is_prime[0] = not_prime;
  is_prime[1] = not_prime;
/*  for (unsigned long long j = 2; j < max_num; ++j) {
    is_prime[j] = prime;
  }*/
  memset(is_prime+2, prime, max_num - 2);
  unsigned long long end = 0;
  unsigned long long cur_threads_num = 0;
  pthread_t *id;
  printf("%d \n", 2); //because of ++j optimization in printing cadre
  for (unsigned long long i = 2; i < max_num - 1; i *= i) {
    end = i * i;
    current_len = i;

    if (end > max_num - 1) {
      if (argc != 2) {
        end = max_num - 1;
      } else {
        is_prime = realloc(is_prime, end + 1);
        memset(is_prime + max_num, prime, end + 1 - max_num);
        max_num = end + 1;
      }
    }
    cur_threads_num = MIN(number_threads, end - i);
    id = (pthread_t *) malloc(cur_threads_num * sizeof(pthread_t));
    struct cadre *cadres = (struct cadre *) malloc(cur_threads_num * sizeof(struct cadre));

    unsigned long long cadre_border = i + 1;
    for (unsigned long long j = 0; j < cur_threads_num; ++j) {
      cadres[j].left = cadre_border;
      calc_cadres_borders(&cadre_border, end, cur_threads_num, i, j);
      cadres[j].right = cadre_border - 1;
      pthread_create(&id[j], NULL, eratosphen_sieve, &cadres[j]);
    }
    for (unsigned long long j = 0; j < cur_threads_num; ++j)
      pthread_join(id[j], NULL);

    for (unsigned long long j = i + 1; j < end; ++j)
      if (is_prime[j]) {
        printf("%llu\n", j);
        // fputs(j, stdout);
        ++j;
      }
    free(cadres);
    free(id);
  }

  free(is_prime);
  return 0;
}
