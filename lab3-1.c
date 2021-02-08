#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[])
{
	printf("Command line arguments:\n");	
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	printf("\n");

	printf("Environment parameters:\n");
	int j = 0;
	while (envp != NULL) {
		printf("%s\n", envp[j]);
		j++;	
	}

	return 0;
}
