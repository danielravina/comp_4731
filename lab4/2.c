#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFERSIZE 10

void *readFifo(void *arg) {
  int fifo;
  char *path = (char *) arg;

  fifo = open(path, O_RDONLY);

  if (fifo < 0) {
    pthread_exit(&fifo);
  }

  char buffer[BUFFERSIZE];

  while (1) {
    if (read(fifo, buffer, BUFFERSIZE) > 0) {
      printf("%s", buffer);
    }
  }

  pthread_exit(0);
}

int main(void) {
  pthread_t tid1, tid2;

  pthread_create(&tid1, 0, readFifo, "/home/vagrant/fifo1");
  pthread_create(&tid2, 0, readFifo, "/home/vagrant/fifo2");

  pthread_exit(0);

  return 0;
}
