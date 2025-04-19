#pragma GCC push_options
#pragma GCC optimize ("O0")
#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>
#include<semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

void* thread_fn(void* arg);
int var = 0;
sem_t sem;


int main()
{
    printf("Semaphore\n");
    int rc = -1;
    pthread_t thread1, thread2;

    int t1=1;
    int t2=2;

    rc = sem_init(&sem,0, 1);
    if(rc != 0)
        printf("Sem init failed\n");
    printf("Semaphore created\n");
  
    rc = pthread_create(&thread1,NULL,thread_fn,t1);
    if(rc != 0)
        printf("Creating thread1 failed\n");
    printf("after creating thread1, var=%d\n", var);
    
    rc = pthread_create(&thread2,NULL,thread_fn, t2);
    if(rc != 0)
        printf("Creating thread2 failed\n");
    printf("after creating thread2, var=%d\n", var);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&sem);
    return 0;
}


void* thread_fn(void* arg)
{
    int tid;
    tid=(void*)arg;
    while (1)
    {
        sem_wait(&sem);
        printf("thread%d locked sem\n",tid);
        var++;
        printf("thread%d Incrementing, var=%d\n",tid, var);
        printf("thread%d unlocked sem\n",tid);
        sem_post(&sem);
    }
    
}

#pragma GCC pop_options