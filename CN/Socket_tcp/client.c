#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void){
    char* ip = "127.0.0.1";
    int port = 5566;
    int sock;
    struct sockaddr_in  addr;
    char buffer[1024];
    int n;
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("Socket creation error");
        exit(1);
    }
    printf("Socket created\n");
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);   
    connect(sock,(struct sockaddr*)&addr,sizeof(addr));
    printf("Connected to the server\n");
    bzero(buffer,1024);
    strcpy(buffer,"HELLO FROM CLIENT");
    printf("Client : %s\n",buffer);
    send(sock,buffer,strlen(buffer),0);
    bzero(buffer,1024);
    recv(sock,buffer,sizeof(buffer),0);
    printf("Server : %s\n",buffer);
    close(sock);
    printf("Disconnected from the server\n");
    
}
