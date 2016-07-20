#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>

#define SHMOBJ  "/sharedM"

typedef struct {
  sem_t lock;
  unsigned long value;
} counter;

int main(void) {
  counter *shm_data;
  int shmfd;

  shmfd = shm_open(SHMOBJ, O_RDWR, 0666);

  if (shmfd < 0) {
    exit(-1);
  }

  shm_data = mmap(NULL, sizeof(counter), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

  if (shm_data == MAP_FAILED) {
    exit(-1);
  }

  if (sem_destroy(&shm_data->lock) == -1) {
    exit(-1);
  }

  if (munmap(shm_data, sizeof(counter)) < 0) {
    exit(-1);
  }

  if (shm_unlink(SHMOBJ) != 0) {
    exit(-1);
  }

  fprintf(stdout, "Success\n");

  return 0;
}
