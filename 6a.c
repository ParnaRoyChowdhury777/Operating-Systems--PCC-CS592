#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define size 100

void main(){
  int p[2];

  if(pipe(p) == -1){
    printf("\nERROR: Pipe Failed!\n");
    exit(0);
  }
  else {
    int pid = fork();
    if(pid < 0){
      printf("\nERROR: Fork Failed!\n");
      exit(0);
    }
    else if(pid == 0){
      char msg[size];
      printf("Taking input from child(PID - %d).......\n",getpid());
      printf("Enter the message : ");
      fgets(msg, sizeof(msg), stdin);
      msg[strlen(msg) - 1] = '\0';
      write(p[1], msg, strlen(msg)+1);
    }
    else{
      sleep(10);
      printf("\nParent(PID - %d) is receiving message from child.....\n",getpid());
      char msg[size];
      read(p[0], msg, size);
      printf("The message is : \"%s\"\n",msg);
    }
  }
}
