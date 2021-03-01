#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    int shmid;
    char pathname[] = "lab6-2.c";
    key_t key;
    char *source_code;
    int fsize = 0;
    int *fsize_ptr;
    FILE *file;
    file = fopen(pathname, "r");
    
    fseek(file, 0L, SEEK_END);
    fsize = ftell(file);
    rewind(file);
    
    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, sizeof(int) + fsize * sizeof(char), 0666|IPC_CREAT)) < 0) {
        printf("Can\'t create shared memory\n");
        exit(-1);
    }

    if ((fsize_ptr = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    *fsize_ptr = fsize;
    source_code = (char*)(fsize_ptr + 1);
    
    for (int i = 0; i < fsize; i++)
        source_code[i] = fgetc(file);
        
    fclose(file);       
    
    if (shmdt(fsize_ptr) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}
