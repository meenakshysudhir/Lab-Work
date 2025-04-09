#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void){
    int sockID = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;

    memset(&serverAddr,'\0',sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(7007);

    if(bind(sockID,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0){
        perror("Bind error");
        exit(1);
    }
    //printf("Bind Error");
    listen(sockID,10);
    printf("Listening.....\n");
    char buffer[1024];
    addr_size = sizeof(clientAddr);
    int csockID = accept(sockID,(struct sockaddr*)&clientAddr,&addr_size);
    printf("Client connected\n");

    while(1){
        
        recv(csockID,buffer,1024,0);
        printf("Server : Packet recieved %s\n",buffer);
        sleep(1);
        printf("Server : Sending acknowledgement from packet %s\n",buffer);
        send(csockID,buffer,1024,0);
    }
}
