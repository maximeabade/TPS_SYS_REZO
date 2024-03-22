#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    pid_t p;
    int i;
    int n = atoi(argv[1]);
    if(argc == 2){
        for(i=0; i<n; i++){
            p = fork();
            printf("i = %d\n", i);
            switch(p) {
                case 0 : 
                //sleep(15);
                printf("Je suis le fils, mon PID est %d et mon PPID est %d\n\n",getpid() ,getppid());
                break;

                case -1 :
                //sleep(15);
                perror("Erreur de création de processus avec fork");
                exit(-1);
                break;

                default :
                printf("Je suis le père, mon PID est %d et mon PPID est %d\n\n",getpid(), getppid());
                break;
            }
        }
    } else {
        printf("Veuillez donner un entier en argument.\n");
    }
    return 0;
}