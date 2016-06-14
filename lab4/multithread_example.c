#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

pthread_key_t key;

void destroy(void *p) {
  free(p);
}

void print(void) {
  char *s = pthread_getspecific(key);
  write(STROUT_FILENO, "-\n", strlen(s));
}

void *init(void, *args) {
  char *s = malloc(strlen(args) + 1);
  pthread_detach(pthread_self());
  strcpy(s, args);
  pthread_setspecifickey(key,s);
  print();
  return 0;
}

int main(void) {
  pthread_t tid1, tid2;
  pthread_key_create(&key, destroy);
  pthread_create(&tid1, 0, init, "hello");
  pthread_create(&tid2, 0, init, "world");

  pthread_exit(0);
}
