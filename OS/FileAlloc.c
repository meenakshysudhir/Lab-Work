#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int disk[100] = {0}, n, fno = 1;

struct linkedDisk
{
    int occ;
    struct linkedDisk *child;
} *ldisk[30];

void seq(int);
void linkedlist(int);
int main(void)
{
    for (int i = 0; i < 30; i++)
    {
        ldisk[i] = (struct linkedDisk *)malloc(sizeof(struct linkedDisk));
        ldisk[i]->occ = 0;
        ldisk[i]->child = NULL;
    }
    int ch, strt;
    srand(time(0));
    while (1)
    {
        printf("\n1 - Sequential allocation\n2 - Linked allocation\n3 - Break\nChoice : ");
        scanf("%d", &ch);
        if (ch == 1)
        {
            printf("\nSequthe starting address and length of the file : ");
            scanf("%d%d", &strt, &n);
            if (strt > 100 || (strt + n) > 100 || strt < 0)
            {
                printf("Cannot be allocated sequentially\n");
            }
            else
            {
                seq(strt);
            }
        }
        else if (ch == 2)
        {
            printf("Enter the starting address and the length of the file : ");
            scanf("%d%d", &strt, &n);
            if (ldisk[strt]->occ != 0)
            {
                printf("Starting block already occupied\n");
            }
            else
            {
                linkedlist(strt);
            }
        }
        else if (ch == 3)
        {
            break;
        }
        else
        {
            printf("Invalid entry! Try again\n");
        }
    }
}
void seq(int strt)
{
    int flag = 0;
    for (int i = strt; i < (strt + n); i++)
    {
        if (disk[i] != 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        printf("Not enough contingous space for allocation File %d\n", fno);
        return;
    }
    if (flag == 0)
    {
        printf("\nFile %d allocated at : ", fno);
        for (int i = strt; i < (strt + n) && i < 100; i++)
        {
            disk[i] = 1;
            printf("Block%d\t", i);
        }
        fno++;
    }
}
void linkedlist(int strt)
{

    int freeblock = 0;
    for (int i = 0; i < 30; i++)
    {
        if (ldisk[i]->occ == 0)
        {
            freeblock++;
        }
    }
    if (freeblock < n)
    {
        printf("Not enough free blocks\n");
        return;
    }
    else
    {
        printf("Required no. of free blocks available\n");
        printf("\nLinked list allocation : \n");
    }

    int temp = n;
    ldisk[strt]->occ = strt;
    struct linkedDisk *prev = ldisk[strt];
    temp--;
    int lower = 0, upper = 30;
    while (temp > 0)
    {
        int number = (rand() % (upper - lower + 1)) + lower;
        // printf("\n%d \n", number);
        if (ldisk[number]->occ == 0)
        {
            ldisk[number]->occ = number;
            prev->child = ldisk[number];
            ldisk[number]->child = NULL;
            prev = ldisk[number];
            temp--;
            // printf("Block%d  ->  ", number);
        }
    }
    struct linkedDisk *newtemp = ldisk[strt];
    while (newtemp->child != NULL)
    {
        printf("Block %d -> ", newtemp->occ);
        newtemp = newtemp->child;
    }
    printf("Block %d -> ", newtemp->occ);
}