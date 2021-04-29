#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>

int main() {
    int msqid;
    char pathname[] = "lab11-2a.c";
    key_t key;
    int len, maxlen;

    struct mymsgbuf {
        long mtype;
        struct {
            short sinfo;
        } info;
    } mybuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can't get msqid\n");
        exit(-1);
    }

    printf("First program started sending messages to the seond one.\n");
    for (int i = 1; i <= 5; ++i) {
        mybuf.mtype = 1;
        mybuf.info.sinfo = 1337;
        len = sizeof(mybuf.info);

        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Can't send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    printf("First program finished sending messages to the second one.\n");
    printf("First program started receiving messages from the second one.\n");

    for (int i = 1; i <= 5; ++i) {
        maxlen = sizeof(mybuf.info);
        if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0) < 0) {
            printf("Can't receive message from queue\n");
            exit(-1);
        }

        printf("First program received message type = %ld, sInfo = %i\n", mybuf.mtype, mybuf.info.sinfo);
    }

    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    printf("First program finished receiving messages from the second one.\n");

    return 0;
}
