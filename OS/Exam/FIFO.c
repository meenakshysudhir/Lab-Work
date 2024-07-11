#include <stdio.h>
int ref_size, size, hit = 0, occupancy = 0;
int front = -1, rear = -1;
int ref[100], Q[100];
int valExists(int val);
void enqueue(int item);
void printFrames(int num);
int main(void)
{

    printf("Enter the string size :");
    scanf("%d", &ref_size);
    for (int i = 0; i < ref_size; i++)
    {
        scanf("%d", &ref[i]);
    }
    printf("Enter the frame size : ");
    scanf("%d", &size);
    for (int i = 0; i < ref_size; i++)
    {
        int val = ref[i];
        if (valExists(val))
        {
            hit++;
            printf("___\n");
        }
        else
        {
            if (occupancy < size)
            {
                enqueue(val);
                occupancy++;
                printFrames(occupancy);
            }
            else
            {
                enqueue(val);
                printFrames(size);
            }
        }
    }
    printf("No of page hits : %d\n", hit);
    printf("No. of Page miss : %d\n", ref_size - hit);
}
int valExists(int val)
{
    for (int i = 0; i < occupancy; i++)
    {
        if (Q[i] == val)
        {
            return 1;
        }
    }
    return 0;
}
void printFrames(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("%d\t", Q[i]);
    }
    printf("\n");
}
void enqueue(int item)
{
    if (front == -1 || rear == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % size;
    }
    Q[rear] = item;
}