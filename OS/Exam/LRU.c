#include <stdio.h>

int Q[100], refString[100], dist[30], size, n, occupancy = 0, hit = 0;
int front = -1, rear = -1;
int checkVal(int val);
void enqueue(int val);
void printFrames(int occupancy);
int main(void)
{
    printf("Enter the number of pages in reference string : ");
    scanf("%d", &n);
    printf("Enter the frame size : ");
    scanf("%d", &size);
    printf("Enter the reference string : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &refString[i]);
    }
    for (int i = 0; i < n; i++)
    {
        int val = refString[i];
        if (checkVal(val))
        {
            hit++;
            printf("____\n");
        }
        else
        {
            if (occupancy < size)
            {
                enqueue(val);
                occupancy++;
                printFrames(occupancy);
            }
            else // Full occupancy , i.e., size
            {
                for (int j = 0; j < size; j++)
                {
                    dist[j] = 0;
                    for (int k = i - 1; k >= 0; k--)
                    {
                        dist[j]++;
                        if (Q[j] == refString[k])
                        {
                            break;
                        }
                    }
                }
                int max = 0;
                for (int l = 1; l < size; l++)
                {
                    if (dist[max] < dist[l])
                    {
                        max = l;
                    }
                }
                Q[max] = val;
                printFrames(size);
            }
        }
    }
    printf("No. of page hits : %d\n", hit);
    printf("No. of page faults : %d\n", n - hit);
}
int checkVal(int val)
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
void enqueue(int item)
{
    if (front == -1 && rear == -1)
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
void printFrames(int occupancy)
{
    for (int i = 0; i < occupancy; i++)
    {
        printf("%d\t", Q[i]);
    }
    printf("\n");
}