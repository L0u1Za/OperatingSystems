#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

/*
S = 0
cycle 0 to N:
    <-Parent process->
    write()
    A(S,2)
    Z(S)
    read()
    <-Child process->
    D(S,1)
    read()
    write()
    D(S,1)
*/

int main() {
    int     fd[2], result;

    size_t size;
    char  resstring[14];

    char pathname[] = "task1.c";
    key_t key;
    struct sembuf mybuf;
    int semid;

    int N;
    scanf("%d", &N);

    if (pipe(fd) < 0) {
        printf("[error] can\'t open pipe\n");
        exit(-1);
    }

    if ((key = ftok(pathname,0)) < 0) {
        printf("[error] can\'t generate key\n");
        exit(-1);
    }

    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("[error] can\'t get semaphore set\n");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else {
        for (int i = 0; i < N; ++i) {
            if (result > 0) {

                /* Parent process */

                size = write(fd[1], "Hello, world!", 14);

                if (size != 14) {
                    printf("Can\'t write all string to pipe\n");
                    exit(-1);
                }

                mybuf.sem_num = 0;
                mybuf.sem_op = 2;
                mybuf.sem_flg = 0;
                if (semop(semid, &mybuf, 1) < 0) {
                    printf("[parent error] can\'t wait for condition\n");
                    exit(-1);
                }

                mybuf.sem_num = 0;
                mybuf.sem_op = 0;
                mybuf.sem_flg = 0;
                if (semop(semid, &mybuf, 1) < 0) {
                    printf("[parent error] can\'t wait for condition\n");
                    exit(-1);
                }
                size = read(fd[0], resstring, 14);
                if (size != 14) {
                    printf("[parent error] can\'t read string from pipe\n");
                    exit(-1);
                }

                printf("[parent success %d] read from pipe: %s\n", i, resstring);

            } else {

                /* Child process */

                mybuf.sem_num = 0;
                mybuf.sem_op = -1;
                mybuf.sem_flg = 0;
                if (semop(semid, &mybuf, 1) < 0) {
                    printf("[parent error] can\'t wait for condition\n");
                    exit(-1);
                }

                size = read(fd[0], resstring, 14);

                if (size != 14) {
                    printf("Can\'t read string from pipe\n");
                    exit(-1);
                }
                printf("[child success %d] read from pipe: %s\n", i, resstring);

                size = write(fd[1], "Hello, world!", 14);
                if (size != 14) {
                    printf("[child error] can\'t write all string to pipe\n");
                    exit(-1);
                }

                mybuf.sem_num = 0;
                mybuf.sem_op = -1;
                mybuf.sem_flg = 0;
                if (semop(semid, &mybuf, 1) < 0) {
                    printf("[parent error] can\'t wait for condition\n");
                    exit(-1);
                }
            }
        }
    }
    if (close(fd[1]) < 0) {
        printf("parent: Can\'t close writing side of pipe\n"); exit(-1);
    }
    if (close(fd[0]) < 0) {
        printf("child: Can\'t close reading side of pipe\n"); exit(-1);
    }

    return 0;
}
