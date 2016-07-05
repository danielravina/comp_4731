#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>

#define SHARED	"/shared_obj"
#define	NDATA	20

int main(void) {
	int *shm_data;
	int i;
	int shmfd;
	int shmsize = sizeof(shm_data);

	shmfd = shm_open(SHARED, O_RDWR, 0666);

	if (shmfd < 0) {
		exit(-1);
	}

	shm_data = mmap(NULL, shmsize, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

	if (shm_data  == MAP_FAILED) {
		exit(-1);
	}

	for (i = 0; i < NDATA; i++) {
		printf("Shread object is: %d\t\n", shm_data[i]);
	}

	if (munmap(shm_data, shmsize) < 0) {
		exit(-1);
	}

	if (shm_unlink(SHARED) != 0) {
		exit(-1);
	}

	return 0;
}
