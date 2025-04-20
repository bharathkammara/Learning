#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>

void* thread1_fn(void* arg);
void* thread2_fn(void* arg);
int var = 0;


int main()
{
    printf("Mutex\n");
    int fd = -1;
    pthread_t thread1, thread2;
    fd = pthread_create(&thread1,NULL,thread1_fn, NULL);
    if(fd != 0)
        printf("Creating thread1 failed\n");
    printf("after creating thread1, var=%d\n", var);
    
    fd = pthread_create(&thread2,NULL,thread2_fn, NULL);
    if(fd != 0)
        printf("Creating thread2 failed\n");
    printf("after creating thread2, var=%d\n", var);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}


void* thread1_fn(void* arg)
{
    printf("Created thread1 sucessfully\n");
    while (1)
    {
        var++;
        printf("Incrementing in thread1, var=%d\n", var);
    }
    
}

void* thread2_fn(void* arg)
{
    printf("Created thread2 sucessfully\n");
    while (1)
    {
        var++;
        sleep(1);
        printf("Incrementing in thread2, var=%d\n", var);
    }
}