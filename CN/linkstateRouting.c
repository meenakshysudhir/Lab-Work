#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODES 10
#define INF 9999
bool visited[MAX_NODES];
int numNodes;
int graph[MAX_NODES][MAX_NODES];


void dijikstras(int startNode){
    
    int distance[MAX_NODES];
    int previous[MAX_NODES];
    for(int i = 0;i <numNodes;i++){
        distance[i] = INF;
        visited[i] = false;
    }
    distance[startNode] = 0;
    previous[startNode] = -1;
    for(int i = 0; i < numNodes-1;i++){
        int minDistance = INF;
        int minNode;
        for(int j = 0; j < numNodes;j++){
            if(!visited[j] && distance[j] < minDistance){
                minDistance = distance[j];
                minNode = j;
            }
        }
        visited[minNode] = true;
        for(int k = 0; k < numNodes;k++){
            if(!visited[k] && graph[minNode][k] && distance[minNode]+graph[minNode][k] < distance[k]){
                distance[k] = distance[minNode] + graph[minNode][k];
                //visited[k] = true;
                previous[k] = minNode;
            }
        }

    }
    printf("\nRouting Table for Node %d:\n",startNode);
    printf("Destination\tNext Hop\tCost\n");
    for(int k = 0; k < numNodes;k++){
        if(k != startNode){

            printf("%d\t\t%d\t\t%d\n",k,previous[k],distance[k]);
        }
    }
}
int main(){
    
    int links;
    printf("Enter the number of Nodes : ");
    scanf("%d",&numNodes);
    for(int i = 0; i < numNodes;i++){
        for(int j = 0;j < numNodes;j++){

            if(i == j){
                graph[i][j] == 0;
            }
          else{
                graph[i][j] = INF;
            }
        }
    }
    printf("Enter the number of Links : ");
    scanf("%d",&links);
    int s,d,c;
    for(int i = 0; i < links;i++){
        printf("Enter the source,dest,cost of %d :",i+1);
        scanf("%d%d%d",&s,&d,&c);
        graph[s][d] = c;
        graph[d][s] = c;
    }   
    for(int i = 0; i < numNodes;i++){
        dijikstras(i);
    }
   
}
