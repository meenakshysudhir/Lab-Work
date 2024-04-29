#include<stdio.h>
int main(void)
{
    int m , n,alloc[20][20],need[20][20],max[20][20],avail[50],ind = 0;
    printf("No. of process : ");
    scanf("%d",&n);
    printf("No. of resources : ");
    scanf("%d",&m);
    printf("Enter the Allocation Matrix : ");
    for(int i = 0; i < n;i++)
    {
        printf("P%d :",i+1);
        for(int j = 0 ; j < m ; j++)
        {
            scanf("%d",&alloc[i][j]);
        }
        
    }
    printf("Enter the Max Matrix : ");
    for(int i = 0; i < n;i++)
    {
        for(int j = 0 ; j < m ; j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter the available matrix : ");
    for(int i = 0 ; i < m ; i++)
    {
        scanf("%d",&avail[i]);
    }
    int finish[n];
    for(int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }
    int safesequence[n],work[n];
    for(int i = 0; i < m; i++)
    {
        work[i] = avail[i];
    }
    // NEED calculation
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m ; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("Need Matrix : \n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m ; j++)
        {
            printf("%d\t",need[i][j]);
        }
        printf("\n");
    }
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n;i++)
        {
            if(finish[i] == 0)
            {
                int flag = 0;
                for(int j = 0 ; j < m ; j++)
                {
                    if(need[i][j]> work[j])
                    {
                        flag = 1;
                        break;
                    }
                    
                }
                if(flag == 0)
                {
                    safesequence[ind++] = i; 
                }
                for(int y = 0; y < m ; y++)
                {
                    work[y] = work[y] + alloc[i][y];
                    
                }
                finish[i] = 1;
            }
        }
    }
    printf("The safe sequence is : ");
    for(int i = 0;i < ind+1; i++)
    {
        printf("P%d\t",safesequence[i]);
    }
}