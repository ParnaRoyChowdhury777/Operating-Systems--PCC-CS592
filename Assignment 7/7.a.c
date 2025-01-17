#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
	printf("\n%d: Signal handled\n", sig);
	exit(0);
}

int main(int argc, char *argv[]) {
	signal(SIGINT, handler);
	while (1) {
		printf("Waiting for signal\n");
		sleep(1);
	}
}

