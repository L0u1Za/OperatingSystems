#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
  FILE *f = fopen("file.txt","r");
  char *buffer;
  int current = 0;
  int shmid;
  char pathname[] = "task1_a.c";
  key_t key;

  if ((key = ftok(pathname,0)) < 0) {
    printf("[error] Cannot generate key\n");
    exit(-1);
  }

  if ((shmid = shmget(key, 2000*sizeof(char), 0666|IPC_CREAT)) < 0) {
    printf("[error] Cannot create shared memory\n");
    exit(-1);
  }

  if ((buffer = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
    printf("[error] Cannot attach shared memory\n");
    exit(-1);
  }

  while (!feof(f) & current < 1999) {
    buffer[current] = fgetc(f);
    current++;
  }
  printf("Program 1 wrote message\n");

  if (shmdt(buffer) < 0) {
    printf("[error] Cannott detach shared memory\n");
    exit(-1);
  }

  fclose(f);

  return 0;
}
