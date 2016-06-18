#include <pthread.h>
#include <stdio.h>

#define LOOPS 100000

void *print(void *arg) {
  char *word = (char *) arg;
  printf("%s\n", word);
  pthread_exit(0);
  return 0;
}

// Conclusion from output:
// -----------------------
//  The execution time is not consistent and somewhat random
//
int main(void) {
  pthread_t tid1, tid2;

  for(int i = 0; i < LOOPS; i++) {
    pthread_create(&tid1, NULL, print, "hello");
    pthread_create(&tid2, NULL, print, "world");
  }

  pthread_exit(0);
}
