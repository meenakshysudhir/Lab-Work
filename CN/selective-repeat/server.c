#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define packetCount 5

typedef struct packet{
    int id;
    int received;
}Packet;
Packet packets[packetCount];
int main(void){
    
    for(int i = 0; i < packetCount;i++){
        packets[i].id = i+ 1;
        packets[i].received = 0;
    }

    struct sockaddr_in serverAddr,clientAddr;
    socklen_t addr_size;

    int sockID = socket(AF_INET,SOCK_DGRAM,0);
    if(sockID < 0){
        perror("Socket creation error");
        exit(1);
    }
    memset(&serverAddr,'\0',sizeof(serverAddr));
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6626);
    
    int n = bind(sockID,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if(n < 0){
        perror("Bind Error");
        exit(1);
    }
    
    char buffer[1024];
    while(1){
        bzero(buffer,1024);
        addr_size = sizeof(clientAddr);
        recvfrom(sockID,buffer,1024,0,(struct sockaddr*)&clientAddr,&addr_size);
        sleep(1);

        int packet = atoi(buffer);
        if(packets[packet - 1].received == 1 || rand() % 5 == 0)
            continue;
        else if(rand() % 4 == 0){
            printf("Server : Corrupted package received %s\nSending NACK\n\n",buffer);
            bzero(buffer,1024);
            sprintf(buffer,"NACK %d",packet);
            sendto(sockID,buffer,1024,0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
        }
        else{
            printf("Server : Recieved packet %s\nSending Acknowledgement\n",buffer);
            sprintf(buffer,"ACK %d",packet);
            sendto(sockID,buffer,1024,0,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
            packets[packet - 1].received = 1;
        }
    }
    
}
