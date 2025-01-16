#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {

	if (sig == SIGALRM) {
		//signal(SIGALRM, handler);
		printf("Alarm sent from child process\n");
	}

}

int main () {

	signal(SIGALRM, handler);

	int pid = fork();

	if (pid == -1) {
		perror("FORK FAILED\n");
		return EXIT_FAILURE;
	}

	if (pid == 0) {
		sleep(2);
		kill(getppid(), SIGALRM);
	} else {
		printf("Parent waiting for alarm\n");
		pause();
		printf("Parent process received alarm sent from child process\n");
	}

	return EXIT_SUCCESS;

}
