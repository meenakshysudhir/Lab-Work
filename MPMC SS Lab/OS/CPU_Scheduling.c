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
    int completed;
} process[10];

int ct = 0;
float avg_wt = 0, avg_tat = 0;
void sort_at(struct Process pro[10], int n)
{
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pro[j].at > pro[j + 1].at)
            {
                temp = pro[j];
                pro[j] = pro[j + 1];
                pro[j + 1] = temp;
            }
        }
    }
}
void sort_bt(struct Process pro[10], int n)
{
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pro[j].bt > pro[j + 1].bt)
            {
                temp = pro[j];
                pro[j] = pro[j + 1];
                pro[j + 1] = temp;
            }
        }
    }
}
void FCFS(struct Process pro[10], int n)
{
    int ct = 0;
    float avg_tat = 0, avg_wt = 0;
    printf("%d|", ct);
    for (int i = 0; i < n; i++)
    {
        ct += pro[i].bt;
        pro[i].tat = ct - pro[i].at;
        pro[i].wt = pro[i].tat - pro[i].bt;
        avg_wt += pro[i].wt;
        avg_tat += pro[i].tat;
        printf("P%d|%d|", pro[i].pid, ct);
    }
    printf("\nAvg waiting time  : %.2f\nAvg turn around time  : %.2f\n", avg_wt / n, avg_tat / n);
}

void SJF(struct Process pro[10], int n)
{
    int ct = 0, completed = 0, flag = 0;
    struct Process *cp = NULL;

    printf("\nSJF\nGANTT CHART : \n");

    while (completed < n)
    {
        int minBt = 1e9, ind = -1;
        for (int i = 0; i < n; i++)
        {
            if (pro[i].at <= ct && pro[i].completed == 0 && pro[i].bt < minBt)
            {
                ind = i;
                minBt = pro[i].bt;
            }
        }

        if (ind != -1)
        {
            cp = &pro[ind];
            ct += cp->bt;
            cp->tat = ct - cp->at;
            cp->wt = cp->tat - cp->bt;
            cp->completed = 1;
            avg_wt += cp->wt;
            avg_tat += cp->tat;
            printf("%d | P%d | ", ct - cp->bt, cp->pid);
            completed++;
        }
        else
        {
            if (flag == 0)
            {
                printf("0 | ");
                flag = 1;
            }
            printf("IDLE | ");
            ct++;
        }
    }
    printf("%d", ct);
    printf("\nAverage waiting time : %.2f\n", avg_wt / n);
    printf("Average Turnaround time : %.2f\n", avg_tat / n);
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
        process[i].completed = 0;
        scanf("%d%d", &process[i].at, &process[i].bt);
    }
    sort_at(process, n);
    FCFS(process, n);
    sort_bt(process, n);
    SJF(process, n);
}