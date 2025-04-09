#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define packetCount 5
int main(void){

    int sockID = socket(AF_INET,SOCK_STREAM,0);
    if(sockID < 0){
        perror("Socket Error");
        exit(1);
    }
    struct sockaddr_in addr;
    socklen_t addr_size;
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7007);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int i = 0;
    int n = connect(sockID,(struct sockaddr*)&addr,sizeof(addr));
    while(i < packetCount){    
        if(n < 0){
            perror("Connect Error");
            exit(1);
        }     
        char buffer[1024];
        bzero(buffer,1024);
        sprintf(buffer,"%d",i);
        printf("Client : Sending packet %d to the server\n",i);
        send(sockID,buffer,1024,0);
        bzero(buffer,1024);
        recv(sockID,buffer,1024,0);
        printf("Client : Acknowledgement received for packet %s\n",buffer);
        sleep(1);
        i++;
        
    }
}
