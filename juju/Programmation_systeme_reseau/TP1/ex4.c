#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    printf("Je suis le processus de pid : %d.\n", getpid());
    printf("Mon père est le processus de pid : %d.\n", getppid());
    printf("Mon uid : %d.\n", getuid());
    printf("Mon euid : %d.\n", geteuid());
    printf("Mon gid : %d.\n", getgid());
    printf("Mon egid : %d.\n", getegid());
}