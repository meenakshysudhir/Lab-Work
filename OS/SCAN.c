#include <stdio.h>
#include <math.h>
int arr[8] = {82, 170, 43, 140, 24, 16, 190};
int head = 50, n = 7, distance, seekcount = 0, lc = 0, rc = 0, max;
int left[10], right[10];

void sort(int array[], int n);
int main(void)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < head)
        {
            left[lc++] = arr[i];
        }
        else
        {
            right[rc++] = arr[i];
        }
    }
    sort(left, lc);
    sort(right, rc);

    printf("Total cylinders : ");
    scanf("%d", &max);
    printf("Towards right\n");
    for (int i = 0; i < rc; i++)
    {
        printf("%d\t", right[i]);
    }
    printf("%d\t", max);
    distance = fabs(max - head);
    seekcount += distance;
    for (int i = lc - 1; i >= 0; i--)
    {
        printf("%d\t", left[i]);
    }
    distance = fabs(left[0] - max);
    seekcount += distance;
    printf("Seek count : %d\n", seekcount);
}
void sort(int array[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}