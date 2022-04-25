#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int msqid;
    char pathname[] = "task2_a.c";
    key_t key;
    int len, maxlen;

    struct mymsgbuf {
        long mtype;
        struct{
            int iinfo;
        } info;
    } mybuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("[error task2_a.c] can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("[error task2_a.c] can't get msqid\n");
        exit(-1);
    }

    for (int i = 1; i <= 5; ++i) {
        mybuf.mtype = 1;
        mybuf.info.iinfo = 123;
        len = sizeof(mybuf.info);

        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("[error task2_a.c] can't send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    for (int i = 1; i <= 5; ++i) {
        maxlen = sizeof(mybuf.info);

        if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0) < 0) {
            printf("[error task2_a.c] can't receive message from queue\n");
            exit(-1);
        }

        printf("[success task2_a.c] message type = %ld, iinfo = %i\n", mybuf.mtype, mybuf.info.iinfo);
    }

    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);

    return 0;
}