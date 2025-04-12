#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void){
    int sockID = socket(AF_INET,SOCK_STREAM,0);
    if(sockID < 0){
        perror("Sock Creation Error");
        exit(1);
    }
    printf("Socket created\n");
    int arr[7] ={-1,-1,-1,-1,-1,-1,-1};
    struct sockaddr_in serverAddr,clientAddr;
    socklen_t addr_size;
    memset(&serverAddr,'\0',sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8989);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sockID,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0){
        perror("Bind Error");
        exit(1);
    }
    listen(sockID,10);
    printf("Server Listening......\n");
    addr_size = sizeof(clientAddr);
    int csockID = accept(sockID,(struct sockaddr*)&clientAddr,&addr_size);
    char buffer[1024];
    int x = 1;
    while(1){
        bzero(buffer,1024);
        recv(csockID,buffer,1024,0);
        int flag = 0;
        if(atoi(buffer) == x && arr[atoi(buffer) - 1] != -1){
            printf("Server : Received packet %s\n",buffer);
            arr[atoi(buffer) - 1] = atoi(buffer) - 1;
        }   
        else if(arr[atoi(buffer) - 1] == (atoi(buffer) -1)){
            printf("Server : Duplicate packet %s received\n",buffer);
        }
        sleep(1);
        if(rand() % 2 == 0){
            printf("Server : Sending acknowledment for the packet %s\n",buffer);
            send(csockID,buffer,1024,0);
        }

    }
}
