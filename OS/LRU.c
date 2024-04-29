#include<stdio.h>
#define MAX_SIZE 15

int ref[MAX_SIZE],Q[MAX_SIZE];
int capacity,occupancy,size,hit = 0, occupancy = 0;
int front = -1, rear = -1;
int dist[MAX_SIZE];
int checkval(int value,int occupancy)
{
    for(int i = 0;i < occupancy ; i++)
    {
        if(Q[i] == value)
        {
            return 1;
        }
    }
    return 0;
}
void printFrame(int occupancy)
{
    for(int i = 0; i < occupancy; i++)
    {
        printf("%d\t",Q[i]);
    }
    printf("\n");
}
void enqueue(int value, int capacity)
{
    if(front == -1 && rear == -112)
    {
        front = rear = 0;
    }
    else{
        rear = (rear + 1) % capacity;
    }
    Q[rear] = value;
}

int main(void)
{
    int max;
    printf("Enter the reference string size : ");
    scanf("%d",&size);
    printf("Enter the reference string :");
    for(int i = 0; i < size;i++)
    {
        scanf("%d",&ref[i]);
    }
    printf("Enter the number of frames : ");
    scanf("%d",&capacity);
    

    for(int i = 0; i < size; i++)
    {
        int val = ref[i];
        if(checkval(val,occupancy))
        {
            hit++;
            printf("__\n");
        }
        else
        {
            if(occupancy < capacity)
            {
                enqueue(val,capacity);
                occupancy++;
                printFrame(occupancy);
            }
            else{
                for(int j = 0; j < capacity; j++)
                {
                    dist[j] = 0;
                    for(int k = i- 1; k >= 0; k --)
                    {
                        dist[j] += 1;
                        if(Q[j] == ref[k])
                        {
                            break;
                        }
                    }
                    
                }
                max = 0;
                for(int l = 1; l < capacity;l++)
                {
                    if(dist[l] > dist[max])
                    {
                        max = l;
                    }

                }
                Q[max] = val;
                printFrame(capacity);
            }            
        }
    }
    printf("No. of page hits : %d\n",hit);
    int page_fault = size - hit;
    printf("No. of page faults : %d\n", page_fault);   

}