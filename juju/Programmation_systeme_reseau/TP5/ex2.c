#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *my_thread(void * arg)
{
    printf("I'm thread %s\n", (char*)arg);
    pthread_exit(0);
}

void *my_last_thread(void * arg)
{
    pid_t p;
    printf("I'm thread %s\n", (char*)arg);
    p = fork();
    switch(p) {
        case 0 : 
        //sleep(15);
        printf("Je suis le fils, mon PID est %d et mon PPID est %d\n",getpid() ,getppid());
        break;
        case -1 :
        //sleep(15);
        perror("Erreur de création de processus avec fork");
        break;
        default :
        printf("Je suis le père, mon PID est %d et mon PPID est %d\n",getpid(), getppid());
        break;
    }
    pthread_exit(0);
}

int main (int argc, char **argv){
    pthread_t th1, th2, th3;
    void *ret;
    if (pthread_create(&th1, NULL, my_thread, "1") < 0) {
        fprintf (stderr, "pthread_create error for thread 1\n");
        exit (1);
    }
    if (pthread_create(&th2, NULL, my_thread, "2") < 0) {
        fprintf (stderr, "pthread_create error for thread 2\n");
        exit (1);
    }
    if (pthread_create(&th3, NULL, my_last_thread, "3") < 0) {
        fprintf (stderr, "pthread_create error for thread 3\n");
        exit (1);
    }
    (void)pthread_join (th1, &ret);
    (void)pthread_join (th2, &ret);
    (void)pthread_join (th3, &ret);
}