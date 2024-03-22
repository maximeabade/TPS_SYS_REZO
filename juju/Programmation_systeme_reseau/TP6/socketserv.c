#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     /* Creation de la socket */
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        printf("Erreur Creation Socket\n");

     /* La fonction bzero place des octets nuls dans une chaîne de caractères. 
	Cette fonction est utilisée pour donner des valeurs nulles à toutes les structures de la socket.
     */
     bzero((char *) &serv_addr, sizeof(serv_addr));

     /* Numero de port */
     portno = 2848;
     /* TCP IP */
     serv_addr.sin_family = AF_INET;
     /* INADDR_ANY qui signifie que la socket peut-être associée à n'importe quelle adresse
	IP de la machine locale (s'il en existe plusieurs) et à un port number spécifique */
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     /* htons() pour convertir le numéro de port (sur 16 bits - htonl pour 32 bits) 
	depuis l’ordre des octets de l’hôte vers celui du réseau. 
	L'ordre des octets du réseau est en fait big-endian. 
	Il est donc plus prudent d’appeler des fonctions qui
	respectent cet ordre pour coder des informations dans les en-têtes des protocoles réseaux.*/
     serv_addr.sin_port = htons(portno);
     /* bind() va permettre de lier la socket d’écoute à une interface et à un numéro de port local à la machine */
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              printf("Erreur liaison \n");
     /* Maintenant que le serveur a créé et attaché une socket d’écoute, il doit la placer en attente passive,
	c’est-à-dire capable d’accepter les demandes de connexion des processus clients. */
     /* 5 : longueur maximale pour la file des connexions en attente */
     listen(sockfd,5);
     /* accept() est employé avec les sockets utilisant un protocole en mode
	connecté SOCK_STREAM. Il extrait la première connexion de la file des connexions
	en attente de la socket sockfd à l’écoute, crée une nouvelle socket connectée, et
	renvoie un nouveau descripteur de fichier qui fait référence à cette socket.*/
     /* on prepare l'adresse */
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          printf("Erreur acceptation\n");

     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) printf("Erreur de lecture Socket\n");
     printf("Le message reçu : %s\n",buffer);
     n = write(newsockfd,"Message reçu",13);
     if (n < 0) printf("Erreur écriture sur Socket\n");
     close(newsockfd);
     close(sockfd);
     return 0; 
}
