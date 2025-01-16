#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	int pid, status;
	pid = fork();
	if(pid > 0) {
		printf("PARENT: pid=%d\tppid=%d\n",getpid(),getppid());
		sleep(9);
		wait(&status);
	}
	if(pid == 0) {
		printf("CHILD: pid=%d\tppid=%d\n",getpid(),getppid());
		sleep(5);
		printf("CHILD DIED\n");
	}
	return 0;
}
