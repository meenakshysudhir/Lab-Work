#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct node {
    int dist[20];
    int from [20];
} route[10];
int main(void){
    printf("Enter the no. of nodes : ");
    int num;
    scanf("%d",&num);
    int dm[20][20];
    printf("Enter the distance matrix : \n");
    for(int i = 0; i < num;i++){
        for(int j = 0;j < num;j++){
            
            scanf("%d",&dm[i][j]);
            //dm[i][i] = 0;
            route[i].dist[j] = dm[i][j];
            route[i].from[j] = j;
        }
    }
    int flag;
    do{
        flag  = 0;
        for(int i = 0;i < num;i++){
            for(int j = 0;j < num;j++){
                for(int k = 0;k < num;k++){
                    if(route[i].dist[j] > route[i].dist[k] + route[k].dist[j]){
                        route[i].dist[j] = route[i].dist[k] + route[k].dist[j];
                        route[i].from[j] = route[i].from[k];
                        flag = 1;
                    }
                }
            }
        }
    }while(flag);
    printf("Dest\tNextHop\tDist\n");
    for(int i =0;i < num;i++){
        printf("Routing table for %d\n",i);
        for(int j = 0;j < num;j++){
                printf("%c\t%c\t%d\n",j+65,route[i].from[j] + 65,route[i].dist[j]);
        }
    }
}
