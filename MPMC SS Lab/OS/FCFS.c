#include <stdio.h>
#include <stdlib.h>

int tat[10], wt[10];

struct Process
{
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
} process[10];

int ct = 0;
float avg_wt = 0, avg_tat = 0;
void sort(struct Process pro[10], int n)
{
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i; j < n - i - 1; j++)
        {
            if (pro[j].at > pro[j + 1].at)
            {
                temp = pro[j];
                pro[j] = pro[j + 1];
                pro[j + 1] = temp;
            }
        }
    }
    // for (int i = 0; i < n; i++)
    // {
    // printf("P%d", process[i].at);
    // }
}
void FCFS(struct Process pro[10], int n)
{
    // printf("PROCESS\tAT\tBURST TIME\tTAT\tWT\n");
    printf("%d|", ct);
    for (int i = 0; i < n; i++)
    {
        ct += pro[i].bt;
        pro[i].tat = ct - pro[i].at;
        pro[i].wt = pro[i].tat - pro[i].bt;
        avg_wt += pro[i].wt;
        avg_tat += pro[i].tat;
        // printf("P%d\t%d\t%d\t%d\t%d\n", pro[i].pid, pro[i].at, pro[i].bt, pro[i].tat, pro[i].wt);
        printf("P%d|%d|", pro[i].pid, ct);
    }
    printf("\nAvg waiting time  : %f\nAvg turn around time  : %f", avg_wt / n, avg_tat / n);
}
int main(void)
{

    int n;
    int at[10], bt[10];
    printf("Enter the number of proccesses : ");
    scanf("%d", &n);
    printf("Enter the arrival time and burst time :\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d : ", i);
        process[i].pid = i;
        scanf("%d%d", &process[i].at, &process[i].bt);
    }
    sort(process, n);
    FCFS(process, n);
}