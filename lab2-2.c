#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(){
	pid_t pid = fork();

	if (pid == -1) {

	printf("Error\n");

	} else if (pid == 0) {

	printf("My pid = %d\n\n", getpid());

	} else {

	printf("My ppid = %d\n", getppid());

	}
	 

	return 0;
}
