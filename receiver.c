#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH1 "./myfifo1"
#define FIFO_PATH2 "./myfifo2"
#define size 100

void to_uppercase(char *str){
	for(int i=0; str[i]; i++){
		str[i] = toupper(str[i]);
	}
}


int main(){
	char msg[size], subStr[size];
	int start, num_chars;

	int fd1 = open(FIFO_PATH1, O_RDONLY);
	read(fd1, msg, size);
	read(fd1, &start, sizeof(start));
	read(fd1, &num_chars, sizeof(num_chars));
	close(fd1);
	
	printf("%s\n", msg);
	printf("%d %d", start, num_chars);

	strncpy(subStr, msg+start, num_chars);
	subStr[num_chars] = '\0';

	to_uppercase(subStr);

	int fd2 = open(FIFO_PATH2, O_WRONLY);
    write(fd2, subStr, strlen(subStr) + 1);
    close(fd2);

    return 0;
}

