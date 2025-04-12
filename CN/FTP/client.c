#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(void){

    struct sockaddr_in addr;
    socklen_t addr_size;
    int sockID = socket(AF_INET,SOCK_STREAM,0);
    if(sockID < 0){
        perror("Sock creation error");
        exit(1);
    }
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1025);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockID,(struct sockaddr*)&addr,sizeof(addr)) < 0){
        perror("Connection error");
        exit(1);
    }
    FILE *fptr;
    char buffer[1024];
    char filename[100];
    int choice;
    while(1){
        printf("Enter 1 for file Upload(PUT)\nEnter 2 for file read(GET)\nEnter 3 to exit\nChoice : ");
        scanf("%d",&choice);

        switch(choice){
            case 2 :
                bzero(buffer,1024);
                strcpy(buffer,"GET");
                send(sockID,buffer,1024,0);
                bzero(buffer,1024);
                recv(sockID,buffer,1024,0);
                printf("PID : %s\n",buffer);
                bzero(buffer,1024);
                printf("Enter the name of the file to be downloaded : ");
                scanf("%s",filename);
                strcpy(buffer,filename);
                send(sockID,buffer,1024,0);
                bzero(buffer,1024);
                recv(sockID,buffer,1024,0);
                if(strcmp(buffer,"404") == 0){
                    printf("File %s not found\n",filename);
                }
                else if(strcmp(buffer,"200") == 0){
                    fptr = fopen(filename,"w");
                    while(1){
                        bzero(buffer,1024);
                        recv(sockID,buffer,1024,0);
                        if(strcmp(buffer,"END$") == 0){
                            break;
                        }  
                        printf("Buffer recieved : %s",buffer);
                        fprintf(fptr,"%s",buffer);

                    }
                    printf("File %s recieved\n",filename);
                }
                break;
            case 1:
                bzero(buffer,1024);
                strcpy(buffer,"PUT");
                send(sockID,buffer,1024,0);
                bzero(buffer,1024);
                printf("Enter the name of the file to be uploaded : ");
                scanf("%s",filename);
                strcpy(buffer,filename);
                send(sockID,buffer,1024,0);
                bzero(buffer,1024);
                FILE *fptr = fopen(filename,"r");
                if(!fptr){
                    perror("File not found");
                    exit(1);
                }
                fgets(buffer,1024,fptr);
                printf("Buffer : %s\n",buffer);
                send(sockID,buffer,1024,0);
                bzero(buffer,1024);
                strcpy(buffer,"END$");
                send(sockID,buffer,1024,0);
                bzero(buffer,1024);
                fclose(fptr);
                printf("File %s sent\n",filename);
                break;
            case 3 :
                printf("Exiting...\n");
                break;
        }
    }
}
