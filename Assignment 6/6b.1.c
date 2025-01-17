//Named Pipe

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#define size 100

void main(){
  mkfifo("./myfifo1", 0666);
  mkfifo("./myfifo2", 0666);
  char msg1[size], msg2[size], msg[size];
  printf("Inside Process - 1(PId - %d)........\n\n",getpid());
  
  printf("Enter the message-1 : ");
  fgets(msg1, sizeof(msg1), stdin);
  msg1[strlen(msg1) - 1] = '\0';

  printf("Enter the message-2 : ");
  fgets(msg2, sizeof(msg2), stdin);
  msg2[strlen(msg2) - 1] = '\0';

  int fd1 = open("./myfifo1", O_WRONLY);
  printf("Sending messages to Process - 2......\n");
  write(fd1, msg1, sizeof(msg1));
  write(fd1, msg2, sizeof(msg2));

  printf("\nReceiving message from Process -2......\n");
  int fd2 = open("./myfifo2", O_RDONLY);
  read(fd2, msg, size);
  printf("The messages are \"%s\"\n",msg);
  close(fd1);
  close(fd2);
  printf("\nTerminating Process - 1......\n\n");
}
