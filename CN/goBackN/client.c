#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define timeoutVal 5
#define packetCount 5
#define windowSize 3

void sendPackets(int* sockID,struct sockaddr_in addr,int packets[],int windowStart,int windowEnd){
    char buffer[1024];
    while(windowStart < windowEnd){
        bzero(buffer,1024);
        sprintf(buffer,"%d",packets[windowStart]);
        printf("Client : Sending packet %s\n",buffer);
        sendto(*sockID,buffer,1024,0,(struct sockaddr*)&addr,sizeof(addr));
        windowStart++;
    }
}

int main(void){
    char* ip = "127.0.0.1";
    int port = 5533;

    pthread_t timeoutThread;
    int sockID;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    
    sockID = socket(AF_INET,SOCK_DGRAM,0);
    if(sockID < 0){
        perror("Socket Error");
        exit(1);
    }
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    int packets[packetCount];
    for(int i = 0;i < packetCount;i++){
        packets[i] = i;
    }

    int windowStart = 0;
    int windowEnd  = windowStart + windowSize;

    sendPackets(&sockID,addr,packets,windowStart,windowEnd);
    int flag = 1;
    while(windowStart != windowEnd){
        bzero(buffer,1024);
        addr_size = sizeof(addr);

        struct timeval timeout;
        timeout.tv_sec = timeoutVal;
        timeout.tv_usec = 0;    

        if(setsockopt(sockID,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout)) < 0){
            printf("Socket timeset error\n");
        }
        else{
            bzero(buffer,1024);
            addr_size = sizeof(addr);
            int rec = recvfrom(sockID,buffer,1024,0,(struct sockaddr*)&addr,&addr_size);
            if(rec < 0){
                printf("Client : Timeout Error |  Sending window again\n");
                sendPackets(&sockID,addr,packets,windowStart,windowEnd);
            }
            else {
                printf("Client : Recieved Acknowledgement for packet %s\n",buffer);
                if(atoi(buffer) != windowStart){
                    printf("Client : Wrong acknowdgement | Sending window again Window Start = %d\n\n",windowStart);
                    sendPackets(&sockID,addr,packets,windowStart,windowEnd);
                }
                else {
                //Correct aknowledgment
                    windowStart++;
                    if(windowEnd< packetCount) windowEnd++;
                    if(windowStart != windowEnd) {
                        bzero(buffer,1024);
                        if(flag == 1){
                            sprintf(buffer,"%d",packets[windowEnd - 1]);
                            printf("Client : Sending packet %s\n",buffer);
                            sendto(sockID,buffer,1024,0,(struct sockaddr*)&addr,sizeof(addr));
                        }
                        if(windowEnd  ==  packetCount){
                            flag = 0;
                        }
                    }
                }
            }
        }
        sleep(1);
    }
}
