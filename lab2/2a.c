#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int child_notify;

  if (fork() == 0) {
    execlp("/bin/ls", "ls", "-l" , argv[1], (char*) 0);
  }
  else {
    wait( &child_notify );
  }

  return 0;
}
