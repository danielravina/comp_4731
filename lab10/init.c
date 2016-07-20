#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>

#define SHMOBJ "/sharedM"

typedef struct {
  sem_t lock;
  unsigned long value;
} counter;

int main(void) {
  counter *shm_data;
  int shmfd;

  shmfd = shm_open(SHMOBJ, O_CREAT | O_RDWR, 0666);
  if (shmfd < 0) {
    exit(-1);
  }

  ftruncate(shmfd, sizeof(counter));

  if (ftruncate < 0) {
    exit(-1);
  }

  shm_data = mmap(NULL, sizeof(counter), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

  if (shm_data == MAP_FAILED) {
    exit(-1);
  }

  sem_init(&shm_data->lock, 1, 1);
  shm_data->value = 0;

  return 0;

}
