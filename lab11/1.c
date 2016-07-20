#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

int main (int argc, char *argv[]) {
	int fd;
	struct stat file_stat;

  for(int i = 1; i < argc; i++) {

  	if ((fd = open(argv[i], O_RDWR)) == -1) {
  		exit(-1);
  	}

  	if ((fstat(fd, &file_stat)) == -1) {
  		exit(-1);
  	}

  	fprintf(stdout, "name\t\t\t: %s\n", argv[i]);
  	fprintf(stdout, "i-number\t\t: %ld\n", (long)file_stat.st_ino);
  	fprintf(stdout, "mode\t\t\t: %lo\n",  (unsigned long)file_stat.st_mode);
  	fprintf(stdout, "# of links\t\t: %ld\n", (long)file_stat.st_nlink);
  	fprintf(stdout, "user ID\t\t\t: %ld\n", (long)file_stat.st_uid);
  	fprintf(stdout, "group ID\t\t: %ld\n", (long)file_stat.st_gid);
  	fprintf(stdout, "mode\t\t\t: %ld\n", (long)file_stat.st_mode);
  	fprintf(stdout, "size\t\t\t: %lld\n", (long long)file_stat.st_size);
  	fprintf(stdout, "access time\t\t: %s", ctime(&file_stat.st_atime));
  	fprintf(stdout, "modification time\t: %s", ctime(&file_stat.st_mtime));
  	fprintf(stdout, "status change time\t: %s", ctime(&file_stat.st_ctime));
    fprintf(stdout, "\n");
  }

	return 0;
}
