#pragma GCC push_options
#pragma GCC optimize ("O0")
#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>

void* thread_fn(void* arg);
int var = 0;
pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;


int main()
{
    printf("Mutex\n");
    int rc = -1;
    pthread_t thread1, thread2;

    int t1=1;
    int t2=2;

    rc = pthread_mutex_init(&fastmutex, NULL);
    if(rc != 0)
        printf("Mutex Init failed\n");
    printf("Created Mutex\n");
    
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
    pthread_mutex_destroy(&fastmutex);
    return 0;
}


void* thread_fn(void* arg)
{
    int tid;
    tid=(void*)arg;
    while (1)
    {
        printf("thread%d entered thread_fn\n",tid);
        pthread_mutex_lock(&fastmutex);
        printf("thread%d locked mutex\n",tid);
        var++;
        printf("thread%d Incrementing, var=%d\n",tid, var);
        pthread_mutex_unlock(&fastmutex);
        printf("thread%d unlocked mutex\n",tid);
    }
    
}

#pragma GCC pop_options