#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define packetCount 10
int main(void){
    int rate,op,remainingSize = 0,bucketSize;
    int packets[packetCount];

    for(int i = 0; i < packetCount;i++){
        packets[i] = (rand() % 4 + 1) * 10;
       
    }
    printf("Enter the output rate : ");
    scanf("%d",&rate);
    printf("Enter the bucket size : ");
    scanf("%d",&bucketSize);
    int i = 0;
    while(i < packetCount || remainingSize > 0){
        if(i < packetCount){
            if(packets[i] + remainingSize > bucketSize){
                printf("Exceeding bucket size\n");
            }
            else{
                remainingSize += packets[i];
                printf("Packet size to be transmitted : %d\n",packets[i]);
                printf("Bytes to be transmitted : %d\n",remainingSize);
            }
            i++;
        }
       // printf("remaining size : %d\n",remainingSize);
        int timetoTransmit = (rand() % 3 + 1) * 10;
        printf("Transmission time : %d\n",timetoTransmit);
        int clk = 10;
        for(int clk = 10; clk <= timetoTransmit;clk -=10){
            sleep(1);
            if(remainingSize){
                if(remainingSize <= rate){
                    op = remainingSize;
                    remainingSize = 0;
                }
                else{
                    op = rate;
                    remainingSize -= rate;
                }
                printf("Byte %d transmitted\n",op);
            }
            else{
                printf("No bytes to transmitted\n");
                break;
            }
        }
    }
}
