#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig) {
	if (sig == SIGCONT) {
		printf("\nParent sent a signal\n");
	}
}

int main() {

	signal(SIGCONT, handler);

	int pid = fork();

	if (pid == -1) {
		fprintf(stderr, "ERROR\n");
		return 1;
	}

	if (pid == 0) {
		while (1) {
			pause();
			printf("Child has received signal\n");
			int n;
			printf("Enter the year: ");
			scanf("%d", &n);
			if (n%4==0 && n%100!=0 || n%400==0)
				printf("Leap year\n");
			else
				printf("Not a leap year\n");
		}
	} else {
		while (1) {
			sleep(5);
			kill(pid, SIGCONT);
		}
	}

}
