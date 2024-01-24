#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int somme;
	if (argc != 3) {
		printf("usage: %s <operande_1> <operande_2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	somme=atoi(argv[1])+atoi(argv[2]);
	printf("%s + %s = %d\n", argv[1], argv[2], somme);
}
