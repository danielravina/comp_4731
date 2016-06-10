#include <stdio.h>

int main(int argc, char const *argv[]) {
  int pid = fork();

  if(pid == 0) {
    printf("child:   pid = %i, ppid = %i, pgid = %i\n", getpid(), getppid(), getpgrp());
    // 0 will create a new group
    setpgid(getpid(), 0);
    printf("child:   pid = %i, ppid = %i, pgid = %i\n", getpid(), getppid(), getpgrp());
  } else {
    wait(0);
    printf("parent:  pid = %i, ppid = %i, pgid = %i\n", getpid(), getppid(), getpgrp());
  }
}


