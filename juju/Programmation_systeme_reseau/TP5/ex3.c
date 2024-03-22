#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


static pthread_mutex_t my_mutex;


void *imprimerNumThread(void * arg)
{
    int pthread_mutex_lock(pthread_mutex_t *mutex);
    for(int i =0; i<3; i++){
        printf("%s\n", (char*)arg);
    }
    int pthread_mutex_unlock(pthread_mutex_t *mutex); 
    pthread_exit(0);
}


int main (int argc, char **argv){
    pthread_t th1, th2, th3, th4;
    void *ret;
    pthread_mutex_init(&my_mutex, NULL);//initialise le mutex par défaut
    if (pthread_create(&th1, NULL, imprimerNumThread, "1") < 0) {
        fprintf (stderr, "pthread_create error for thread 1\n");
        exit (1);
    }
    if (pthread_create(&th2, NULL, imprimerNumThread, "2") < 0) {
        fprintf (stderr, "pthread_create error for thread 2\n");
        exit (1);
    }
    if (pthread_create(&th3, NULL, imprimerNumThread, "3") < 0) {
        fprintf (stderr, "pthread_create error for thread 3\n");
        exit (1);
    }
    if (pthread_create(&th4, NULL, imprimerNumThread, "4") < 0) {
        fprintf (stderr, "pthread_create error for thread 4\n");
        exit (1);
    }
    pthread_mutexattr_destroy(&my_mutex);
    (void)pthread_join (th1, &ret);
    (void)pthread_join (th2, &ret);
    (void)pthread_join (th3, &ret);
    (void)pthread_join (th4, &ret);
}