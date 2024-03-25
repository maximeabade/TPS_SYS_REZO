#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int i;
    int somme = 0;
    if(argc > 1){
        for(i=1; i<argc; i++){
            somme += atoi(argv[i]);
        }
        printf("La somme de la liste est %d.\n", somme);
    } else {
        printf("Il n'y a pas d'arguments.\n");
    }
	return(0);
}
