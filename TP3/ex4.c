#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int signum) {
    // Handler pour le signal SIGCHLD
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    // Déroute le signal SIGCHLD
    signal(SIGCHLD, handler);
    
    // Crée un fils
    pid_t pid = fork();

    if (pid < 0) {
        // Erreur lors de la création du processus fils
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Code exécuté par le fils
        printf("Je suis le fils avec PID : %d\n", getpid());
        while(1); // Le fils ne se termine pas
    } else {
        // Code exécuté par le père
        printf("Je suis le père avec PID : %d\n", getpid());
        while(1); // Le père ne se termine pas
    }

    return 0;
}
