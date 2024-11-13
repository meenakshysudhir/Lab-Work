#include <stdio.h>
#include <stdlib.h>
void FCFS(int seq[10], int head, int n)
{
    int seek_count = 0, prev;
    printf("\n%d\t", head);
    prev = head;
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", seq[i]);
        seek_count += abs(prev - seq[i]);
        prev = seq[i];
    }
    printf("\nSeek count : %d", seek_count);
}
void sort(int seq[10], int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (seq[j] > seq[j + 1])
            {
                temp = seq[j];
                seq[j] = seq[j + 1];
                seq[j + 1] = temp;
            }
        }
    }
}
void SCAN(int r[10], int rc, int l[10], int lc, int begin, int end, int head)
{

    int choice, prev, seek_count = 0;
    printf("1 to move left\n2 to move right\nChoice : ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Towards the left : ");
        printf("%d\t", head);
        prev = head;
        for (int i = lc - 1; i >= 0; i--)
        {
            printf("%d\t", l[i]);
            seek_count += abs(l[i] - prev);
            prev = l[i];
        }
        printf("%d\t", begin);
        seek_count += abs(prev - begin);
        prev = begin;
        for (int i = 0; i < rc; i++)
        {
            printf("%d\t", r[i]);
            seek_count += abs(r[i] - prev);
            prev = r[i];
        }
        printf("\nSeek Count  : %d\n", seek_count);
    }
    else if (choice == 2)
    {
        printf("Towards the right : ");
        printf("%d\t", head);
        prev = head;
        for (int i = 0; i < rc; i++)
        {
            printf("%d\t", r[i]);
            seek_count += abs(r[i] - prev);
            prev = r[i];
        }
        printf("%d\t", end);
        seek_count += abs(end - prev);
        prev = end;
        for (int i = lc - 1; i >= 0; i--)
        {
            printf("%d\t", l[i]);
            seek_count += abs(l[i] - prev);
            prev = l[i];
        }
        printf("\nSeek Count  : %d\n", seek_count);
    }
    else
    {
        printf("Invalid choice \n");
    }
}
int main(void)
{
    int ch, n, head;
    int seq[10] = {176, 79, 34, 60, 92, 11, 41, 114};
    n = 8;
    printf("Enter 1 for FCFS\nEnter 2 for SCAN\nEnter 3 for C-SCAN\nEnter your choice : ");
    scanf("%d", &ch);
    printf("Enter the head : ");
    scanf("%d", &head);
    if (ch == 1)
    {
        FCFS(seq[10], head, n);
    }
    else if (ch == 2)
    {
        int r[10], l[10];
        int begin, end, lc = 0, rc = 0;
        printf("Enter the ends of the cylinder : ");
        scanf("%d%d", &begin, &end);
        for (int i = 0; i < n; i++)
        {
            if (seq[i] > head)
            {
                r[rc++] = seq[i];
            }
            else
            {
                l[lc++] = seq[i];
            }
        }
        sort(r, rc);
        sort(l, lc);
        SCAN(r, rc, l, lc, begin, end, head);
    }
}
