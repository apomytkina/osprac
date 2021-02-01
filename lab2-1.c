#include <sys/types.h>
#include <unistd.h>

int main(){
	pid_t pid, ppid;

	pid = getpid();
	ppid = getppid();

	printf("My pid = %d, my pid = %d\n", (int)pid, (int)ppid);

	return 0;
}
