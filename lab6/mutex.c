
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NITEMS 10
#define NPRODUCERS 2
#define NCONSUMERS 2

struct{
    int n_items;
    int next_write;
    int next_read;
    int data[NITEMS];
} buf = {0, 0, 0, {0}};

pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void * args){
    int item = 0;
    int id = (int) args;

    while(1){
	    pthread_mutex_lock(&mutex);
	    while(buf.n_items == NITEMS ) {
	        pthread_cond_wait(&not_full, &mutex);
	    }

	    buf.n_items++;
	    item++;
	    buf.data[buf.next_write] = item;

	    printf("+%d: %d --> #%d\n", id, buf.data[buf.next_write], buf.next_write);
	    buf.next_write = (buf.next_write +1) % NITEMS;

	    pthread_cond_signal(&not_empty);
	    pthread_mutex_unlock(&mutex);
	    sleep(2);
    }

    pthread_exit(0);
}


void *consumer(void * args) {
  int i;
  int id = (int) args;

  while(1){
    pthread_mutex_lock(&mutex);
    while(buf.n_items == 0 ) {
        pthread_cond_wait(&not_empty, &mutex);
    }

    buf.n_items--;
    i = buf.next_read;

    printf("-%d: %d <-- #%d\n", id, buf.data[i], i);

    buf.next_read = (buf.next_read +1) % NITEMS;
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);

    sleep(2);
  }
  pthread_exit(0);
}

int main (void){
  pthread_t pid;
  int i;
  int status_th;

  for(i = 0; i < NPRODUCERS; i++){
      status_th = pthread_create(&pid, 0, producer,(void *) i);

      if(status_th != 0){
          return 1;
      }
  }

  for(i = 0; i < NCONSUMERS; i++){
      status_th = pthread_create(&pid, 0, consumer,(void *) i);

      if(status_th != 0){
          return 1;
      }
  }

  pthread_exit(0);

}



