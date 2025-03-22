#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>  
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/types.h>

    int clientCount = 0;
    typedef struct client{
        int index;
        int sockID;
        struct sockaddr_in clientAddr;
        int len;
    } client;

    client Client[1024];
    pthread_t thread[1024];

    void *clientCommunication(void* ClientDetail){
        struct client *clientDetail = (client*)ClientDetail;
        int index = clientDetail -> index;
        int clientSocket = clientDetail -> sockID;
        printf("Client %d connected\n",index+1);
    
    while(1){
        char buffer[1024];
        bzero(buffer,sizeof(buffer));   
        int read = recv(clientSocket,buffer,sizeof(buffer),0);
        buffer[read] = '\0';
        char output[1024];
        if(strcmp(buffer,"SEND") == 0){
            read = recv(clientSocket,buffer,1024,0);
            buffer[read] = '\0';
        }
        int id = atoi(buffer) - 1;

        for(int i = 0; i < clientCount;i++){
            if(i == id){
                continue;   
            }
            else {
                send(Client[i].sockID,buffer,1024,0);
            }
        }
    }
}

int main(void){
        int serverSocket = socket(PF_INET,SOCK_STREAM,0);
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port= htons(8085);
        serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
        if(bind(serverSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) == -1){
            perror("Bind error");
            exit(0);                
        }
        if(listen(serverSocket,1024) == -1){
            exit(0);
        }
        printf("Server listening on port 8085.....\n");
        while(1){
            Client[clientCount].sockID = accept(serverSocket,(struct sockaddr*)&Client[clientCount].clientAddr,&Client[clientCount].len);
            Client[clientCount].index = clientCount;    
            pthread_create(&thread[clientCount],NULL,clientCommunication,(void*)&Client[clientCount]);

            clientCount++;
        }
        for(int i = 0; i < clientCount;i++){
            pthread_join(thread[i],NULL);
        }

}

