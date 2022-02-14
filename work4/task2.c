#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     fd[2][2], result;

  size_t size[2];
  char  resstring[2][14];

  for (int i = 0; i < 2; ++i) {
    if (pipe(fd[i]) < 0) {
      printf("Can\'t open pipe:%d\n", i + 1);
      exit(-1);
    }
  }

  result = fork();

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) {
    /* Parent process */

    if (close(fd[0][0]) < 0) {
      printf("[parent] Can\'t close reading side of 1 pipe\n"); exit(-1);
    }

    size[0] = write(fd[0][1], "Hello, world, from parent!", 27);

    if (size[0] != 27) {
      printf("Can\'t write all string to 1 pipe\n");
      exit(-1);
    }

    if (close(fd[0][1]) < 0) {
      printf("[parent] Can\'t close writing side of 1 pipe\n"); exit(-1);
    }

    if (close(fd[1][1]) < 0) {
      printf("[parent] Can\'t close writing side of 2 pipe\n"); exit(-1);
    }


    size[1] = read(fd[1][0], resstring[1], 26);

    if (size[1] < 0) {
      printf("Can\'t read string from 2 pipe\n");
      exit(-1);
    }

    printf("Parent got:  %s\n", resstring[1]);

    if (close(fd[1][0]) < 0) {
      printf("[parent] Can\'t close reading side of 1 pipe\n"); exit(-1);
    }

  } else {

    /* Child process */
    if (close(fd[0][1]) < 0) {
      printf("[child] Can\'t close writing side of 1 pipe\n"); exit(-1);
    }

    size[0] = read(fd[0][0], resstring[0], 27);

    if (size[0] < 0) {
      printf("Can\'t read string from 1 pipe\n");
      exit(-1);
    }

    printf("Child got:  %s\n", resstring[0]);

    if (close(fd[0][0]) < 0) {
      printf("[child] Can\'t close reading side of 1 pipe\n"); exit(-1);
    }

    if (close(fd[1][0]) < 0) {
      printf("[child] Can\'t close reading side of 2 pipe\n"); exit(-1);
    }

    size[1] = write(fd[1][1], "Hello, world, from child!", 26);

    if (size[1] != 26) {
      printf("Can\'t write all string to 2 pipe\n");
      exit(-1);
    }

    if (close(fd[1][1]) < 0) {
      printf("[child] Can\'t close writing side of 2 pipe\n"); exit(-1);
    }
  }

  return 0;
}
