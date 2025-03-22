#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
    char s[100];
    printf("Enter the string : ");
    scanf("%s",s);
    int n = fork();
    if(n == -1){
        printf("Error forking\n");

    }
    else if(n == 0){
            printf("Child process:\n");
            int i = 0;
            char str[100];
            while(s[i]!= '\0'){
                str[i] = s[i] - 32;
                i++;
            }
            str[i]='\0';
            printf("%s",str);
    }
    else {
        printf("Parent process:\n");
        wait(NULL);
    }
}
