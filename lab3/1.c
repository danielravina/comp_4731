#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INPUT_BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {
  int status;
  char inputBuffer[INPUT_BUFFER_SIZE];
  char* userInput[100];
  ssize_t readLen;

  while(1) {
    printf("> ");
    fflush(stdout);
    readLen = read(0, inputBuffer, INPUT_BUFFER_SIZE);

    // EOF / ctr + d
    if (readLen <= 0) {
      printf("%s\n", "bye bye");
      exit(0);
    }

    char *token;
    inputBuffer[readLen] = '\0';

    token = strtok(inputBuffer, " \n");

    int i = 0;
    while(token != NULL){
      userInput[i] = token;
      token = strtok(NULL, " \n");
      ++i;
    }

    userInput[i] = 0;

    int pid = fork();

    if (pid == 0) {
      execvp(userInput[0], userInput);
    } else {
      wait(0);
    }
  }
}
