#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
  int fd[2];
  int is_there_space = 0;
  int sz = 0;
  if (pipe2(fd, O_NONBLOCK) < 0) {
    printf("[error] Can\'t open pipe\n");
    exit(-1);
  }

  while (!is_there_space) {
    if (write(fd[1], "p", 1) > 0) sz++;
    else is_there_space = 1;
  }

  printf("Size: %d\n", sz);

  if (close(fd[0]) < 0) {
    printf("[error] Can'\t close reading side of pipe\n");
    exit(-1);
  }
  if (close(fd[1]) < 0) {
    printf("[error] Can'\t close writing side of  pipe\n");
    exit(-1);
  }

  return 0;
}
