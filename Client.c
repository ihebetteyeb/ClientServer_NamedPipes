#include "server_cli_fifo.h"
#include "Handlers_Cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <signal.h>


int main() {
    // Déclarations
     Question question;
     Reponse reponse;
     int client_id = getpid();
     int fifo1_fd;
     int fifo2_fd;

    printf("client %d is working \n",client_id);

    // Ouverture des tubes nommés
    fifo1_fd = open(FIFO1, O_WRONLY);
    fifo2_fd = open(FIFO2, O_RDONLY);
    if (fifo1_fd == -1 || fifo2_fd == -1) {
        perror("Erreur lors de l'ouverture des tubes nommés.");
        exit(1);
    }

    // Installation des Handlers
    signal(SIGUSR1, handle_reveil);

    // Initialisation du générateur de nombres aléatoires
    srand(getpid());


    // Construction et envoi d'une question



    question.n = rand() % NMAX + 1;
    printf(" n = %d \n", question.n);
    question.client_id = client_id;

    write(fifo1_fd, &question, sizeof(Question));

    // Attente de la réponse
    printf("Se mettre en attente ... \n");
    pause();

    // Attendez le signal SIGUSR1 pour la réponse


    // Lecture de la réponse
    if (read(fifo2_fd, &reponse, sizeof(Reponse)) == -1) {
        perror("Erreur lors de la lecture de la réponse depuis fifo2");
    } else {
        // Envoi du signal SIGUSR1 au serveur
        if (kill(reponse.server_id, SIGUSR1) == -1) {
            perror("Erreur lors de l'envoi du signal SIGUSR1 au serveur");
        }



    // Traitement local de la réponse
        printf("Nombres reçus depuis le serveur : ");
    for (int i = 0; i < question.n ; i++) {
        printf("%d ", reponse.nombres[i]);
    }
    printf("\n");


    // Fermez les tubes nommés

    if (close(fifo1_fd) == -1) {
   // perror("Erreur lors de la fermeture de FIFO1.");
    }

    if (close(fifo2_fd) == -1) {
   // perror("Erreur lors de la fermeture de FIFO2.");
    }

    return 0;
}
}

