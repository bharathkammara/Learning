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
pthread_spinlock_t sp;


int main()
{
    printf("Spinlock\n");
    int rc = -1;
    pthread_t thread1, thread2;

    int t1=1;
    int t2=2;

    rc = pthread_spin_init(&sp, 0);;
    if(rc != 0)
        printf("Spinlock init failed\n");
    printf("spinlock created\n");
  
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
    pthread_spin_destroy(&sp);
    return 0;
}


void* thread_fn(void* arg)
{
    int tid;
    tid=(void*)arg;
    while (1)
    {       
        pthread_spin_lock(&sp);
        printf("thread%d locked by spinlock\n",tid);
        var++;
        printf("thread%d Incrementing, var=%d\n",tid, var);
        pthread_spin_unlock(&sp);
        printf("thread%d unlocked spinlock\n",tid);
        
    }
    
}

#pragma GCC pop_options