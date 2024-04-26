
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
int main(void)
{
    int shmid;
    void *shared_memory;
    char buff[100];
    shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);
    printf("Key of shared memory : %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    printf("Shared memory attached at : %p\n", shared_memory);
    printf("Enter data to be written : \n");
    read(0, buff, 100);
    strcpy(shared_memory, buff);
    printf("Data written : %s\n", (char *)shared_memory);
}