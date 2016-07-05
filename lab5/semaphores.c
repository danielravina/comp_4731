#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NITEMS 100

struct {
  int next_write;
  int next_read;
  int data[NITEMS];
} buf = {0, 0, {0}};

sem_t available, used, lock;


void *consume(void *args) {
  int id = (int) args;
  int i;
  int value;

  while(1) {
    sem_wait(&used);
    sem_wait(&lock);

    i = buf.next_read;

    printf("- %d: %d <-- #%d\n", id, buf.data[i], i);
    buf.next_read = (buf.next_read + 1) % NITEMS;

    sem_post(&lock);
    sem_post(&available);

    sleep(2);
  }

  pthread_exit(0);
}

void *produce(void *args) {
  int id = (int) args;
  int i;
  int value = 0;

  while(1) {

    sem_wait(&available);
    sem_wait(&lock);

    i = buf.next_write;

    buf.data[i] = value++;

    printf("+ %d: %d --> #%d\n", id, buf.data[i], i);

    buf.next_write = (buf.next_write + 1) % NITEMS;

    sem_post(&lock);
    sem_post(&used);

    sleep(2);
  }

  pthread_exit(0);
}


void main(int argc, char const *argv[]) {
  pthread_t tid1, tid2, tid3, tid4;

  sem_init(&available, 0, NITEMS);
  sem_init(&used, 0,0);
  sem_init(&lock, 0, 1);

  pthread_create(&tid1, 0, produce, (void *) 0);
  pthread_create(&tid2, 0, produce, (void *) 1);
  pthread_create(&tid3, 0, consume, (void *) 0);
  pthread_create(&tid4, 0, consume, (void *) 1);

  pthread_exit(0);
}
