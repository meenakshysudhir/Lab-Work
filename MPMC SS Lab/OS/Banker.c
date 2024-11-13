#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
struct Process
{
    int pid;
    int ALLOC[MAX_SIZE];
    int MAX[MAX_SIZE];
    int NEED[MAX_SIZE];
    int finish;
} process[MAX_SIZE];

struct Other
{
    int AVAIL[MAX_SIZE];
    int WORK[MAX_SIZE];
} other;

void displayAlloc(int, int);
void displayMax(int, int);
void displayNeed(int, int);
void displayAvail(int);
int main(void)
{
    int np, nr, completed = 0;
    printf("Enter the no. of process and no. of resources : ");
    scanf("%d%d", &np, &nr);
    printf("Enter the Allocation Matrix : \n\t");

    // INPUT FOR ALLOCATION MATRIX

    for (int i = 0; i < nr; i++)
    {
        printf("R%d\t", i + 1);
    }
    for (int i = 0; i < np; i++)
    {
        printf("\nP%d\t", i + 1);
        process[i].pid = i + 1;
        process[i].finish = 0;
        for (int j = 0; j < nr; j++)
        {
            scanf("%d", &process[i].ALLOC[j]);
        }
    }

    // INPUT FOR MAX MATRIX

    printf("Enter the MAX Matrix : \n\t");
    for (int i = 0; i < nr; i++)
    {
        printf("R%d\t", i + 1);
    }
    for (int i = 0; i < np; i++)
    {
        printf("\nP%d\t", i + 1);
        for (int j = 0; j < nr; j++)
        {
            scanf("%d", &process[i].MAX[j]);
        }
    }

    // INPUT FOR AVAILABLE AND WORK MATRIX
    printf("\nEnter the available matrix\n");
    for (int i = 0; i < nr; i++)
    {
        printf("R%d\t", i + 1);
    }
    printf("\n");
    for (int i = 0; i < nr; i++)
    {
        scanf("%d", &other.AVAIL[i]);
        other.WORK[i] = other.AVAIL[i];
    }

    // CALCULATION OF NEED MATRIX

    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < nr; j++)
        {
            process[i].NEED[j] = process[i].MAX[j] - process[i].ALLOC[j];
        }
    }
    displayNeed(np, nr);
    printf("Sequence : ");
    while (completed != np)
    {
        int i = 0, flag;
        while (i < np)
        {
            flag = 0;
            if (process[i].finish == 0)
            {
                for (int j = 0; j < nr; j++)
                {
                    if (process[i].NEED[j] > other.WORK[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("P%d\t", process[i].pid);
                    process[i].finish = 1;
                    completed++;
                    for (int j = 0; j < nr; j++)
                    {
                        other.WORK[j] += process[i].ALLOC[j];
                    }
                }
            }
            i++;
        }
    }

    // displayAlloc(np, nr);
    // displayMax(np, nr);

    // displayAvail(np);
}

void displayAlloc(int np, int nr)
{
    // DISPLAY ALLOCATION MATRIX
    printf("\n_________________________________________________________________________________\n");
    printf("ALLOC MATRIX\n");
    for (int i = 0; i < nr; i++)
    {
        printf("R%d\t", i + 1);
    }
    printf("\n");
    for (int i = 0; i < np; i++)
    {
        printf("P%d\t", process[i].pid);
        for (int j = 0; j < nr; j++)
        {
            printf("%d\t", process[i].ALLOC[j]);
        }
        printf("\n");
    }
}

void displayMax(int nr, int np)
{
    // DISPLAY ALLOCATION MATRIX
    printf("\nMAX MATRIX\n");
    for (int i = 0; i < np; i++)
    {
        printf("P%d\t", process[i].pid);
        for (int j = 0; j < nr; j++)
        {
            printf("%d\t", process[i].MAX[j]);
        }
        printf("\n");
    }
}
void displayNeed(int np, int nr)
{
    // DISPLAY ALLOCATION MATRIX
    printf("\nNEED MATRIX\n");
    for (int i = 0; i < np; i++)
    {
        printf("P%d\t", process[i].pid);
        for (int j = 0; j < nr; j++)
        {
            printf("%d\t", process[i].NEED[j]);
        }
        printf("\n");
    }
}
void displayAvail(int np)
{
    printf("\nAVAIL MATRIX\n");
    for (int i = 0; i < np; i++)
    {
        printf("%d\t", other.AVAIL[i]);
    }
}