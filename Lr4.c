#include <stdio.h>
#include <time.h>
#include <sync.h>
#include <sys/neutrino.h>

barrier_t barrier;


void *thread1(void *not_used){
    time_t now;
    char buf[27];
    time(&now);

    printf("Potok1,vremia%s\n",ctime_r(&now,buf));
    sleep(3);

    barrier_wait(&barrier);
    tine(&now);
    printf("barrier v potoke1,vremia srabativania%s\n",ctime_r(&now,buf));

}
void *thread2(void *not_used){
    time_t now;
    char buf[27];
    time(&now);

    printf("Potok2,vremia%s\n",ctime_r(&now,buf));
    sleep(6);

    barrier_wait(&barrier);
    tine(&now);
    printf("barrier v potoke2,vremia srabativania%s\n",ctime_r(&now,buf));
}

main(){
    time_t now;
    char buf[27];
    barrier_init(&barrier,NULL,3);
    printf("Start\n");
    pthread_create(NULL,NULL,thread1,NULL);
    pthread_create(NULL,NULL,thread2,NULL);
    time(&now);
    printf("Main(): oshidanie y bariera, vremia %s\n",ctime_r(&now,buf));
    barrier_wait(&barrier);
    time(&now);
    printf("barrier v main(),vremia srabativania %s\n",ctime_r(&now,buf));
    sleep(5);
}