#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FIFO_PATH1 "./myfifo1"
#define FIFO_PATH2 "./myfifo2"
#define size 100

int main(){
	mkfifo(FIFO_PATH1, 0666);
	mkfifo(FIFO_PATH2, 0666);

	char input[size], res[size];
	int start, num_chars;

	printf("Enter a string in lowercase: ");
	fgets(input, size, stdin);
	input[strlen(input) - 1] = '\0';

	printf("Enter the starting index: ");
	scanf("%d", &start);

	printf("Enter the number of characters: ");
	scanf("%d", &num_chars);

	int fd1 = open(FIFO_PATH1, O_WRONLY);
	write(fd1, input, sizeof(input));
	write(fd1, &start, sizeof(start));
	write(fd1, &num_chars, sizeof(num_chars));
	close(fd1);

	int fd2 = open(FIFO_PATH2, O_RDONLY);
	read(fd2, res, size);
	close(fd2);

	printf("Received transformed substring: %s\n", res);
	
	return 0;
}

