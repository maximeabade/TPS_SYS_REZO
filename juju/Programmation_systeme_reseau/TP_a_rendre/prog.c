#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1
#define BUFFER_SIZE 20
#define BUFFER_SIZE_2 40
#define T_DIV 3

// fonction pour écrire une paire d'informations dans un pipe
void write_pair_to_pipe(int pipe[], int first, int second) {
    char first_str[BUFFER_SIZE];
    char second_str[BUFFER_SIZE];
    char buf[BUFFER_SIZE_2];
    // conversion des informations en chaines de caractère
    sprintf(first_str, "%d", first);
    sprintf(second_str, "%d", second);
    // concaténation des deux chaines de caractère
    sprintf(buf, "%s %s", first_str, second_str);
    // écriture dans le pipe
    if (write(pipe[WRITE], buf, sizeof(buf)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

// fonction pour lire une paire d'informations dans un pipe
void read_pair_from_buf(char buf[BUFFER_SIZE_2], int *first, int *second) {
    char id_str[BUFFER_SIZE];
    char num_str[BUFFER_SIZE];
    // séparation des deux chaines de caractère
    sscanf(buf, "%s %s", id_str, num_str);
    // conversion des chaines de caractère en entiers
    *first = atoi(id_str);
    *second = atoi(num_str);
}

// fonction pour lire une intervale donnée par le père
void read_interval(int pipe[], int *start, int *end){
    char buf_start[BUFFER_SIZE_2];
    close(pipe[WRITE]); // fermer le côté écriture du tube

    int bytes_read = read(pipe[READ], buf_start, sizeof(buf_start));
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    
    // attendre que le père envoie le nombre start et end
    while (bytes_read <= 0) {
        bytes_read = read(pipe[READ], buf_start, sizeof(buf_start));
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
    }

    read_pair_from_buf(buf_start, start, end);
}

// Fonction pour vérifier si un nombre est premier
int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Fonction pour effectuer la recherche de nombres premiers dans un intervalle
void search_primes(int id, int start, int end, int common_pipe[]) {
    printf("Processus %d recherche dans [%d,%d]\n", id, start, end);
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            // écrire l'id du fils et le nombre premier trouvé dans le tube
            write_pair_to_pipe(common_pipe, id, i);
        }
    }
    // écrire l'id du fils et un 0 dans le tube
    write_pair_to_pipe(common_pipe, id, 0);
}

// Fonction principale
int main() {

    int N, p;

    // Lecture des valeurs de N et p
    printf("Entrez la valeur de N : ");
    scanf("%d", &N);
    printf("Entrez le nombre de processus travailleurs p : ");
    scanf("%d", &p);

    // Vérification des valeurs de N et p
    if (N <= 1) {
        printf("N doit être supérieur à 1.\n");
        exit(1);
    }
    if (p < 1 || p > N / T_DIV) {
        printf("Le nombre de processus travailleurs p doit être compris entre 1 et N / T_DIV. (T_DIV = %d)\n", T_DIV);
        exit(1);
    }

    int T = N / p / T_DIV; // taille des intervalles à rechercher
    printf("Les intervalles de recherche sont de taille %d.\n", T);
    int pipes[p][2]; // tableau de tubes pour communiquer avec les fils
    int common_pipe[2]; // tube pour communiquer avec le père
    pid_t pid[p]; // tableau de processus pour les fils

    // créer les tubes pour que le père communique avec les fils
    for (int i = 0; i < p; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Erreur à la création du pipe");
            exit(EXIT_FAILURE);
        }
    }

    // créer le tube commun pour que les fils communiquent avec le père
    if (pipe(common_pipe) == -1) {
        perror("Erreur à la création pipe commun");
        exit(EXIT_FAILURE);
    }

    // créer les fils pour effectuer la recherche
    for (int i = 0; i < p; i++) {

        pid[i] = fork(); // création du fils
        if (pid[i] == -1) {

            perror("Erreur fork");
            exit(EXIT_FAILURE);

        } else if (pid[i] == 0) {

            // code exécuté par le fils :
            close(pipes[i][WRITE]); // fermer le côté écriture du tube
            close(common_pipe[READ]); // fermer le côté lecture du tube commun
            
            // écrire l'id du fils et un 0 dans le tube
            write_pair_to_pipe(common_pipe, i, 0);

            int start, end = -1;
            
            while (1)
            {
                read_interval(pipes[i], &start, &end);

                // vérifier si le père a envoyé la fin de la recherche
                if (start == 0 && end == 0) {
                    break;
                }

                // effectuer la recherche des nombres premiers
                search_primes(i, start, end, common_pipe);

            }

            exit(EXIT_SUCCESS);
        }
    }

    // code exécuté par le père :

    // le compteur d'intervalle calculé
    int count_intervals = 0;

    // le nombre de processus fils terminé
    int nbr_of_finished = 0;
    int stop = 0;

    while (nbr_of_finished < p) {

        char buf[BUFFER_SIZE_2];

        close(common_pipe[WRITE]); // fermer le côté écriture du tube
        int bytes_read = read(common_pipe[READ], buf, sizeof(buf)); // lire depuis le tube
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (bytes_read > 0) {

            // lire la paire id & num dans le buffer
            int id, num = -1;
            read_pair_from_buf(buf, &id, &num);

            // vérifier si le fils a envoyé la fin de la recherche
            if (num == 0) {
                count_intervals++;
                // si il reste des intervalles à parcourir
                if(!stop){
                    int start = T * count_intervals - T + 1;
                    int end = T * count_intervals;
                    if (end >= N) {
                        end = N;
                        stop = 1;
                    }
                    close(pipes[id][READ]); // fermer le côté lecture du tube
                    // informer le fils du nouvel intervalle de recherche
                    write_pair_to_pipe(pipes[id], start, end);
                } else {
                    nbr_of_finished++;
                    // envoyer la fin de la recherche au fil
                    write_pair_to_pipe(pipes[id], 0, 0);
                }
                continue;
            }

            printf("Processus %d a trouvé le nombre premier %d\n", id, num);
        }
    }

    close(pipes[0][READ]);
    // attendre que tous les fils se terminent
    for (int i = 0; i < p; i++) {
        int status;
        waitpid(pid[i], &status, 0);
    }

    return 0;
}