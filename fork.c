// Source: man fork
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    puts("Expected to get one argument (number of forks)");
    exit(EXIT_FAILURE);
  }
  int num_forks = atoi(argv[1]);
  pid_t pid, wpid;

  /* Fork a new child process and sleep before each fork for 2 seconds */
  for (int i = 0; i < num_forks; i++) {
    sleep(2);
    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
      perror("signal");
      exit(EXIT_FAILURE);
    }
    pid = fork();
    switch (pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0:
      puts("Child busy looping.");
      while(1);
      exit(EXIT_SUCCESS);
    default:
      printf("Child is PID %jd\n", (intmax_t)pid);
    }
  }

   int status = 0;
   while ((wpid = wait(&status)) > 0);
}
