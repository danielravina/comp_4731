#include <stdio.h>
#include <unistd.h>

#define BUFFERSIZE 1024

int main(int argc, char** argv)
{
  ssize_t readLen;
  ssize_t writeLen;

  char buffer[BUFFERSIZE];

  while((readLen = read(0, buffer, BUFFERSIZE)) > 0) {
    writeLen = write(1, buffer, readLen);
  }
}
