#include <stdio.h>
#include <fcntl.h>

#define BUFFERSIZE 1024

void error() {
  const char msg[] = "Error writing to file\n";
  write(2, msg, sizeof(msg));
}

int main(int argc, char** argv)
{
  char buffer[BUFFERSIZE];

  int sourceFile  = open(argv[1], O_RDONLY);
  int targetFile  = open(argv[2], O_RDWR|O_CREAT, 0666);

  ssize_t readLen;
  ssize_t writeLen;

  if(sourceFile == -1 || targetFile == -1){
    error();
  }

  while((readLen = read(sourceFile, buffer, BUFFERSIZE)) > 0) {
    writeLen = write(targetFile, buffer, readLen);
    if(writeLen == -1){
      error();
    }
  }

  close(targetFile);
  close(sourceFile);
}
