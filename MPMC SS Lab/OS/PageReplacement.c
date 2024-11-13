#include <stdio.h>
#define MAX_SIZE 100

int Q[MAX_SIZE];
int front = -1, rear = -1;
void enqueue(int val, int n)
{
    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        // printf("\t%d\t", val);
        rear = (rear + 1) % n;
    }
    Q[rear] = val;
}
void displayQ(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", Q[i]);
    }
    printf("\n");
}
int main(void)
{
    int arr[MAX_SIZE];
    int n, f, hit = 0;
    printf("Enter the number of pages and frames : ");
    scanf("%d%d", &n, &f);
    printf("\n%d %d\n", n, f);
    printf("Enter the sequence : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < f; i++)
    {
        Q[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int flag = 0;
        for (int j = 0; j < f; j++)
        {
            if (arr[i] == Q[j])
            {
                flag = 1;
                hit++;
                printf("HIT\n");
                break;
            }
        }
        if (flag == 0)
        {
            enqueue(arr[i], f);
            displayQ(f);
        }
    }
    printf("Page hit  : %d\n", hit);
    printf("Page Faults : %d\n", n - hit);
}