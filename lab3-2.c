#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[], char* envp[]) {
	pid_t pid = fork();

	if (pid == -1) {

	printf("Error\n");

	} else if (pid == 0) {

	printf("My pid = %d\n\n", getpid());
	(void) execle("/bin/cat", "/bin/cat", "lab3-2.c", 0, envp);
	printf("Error\n");

	} else {

	printf("My ppid = %d\n", getppid());

	}

	return 0;
}
