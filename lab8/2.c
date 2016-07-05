#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main(void) {
	int *file_data;
	int status;

	if ((file_data = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(-1);
	}

	*file_data = 0;

	status = fork();

	if (status == -1) {
		perror("fork");
		exit(-1);
	} else if(status == 0) {
		printf("file data is: %d\n", *file_data);
		(*file_data)++;

		if (munmap(file_data, sizeof(int)) == -1) {
			perror("munmap");
			exit(-1);
		}
		exit(0);
	} else {
		wait(&status);
		printf("file data is: %d\n", *file_data);

		if (munmap(file_data, sizeof(int)) == -1) {
			perror("munmap");
			exit(-1);
		}
		exit(0);
	}
	return 0;
}
