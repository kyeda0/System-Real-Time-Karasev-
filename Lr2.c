#include <stdio.h>
#include <pthread.h>
#include <sys/neutrino.h>

pthread_t thread_id1;
pthread_t thread_id2;

void *long_thread_id1(void * notused){
    int n;
    for ( n = 0; n < 5; n++)
    {
        printf("Eto pervii potok , TID %d - N povtora %d\n",thread_id1,n);
        sleep(2);
    } 
}
void *long_thread_id2(void * notused){
    int m;
    for ( m = 0; m< 5; m++)
    {
        printf("Eto vtoroi potok , TID %d - N povtora %d\n",thread_id2,m);
        sleep(1);
    } 
}

int main(void){
    printf("Prog theread PID %d\n",getpid());
    printf("Rusanov Eugeni I914B");
    pthread_create(&long_thread_id1,NULL,long_thread_id1,NULL);
    pthread_create(&long_thread_id2,NULL,long_thread_id2,NULL);
    sleep(40);
    return(1);
}
