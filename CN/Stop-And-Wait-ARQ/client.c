#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#define timeoutValue 5
int main(void){
    int sockID = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    socklen_t addr_size;
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8989);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int n = connect(sockID,(struct sockaddr*)&addr,sizeof(addr));
    if(n < 0){\
        perror("Connection Error");
        exit(1);
    }
    printf("Connection Established\n");
    int packetCounter = 1;
    
    char buffer[1024];
    while(packetCounter <= 7){
        bzero(buffer,1024);
        sprintf(buffer,"%d",packetCounter);
        printf("Client : Sending packet %s\n",buffer);
        send(sockID,buffer,1024,0);

        bzero(buffer,1024);
        addr_size = sizeof(addr);
        struct timeval timeout;
        timeout.tv_sec = timeoutValue;
        timeout.tv_usec = 0;

        if(setsockopt(sockID,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout)) < 0){
            perror("Error\n");
        }
        else{
            bzero(buffer,1024);
            recv(sockID,buffer,1024,0);
            if(recv < 0){
                printf("Client : Timeout Error. Sending packet again\n");
            }
            else{
                if(atoi(buffer) == packetCounter){
                printf("Client : Received acknowledgment for packet %s\n",buffer);
                packetCounter++;
                }
            }

        }
        sleep(1);
    }
}
