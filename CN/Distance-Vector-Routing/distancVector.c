#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

struct node{
    int dist[20];
    int from[20];
} route[20];
int main(void){
    int dm[20][20],n;
    printf("Enter the number of nodes : ");
    scanf("%d",&n);
    printf("Enter the distance matrix : ");
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            scanf("%d",&dm[i][j]);
            dm[i][i] = 0;
            route[i].dist[j] = dm[i][j];
            route[i].from[j] = j;
        }
    }
    int flag;
    do{
        flag = 0;
        for(int i = 0;i < n;i++){
            for(int j =0;j < n;j++){
                for(int k = 0;k < n;k++){
                    if(route[i].dist[j] > (route[i].dist[k] + route[k].dist[j])){
                        route[i].dist[j] = route[i].dist[k]+route[k].dist[j];
                        route[i].from[j] = route[i].from[k];
                        flag = 1;
                    }
                }
            }
        }
    } while(flag);

    for(int i = 0;i < n;i++){
        printf("Router infor for router %d\n",i+65);
        printf("Dest\tNextHop\tDist\n");
        for(int j = 0; j < n;j++){
            printf("%c\t%c\t%d\n",j+65,route[i].from[j] + 65,route[i].dist[j]);
        }
    }
}
