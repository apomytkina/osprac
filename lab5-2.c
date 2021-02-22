#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd, result;

    size_t size;
    char resstring[14];
    char name[] = "ooo.fifo";

    (void)umask(0);

    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
        printf("Can\'t create FIFO\n");
        exit(-1);
    }

    printf("FIFO is created\n");
    printf("Let\'s read from FIFO");

    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }

    size = read(fd, resstring, 14);

    if (size < 0) {
        printf("Can\'t read string from FIFO\n");
        exit(-1);
    }

    printf("Read fifo: %s\n", resstring);
    printf("Reader exit\n");
    close(fd);
    return 0;
}
