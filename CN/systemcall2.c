#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    int n = fork();
    int status;
    if(n == -1){
        printf("Bad fork\n");
        exit(1);
    }
    else if(n == 0)
    {
        printf("Display as child process\n");
    }
    else {
        wait(&status);
        printf("Display as child process\n");
    }
}
