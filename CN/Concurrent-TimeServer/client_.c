#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(void){
    int sockID = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    socklen_t addr_size;

    memset(&addr,'\0',sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8888);

    if(connect(sockID,(struct sockaddr*)&addr,sizeof(addr)) < 0){
        perror("Connection Error");
        exit(1);
    }
    printf("Connected to server\n");
    char buffer[1024];
    bzero(buffer,1024);
    strcpy(buffer,"time");
    send(sockID,buffer,1024,0);
    bzero(buffer,1024);
    recv(sockID,buffer,1024,0);
    printf("Server Time : %s\n",buffer);
    close(sockID);
}
