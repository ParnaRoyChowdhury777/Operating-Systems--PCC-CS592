//Child Process and Parent Process

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	int pid;
	pid = fork();
	if(pid > 0) {
		printf("PARENT: pid=%d\tppid=%d\n",getpid(),getppid());
		sleep(9);
	}
	if(pid == 0) {
		printf("CHILD: pid=%d\tppid=%d\n",getpid(),getppid());
		sleep(9);
	}
	return 0;
}
