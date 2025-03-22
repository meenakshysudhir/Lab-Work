#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
    int a[5] = {2,4,1,7,3};
    int n = fork();
    
    if(n > 0){
        int sumE = 0;
        for(int i = 0; i < 5;i++){
            if(a[i]%2 == 0)sumE+= a[i];
        }
        printf("Inside parent process\nSum of Even numbers : %d\n",sumE);
    }
    else{
        int sumO = 0; 
        printf("Inside the child process\n");
        for(int i = 0; i < 5;i++){
            if(a[i]%2 == 1){
                sumO+= a[i];
            }
        }
        printf("Sum of odd numbers: %d\n",sumO);
    }
}
