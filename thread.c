// Source:
// https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_THREADS 8

void *print_message_function(void *ptr);

void *busy_loop(void *ptr) {
  while (1)
    ;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    puts("Expected to get one argument (number of forks)");
    exit(EXIT_FAILURE);
  }
  int num_forks = atoi(argv[1]);
  if (num_forks > MAX_THREADS) {
    printf("Cannot spawn more than %d threads.", MAX_THREADS);
    exit(EXIT_FAILURE);
  }

  pthread_t threads[MAX_THREADS];
  int iret[MAX_THREADS];

  /* Create independent threads each of which will execute function */

  for (int i = 0; i < num_forks; i++) {
    iret[i] = pthread_create(&threads[i], NULL, busy_loop, NULL);
  }

  /* Wait till threads are complete before main continues. */
  for (int i = 0; i < num_forks; i++) {
    pthread_join(threads[i], NULL);
  }
  exit(0);
}