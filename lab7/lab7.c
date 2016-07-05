#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFSIZE 1024

void exec_regular(char *userInput[]) {
	pid_t pid = fork();

  if (pid == 0) {
    execvp(userInput[0], userInput);
  } else {
    wait(0);
  }
}

void exec_arg_1(int fd[], char *arg_1[]) {
	pid_t pid;

	pid = fork();

	switch (pid) {
		case -1:
			exit(-1);
		case 0:
			if (fd[1] != STDOUT_FILENO && dup2(fd[1], STDOUT_FILENO) == -1) {
				exit(0);
			}
			if (execvp(*arg_1, arg_1) == -1) {
				exit(-1);
			}
	}
}

void exec_agr_2(int fd[], char *arg_2[]) {
	pid_t pid;

	pid = fork();
	switch (pid) {
		case -1:
			exit(-1);
		case 0:

			close(fd[1]);

			if (fd[0] != STDIN_FILENO && dup2(fd[0], STDIN_FILENO) == -1) {
				close(fd[0]);
			}

			if (execvp(*arg_2, arg_2) == -1) {
				exit(-1);
			}
	}
}

int main (void) {
	pid_t pid;
  ssize_t readLen;
	char userInput[BUFSIZE];
	char *tmp_intput, *token;

	char *args[BUFSIZE];
	char *arg_1[BUFSIZE];
	char *arg_2[BUFSIZE];

	int i, status;
	int fd[2];

	while(1) {
    printf("> ");
    fflush(stdout);
    readLen = read(0, userInput, BUFSIZE);

    // EOF / ctr + d
    if (readLen <= 0) {
      printf("%s\n", "bye bye");
      exit(readLen);
    }

    userInput[readLen] = '\0';

		char *tmp, *token;

		// split |
		i = 0;
		tmp = userInput;
		while((token = strtok(tmp, "|")) != NULL) {
			args[i++] = token;
			tmp = NULL;
		}

		// split arg_1
		i = 0;
		tmp_intput = args[0];
		while((token = strtok(tmp_intput, " \n")) != NULL) {
			arg_1[i++] = token;
			tmp_intput = 0;
		}

		// split arg_2
		i = 0;
		tmp_intput = args[1];
		while((token = strtok(tmp_intput, " \n")) != NULL) {
			arg_2[i++] = token;
			tmp_intput = 0;
		}

		pipe(fd);

		if (*arg_1 != NULL && *arg_2 != NULL) {
			exec_arg_1(fd, arg_1);
			exec_agr_2(fd, arg_2);
		} else {
			exec_regular(arg_1);
		}

		close(fd[0]);
		close(fd[1]);

		while ((pid = wait(&status)) != -1);
	}

	return 0;
}

