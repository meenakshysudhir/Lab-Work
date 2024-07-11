#include <stdio.h>

int main(void)
{
    int r, p, alloc[50][50], need[50][50], max[50][50], avail[50], work[50], safeSeq[50], finish[50], count = 0, flag = 0;
    printf("No. of process and resources :  ");
    scanf("%d%d", &p, &r);
    printf("Allocation Matrix : \n");
    for (int i = 0; i < p; i++)
    {
        printf("P%d : ", i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Max Matrix : \n");
    for (int i = 0; i < p; i++)
    {
        printf("P%d : ", i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Available matrix : ");
    for (int i = 0; i < r; i++)
    {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }
    printf("Need Matrix : \n");
    for (int i = 0; i < p; i++)
    {
        printf("P%d : ", i);
        for (int j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < p; i++)
    {
        finish[i] = 0;
    }
    for (int k = 0; k < p; k++)
    {
        for (int i = 0; i < p; i++)
        {
            flag = 0;
            for (int j = 0; j < r; j++)
            {
                if (finish[i] != 0)
                {
                    if (need[i][j] > work[j]) // need <= work
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag == 0)
            {
                finish[i] = 1;
                for (int j = 0; j < r; j++)
                {
                    work[j] += alloc[i][j];
                }
                safeSeq[count++] = i;
            }
        }
    }
    flag = 0;
    for (int i = 0; i < p; i++)
    {
        if (finish[i] == 0)
        {

            printf("Deadlock detected\n");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("No deadlock detected\n");
        for (int i = 0; i < p; i++)
        {
            printf("%d\t", safeSeq[i]);
        }
    }
}