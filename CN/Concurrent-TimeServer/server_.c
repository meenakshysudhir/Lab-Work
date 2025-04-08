#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(void){
    int sockID = socket(AF_INET,SOCK_STREAM,0);
    if(sockID < 0){
        perror("Socket Creation Error");
        exit(1);
    }
    struct sockaddr_in serverAddr,clientAddr;
    socklen_t addr_size;
    pid_t pid;
    
    memset(&serverAddr,'\0',sizeof(serverAddr));
    serverAddr.sin_family =  AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8888);
    if(bind(sockID,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0){
        perror("Bind Error");
        exit(1);
    }
    listen(sockID,10);
    printf("Server Listening.........\n");
    int clientCount = 0;
    char buffer[1024];
    addr_size = sizeof(clientAddr);
    while(1){
        int csockID = accept(sockID,(struct sockaddr*)&clientAddr,&addr_size);        
        bzero(buffer,1024);
        recv(csockID,buffer,1024,0);
        if(strcmp(buffer,"time") == 0){
            time_t t = time(NULL);
            struct tm* tm = localtime(&t);
            char time_str[1024];
            strftime(time_str,1024,"%Y-%m-%d %H:%M:%S",tm);
            send(csockID,time_str,1024,0);
        }
        else{
            char* msg = "Unknown command";
            send(csockID,msg,strlen(msg),0);
        }
    close(csockID);
    }

}
