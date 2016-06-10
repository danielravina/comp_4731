#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int child_notify;

  printf("Number of args is: %i\n", argc);

  char *ls_args[10000];
  ls_args[0] = "ls";
  ls_args[1] = "-l";

  if (fork() == 0) {
    for(int i = 1; i < argc; i++) {
      ls_args[i+1] = argv[i];
    }

    // ls_args is ['ls', '-l', argv[1], argv[2], argv[3], ...]
    execvp("/bin/ls", ls_args);
  }
  else {
    wait( &child_notify );
  }

  return 0;
}

