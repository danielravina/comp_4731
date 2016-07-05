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
	int *shm_data, i;
	int shmfd;
	int shmsize = sizeof(shm_data);

	printf("%d\n", shmsize);

	shmfd = shm_open(SHARED, O_CREAT | O_EXCL | O_RDWR, S_IRWXU | S_IRWXG);

	if (shmfd < 0) {
		exit(-1);
	}

	if (ftruncate(shmfd, shmsize) == -1) {
		exit(-1);
	}

	shm_data = mmap(NULL, shmsize, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

	if (shm_data  == MAP_FAILED) {
		exit(-1);
	}

	for (i = 0; i < NDATA; ++i) {
		shm_data[i] = (i + 1) * 3;
	}

	if (munmap(shm_data, shmsize) < 0) {
		exit(-1);
	}


	return 0;
}
