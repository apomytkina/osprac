#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{ 
    char *source_code;
    int *array;
    int shmid;
    char pathname[] = "lab6-2.c";
    key_t key; 
    int fsize = 0;
    int *fsize_ptr;
    
    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    
    if ((shmid = shmget(key, sizeof(int) + fsize * sizeof(char), 0)) < 0) {
        printf("Can\'t create shared memory\n");
        exit(-1);
    }

    if ((fsize_ptr = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    fsize = *fsize_ptr;
    source_code = (char*)(fsize_ptr + 1);
    
    for (int i = 0; i < fsize; i++)
        putchar(source_code[i]);
    
    if (shmdt(fsize_ptr) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    
    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        printf("Can't delete shared memory\n");
        exit(-1);
    }
    return 0;
}
