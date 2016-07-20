#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 1024
#define TIMEOUT 6
#define NTIMEOUTS 3
#define THRESHOLD 15

volatile sig_atomic_t count = 0;

void sighandler(int signo) {
  if (NTIMEOUTS == ++count) {
    puts("no input given. Goodbye!");
    exit(2);
  } else {
    printf("\n>");
    fflush(stdout);
    alarm(TIMEOUT);
    }
}

int main(void) {
    char buffer[BUFSIZE];
    struct sigaction act;

    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_flags |= SA_RESTART;

    if (sigaction(SIGALRM, &act, 0) == -1) {
        perror("signation");
        return 1;
      }

    printf("> ");
    alarm(TIMEOUT);

    if (NULL == fgets(buffer, BUFSIZE, stdin)) {
      puts("no input given. Goodbye!");
      exit(2);
    } else {
      alarm(THRESHOLD);
      count = NTIMEOUTS -1;
      while(1) {}
    }

    // alarm(0);
    // fputs(buffer, stdout);

    return 0;
  }
