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
#define NITEMS   25

typedef struct {
  sem_t lock;
  unsigned long value;
} counter;

int main(void) {
  counter *shm_data;
  int shmfd;

  size_t i;

  shmfd = shm_open(SHMOBJ, O_RDWR, 0666);

  if (shmfd < 0) {
    exit(-1);
  }

  shm_data = mmap(NULL, sizeof(counter), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

  if (shm_data == MAP_FAILED) {
    exit(-1);
  }

  for (i = 0; i < NITEMS; ++i) {
    if (sem_wait(&shm_data->lock) == -1) {
      exit(-1);
    }

    fprintf(stdout, "Current value:\t%lu\n", shm_data->value);
    shm_data->value++;
    fprintf(stdout, "New value:\t%lu\n", shm_data->value);

    if (sem_post(&shm_data->lock) == -1) {
      exit(-1);
    }
  }

  return 0;
}
