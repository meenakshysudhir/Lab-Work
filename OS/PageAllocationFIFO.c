#include<stdio.h>
#define MAX_SIZE 15

int ref[MAX_SIZE],Q[MAX_SIZE];
int capacity,occupancy,size,hit = 0, occupancy = 0;
int front = -1, rear = -1;
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
                // Q[occupancy] = val;
                // occupancy++;
                enqueue(val,capacity);
                occupancy++;
                printFrame(occupancy);
            }
            else{
                enqueue(val,capacity);
                printFrame(capacity);

            }            
        }
    }
    printf("No. of page hits : %d\n",hit);
    int page_fault = size - hit;
    printf("No. of page faults : %d\n", page_fault);   

}