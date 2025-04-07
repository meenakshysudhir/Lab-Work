#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <stdlib.h>
#define packetCount 5
#define windowSize 3
#define timeoutVal 5
typedef struct packet{
    int id;
    int sent;
} Packet;

Packet packets[packetCount];
pthread_t thread[packetCount], receiveThread;
int sockID;
struct sockaddr_in addr;
socklen_t addr_size;
int windowStart,windowEnd,nextToSend;

void *sendPacket(void *sendPacket){
        Packet *packet = (Packet*)sendPacket;
        char buffer[1024];
        while(packet -> sent == 0){
            printf("Client : Sending packet %d\n",packet -> id);
            bzero(buffer,1024);
            sprintf(buffer,"%d",packet->id);

            sendto(sockID,buffer,1024,0,(struct sockaddr*)&addr,sizeof(addr));    
            sleep(timeoutVal);
            if(packet->sent == 0){
                printf("Timeout for packet %d\n",packet->id);
            }
        }
}

void *receivePacket(){
    addr_size = sizeof(addr);
    char buffer[1024];
    while(1){
        bzero(buffer,1024);
        recvfrom(sockID,buffer,1024,0,(struct sockaddr*)&addr,&addr_size);
        char msg[1024];
        int packetID;
        sscanf(buffer,"%s%d",msg,&packetID);
        if(strcmp(msg,"NACK") == 0){
            printf("Client: Recieved Negative Acknowledgement for packet %d\nSending packet again\n\n",packetID);
            pthread_cancel(thread[packetID - 1]);
            pthread_create(&thread[packetID - 1],NULL,sendPacket,(void*)&packets[packetID - 1]);
        }
        else if(strcmp(msg,"ACK") == 0){
            printf("Client: Acknowledgement recieved for packet %d\n",packetID);
            packets[packetID - 1].sent = 1;
            if(windowStart == (packetID -1)){
                while(packets[windowStart].sent == 1){
                    windowStart++;
                    if(windowEnd < packetCount){
                        windowEnd++;
                    }
                }
            }
        }
        else {
        printf("Invalid message\n");
        }
    }
}

int main(void){
    for(int i = 0;i < packetCount;i++){
        packets[i].id = i+1;
        packets[i].sent = 0;
    }
    char buffer[1024];
    sockID = socket(AF_INET,SOCK_DGRAM,0);
    if(sockID < 0){
        perror("Socket Error");
        exit(1);
    }
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6626);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    pthread_create(&receiveThread,NULL,receivePacket,NULL);
    windowStart = 0;
    windowEnd = windowStart + windowSize -1; // 0 to 2

    for(int i = windowStart; i <= windowEnd;i++){
        pthread_create(&thread[i],NULL,sendPacket,(void*)&packets[i]);
    }
    int nexttoSend = windowEnd + 1;
    while(windowStart != windowEnd){
        if(nextToSend  <= windowEnd && nextToSend <= packetCount){
            pthread_create(&thread[nexttoSend],NULL,sendPacket,(void*)&packets[nextToSend]);
            nextToSend++;
        }
    }
    close(sockID);

}

