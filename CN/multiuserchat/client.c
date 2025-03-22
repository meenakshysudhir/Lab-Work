#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <fcntl.h>

void *serverCommunication(void* sockID){
    int clientSocket = *((int *)sockID);
    while(1){
        char data[1024];
        bzero(data,1024);
        int read =  recv(clientSocket,data,sizeof(data),0);
        data[read] = '\0';
        printf("%s\n",data);
    }

}

int main(void){
    int clientSocket = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family =  AF_INET;
    serverAddr.sin_port = htons(8085);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(connect(clientSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) == -1){
        perror("Connection failed\n");
        exit(0);
    }
    printf("Connection established\n");
    pthread_t thread;
    pthread_create(&thread,NULL,serverCommunication,(void*)&clientSocket);
    while(1){
        char input[1024];
        scanf("%s",input);
        if(strcmp(input,"SEND") == 0){
            send(clientSocket,input,1024,0);
            scanf("%s",input);
            send(clientSocket,input,1024,0);
            scanf("%[^\n]",input);
            send(clientSocket,input,1024,0);
        }   
    }

}
