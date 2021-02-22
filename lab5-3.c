#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd, result;

    size_t size;
    char resstring[14];
    char name[]="ooo.fifo";

    (void)umask(0);

    printf("Let\'s write to FIFO\n");

    if((fd = open(name, O_WRONLY)) < 0){
        printf("Can\'t open FIFO for writing\n");
        exit(-1);
    }

    size = write(fd, "Hello, world!", 14);
    printf("FIFO is written\n");

    if(size != 14) {
        printf("Can\'t write all string to FIFO\n");
        exit(-1);
    }
    close(fd);
    printf("Writer exit\n");
    return 0;
}
