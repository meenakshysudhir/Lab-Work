#include <stdio.h>
#include <math.h>

int left[8], right[8];

void sort(int arr[], int size)
{
    // BUBBBLE SORT
    int temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void SCAN(int arr[], int head, int ch, int diskSize)
{
    int distance, curr_track, seek_count = 0;
    int left_size = 0, right_size = 0;
    for (int i = 0; i < 8; i++)
    {
        if (arr[i] < head)
        {
            left[left_size++] = arr[i];
        }
        else
        {
            right[right_size++] = arr[i];
        }
    }
    sort(left, left_size);
    sort(right, right_size);
    for (int i = 0; i < left_size; i++)
    {
        printf("%d\t", left[i]);
    }
    printf("\nRIGHT:\n");
    for (int i = 0; i < right_size; i++)
    {
        printf("%d\t", right[i]);
    }
    if (ch == 1)
    {
        for (int i = left_size - 1; i >= 0; i--)
        {
            curr_track = left[i];
            distance = fabs(head - curr_track);
            seek_count += distance;
            head = curr_track;
        }
        distance = fabs(head - 0);
        seek_count += distance;
        head = 0;
        for (int i = 0; i < right_size; i++)
        {
            curr_track = right[i];
            distance = fabs(head - curr_track);
            seek_count += distance;
            head = curr_track;
        }
        printf("\nSeek count : %d\n", seek_count);
        printf("Seek sequence : ");
        for (int i = left_size - 1; i >= 0; i--)
        {
            printf("%d\t", left[i]);
        }
        printf("0\t");
        for (int i = 0; i < right_size; i++)
        {
            printf("%d\t", right[i]);
        }
    }
    if (ch == 2)
    {
        for (int i = 0; i < right_size; i++)
        {
            curr_track = right[i];
            distance = fabs(head - curr_track);
            seek_count += distance;
            head = curr_track;
        }
        distance = fabs(diskSize - head);
        seek_count += distance;
        head = diskSize;
        for (int i = left_size - 1; i >= 0; i--)
        {
            curr_track = left[i];
            distance = fabs(head - curr_track);
            seek_count += distance;
            head = curr_track;
        }

        printf("\nSeek count : %d\n", seek_count);
        printf("Seek sequence : ");
        for (int i = 0; i < right_size; i++)
        {
            printf("%d\t", right[i]);
        }
        printf("%d\t", diskSize);
        for (int i = left_size - 1; i >= 0; i--)
        {
            printf("%d\t", left[i]);
        }
    }
}

int main(void)
{
    int arr[8] = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;
    printf("Enter 1 for left and 2 for right first :");
    int ch;
    scanf("%d", &ch);
    printf("Enter the disk size : ");
    int diskSize;
    scanf("%d", &diskSize);
    SCAN(arr, head, ch, diskSize);
}