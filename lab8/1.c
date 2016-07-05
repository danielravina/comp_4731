#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main (int argc, char** argv) {
	int fd;
	char *file_data;
	struct stat file_stat;

	if ((fd = open(argv[1], O_RDWR)) < 0) {
		exit(-1);
	}

	if ((fstat(fd, &file_stat)) < 0) {
		exit(-1);
	}

	int length = atoi(argv[2]);
	// Can't run on Linux VM. See: http://stackoverflow.com/questions/18420473/invalid-argument-for-read-write-mmap
	file_data = mmap(0, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)

	if (file_data == MAP_FAILED) {
		exit(-1);
	}

	for (int i = 0; i < length; i++) {
		file_data[i] = toupper(file_data[i]);
	}

	if (munmap(file_data, length) < 0) {
		exit(-1);
	}

	return 0;
}
