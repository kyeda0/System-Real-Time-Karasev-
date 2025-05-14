#include <stdio.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <sched.h>

pthread_t thread_id1;
pthread_t thread_id2;

void *long_thread_id1(void *notused){
    int n;
    for (n = 0; n < 5; n++) {
        printf("Eto pervii potok, TID %d - N povtora %d\n", (int)pthread_self(), n);
        sleep(2);
    }
    return NULL;
}

void *long_thread_id2(void *notused){
    int m;
    for (m = 0; m < 5; m++) {
        printf("Eto vtoroi potok, TID %d - N povtora %d\n", (int)pthread_self(), m);
        sleep(1);
    }
    return NULL;
}

int main(void) {
    struct sched_param param;

    printf("Prog thread PID %d\n", getpid());
    printf("Rusanov Eugene I914B\n");

    pthread_attr_t attr1;
    pthread_attr_init(&attr1);
    pthread_attr_setschedpolicy(&attr1, SCHED_RR);           
    param.sched_priority = 10;                                
    pthread_attr_setschedparam(&attr1, &param);
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED); 
    pthread_create(&thread_id1, &attr1, long_thread_id1, NULL);

    pthread_attr_t attr2;
    pthread_attr_init(&attr2);
    pthread_attr_setschedpolicy(&attr2, SCHED_FIFO);          
    param.sched_priority = 8;                                 
    pthread_attr_setschedparam(&attr2, &param);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    pthread_create(&thread_id2, &attr2, long_thread_id2, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 0;
}
