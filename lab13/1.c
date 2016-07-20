#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <dirent.h>
#include <fcntl.h>

void readDirectory(const char *dirPath, int depth) {
  DIR *pDir;
  struct dirent *dir;
  struct stat statDir;
  int spaces = depth * 4;

  lstat(dirPath, &statDir);

  if (S_ISLNK(statDir.st_mode)) {
    return;
  }

  if ((pDir = opendir(dirPath)) == NULL) {
    return;
  }

  if ((chdir(dirPath)) == -1) {
    return;
  }

  fprintf(stderr, "%*s%s/\n", spaces, "", dirPath);
  spaces = (depth +1) * 4;

  while ((dir = readdir(pDir)) != NULL) {
    lstat(dir->d_name, &statDir);

    if (S_ISDIR(statDir.st_mode)) {

      if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
        continue;
      }

      readDirectory(dir->d_name, depth + 1);

    } else {
      fprintf(stderr, "%*s%s\n", spaces, "", dir->d_name);
    }
  }

  chdir("..");
  closedir(pDir);
}

int main(int argc, char *argv[]) {
  while (--argc > 0) {
    readDirectory(*++argv, 0);
  }

  return 0;
}
