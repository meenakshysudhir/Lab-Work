#include <stdio.h>
struct Process
{
    int pid;
    int at;
    int bt;
    int rt;
    int wt;
    int tat;
} process[10];
int ct = 0, n;
void sort();
void srtf();
int main(void)
{
    printf("Enter the number of process : ");
    scanf("%d", &n);
    printf("Enter the arrival and burst time : ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d : ", i);
        scanf("%d%d", &process[i].at, &process[i].bt);
        process[i].pid = i;
        process[i].rt = process[i].bt;
    }
    sort();
    srtf();
}

void sort()
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (process[j].at > process[j + 1].at)
            {
                struct Process temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

void srtf()
{
    int completed = 0, ct = 0, curr = -1, prev = -1;
    while (completed <= n - 1)
    {
        curr = -1;
        for (int i = 0; i < n; i++)
        {
            if (process[i].at > ct)
            {
                break;
            }
            if ((process[i].at <= ct) && (process[i].rt > 0) && (curr == -1 || process[curr].rt > process[i].rt))
            {
                curr = i;
            }
        }
        if (curr != -1)
        {
            if (curr != prev)
            {
                printf("%d | P%d |", ct, process[curr].pid);
            }
            ct++;
            process[curr].rt--;
            if (process[curr].rt == 0)
            {
                completed++;
                process[curr].tat = ct - process[curr].at;
                process[curr].wt = process[curr].tat - process[curr].bt;
            }
            prev = curr;
        }
        else
        {
            if (prev != curr)
            {
                printf("%d | IDLE |", ct);
            }
            prev = -1;
            ct++;
        }
    }
    printf("%d", ct);
    float avgWt = 0, avgTat = 0;
    for (int i = 0; i < n; i++)
    {
        avgTat += process[i].tat;
        avgWt += process[i].wt;
    }
    printf("Average Turnaround time : %.2f\nAverage Waiting Time : %.2f\n", avgTat / n, avgWt / n);
}