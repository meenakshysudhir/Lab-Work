#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(void){
    char* ip = "127.0.0.1";
    int port = 5533;
    int b;

    int sockID = socket(AF_INET,SOCK_DGRAM,0);
    if(sockID < 0){
        perror("Socket creation error");
        exit(1);
    }

    struct sockaddr_in serverAddr,clientAddr;
    socklen_t len ;
    char buffer[1024];
    int recd[10];
    for(int i = 0; i < 10;i++){
        recd[i] = -1;
    }
    memset(&serverAddr,'\0',sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    
    int n = bind(sockID,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if(n < 0){
        perror("Bind Error");
        exit(1);
    }
    while(1){
        bzero(buffer,1024);
        len = sizeof(clientAddr);
        recvfrom(sockID,buffer,1024,0,(struct sockaddr*)&clientAddr,&len);
        b = atoi(buffer);
        if(recd[b] == b){
            printf("Server : Duplicate packet %s\n",buffer);
        }
        else {
            recd[b] = b;
            printf("Server : Recieved packet %s\n",buffer);
        }
        sleep(1);
        if(rand() % 2 == 0){
            printf("Sendinig acknowledgement for packet %s\n",buffer);
            sendto(sockID,buffer,1024,0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
        }
    }
}
