#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#define size 100

void main(){
  char msg1[size], msg2[size], msg[size];
  
  printf("Inside Process - 2 (PID - %d).......\n",getpid());
  printf("\nReceiving Message from Process -1......\n");

  int fd1 = open("./myfifo1", O_RDONLY);
  read(fd1, msg1, size);
  read(fd1, msg2, size);
  printf("Message-1 : %s\n",msg1);
  printf("Message-2 : %s\n",msg2);

  if(strcmp(msg1, msg2) == 0){
    strcpy(msg, "SAME");
  }
  else{
    strcpy(msg, "NOT SAME");
  }

  int fd2 = open("./myfifo2", O_WRONLY);
  printf("\nSending message to Process - 1.......\n");
  write(fd2, msg, sizeof(msg));
  close(fd1);
  close(fd2);

  printf("\nTerminating Process -2......\n\n");
}
