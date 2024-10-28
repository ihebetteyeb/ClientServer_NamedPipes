
#include "server_cli_fifo.h"
#include "Handlers_Serv.h"
#include <sys/types.h>
#include <signal.h>

int main() {

    // Déclarations
    int  fd_fifo1;
    int  fd_fifo2 ;
    Question question;
    Reponse reponse;
    int server_id = getpid();


    printf("Attente des questions de client ... \n ");
    // Création et initialisation des tubes nommés
      if (mkfifo(FIFO1, 0666) == -1) {
        perror("Erreur lors de la création du tube nommé fifo1");
        exit(EXIT_FAILURE);
    }
        if (mkfifo(FIFO2, 0666) == -1) {
            perror("Erreur lors de la création du tube nommé fifo2");
            exit(EXIT_FAILURE);
        }
    // Initialisation du générateur de nombres aléatoires
    srand(getpid());

    // Ouverture des tubes nommés
      fd_fifo1 = open(FIFO1, O_RDONLY);
     fd_fifo2 = open(FIFO2, O_WRONLY);
 if (fd_fifo1 == -1 || fd_fifo2 == -1) {
        perror("Erreur lors de l'ouverture des tubes nommés.");
        exit(1);
    }
    // Installation des Handlers
    signal(SIGUSR1, hand_reveil);
    signal(SIGINT, fin_serveur);


        while (1) {
    // Lecture d'une question depuis le tube nommé fifo1

    ssize_t bytes_read = read(fd_fifo1, &question, sizeof( Question));

    if (bytes_read == -1) {
        perror("Erreur lors de la lecture de la question");
        continue; // Réessayer la lecture
    } else if (bytes_read == 0) {
        // Le tube a été fermé par tous les clients, vous pouvez quitter la boucle ici si nécessaire
        continue;
    } else {
        // Vous avez lu une question avec succès
        // Maintenant, vous pouvez générer une réponse aléatoire



        // Génération de la réponse aléatoire
        reponse.client_id = question.client_id;
        reponse.server_id = server_id;
        for (int i = 0; i < question.n; i++) {
            reponse.nombres[i] = rand() % NMAX + 1 ;
        }

        // Envoi de la réponse au client via le tube nommé fifo2
        if (write(fd_fifo2, &reponse, sizeof( Reponse)) == -1) {
            perror("Erreur lors de l'envoi de la réponse");
        }else {

            // Envoi du signal SIGUSR1 au client concerné
        kill(question.client_id, SIGUSR1);
        }



    }
}


    // Fermeture des tubes et nettoyage
    if (close(fd_fifo1) == -1) {
    perror("Erreur lors de la fermeture de FIFO1.");
    }

    if (close(fd_fifo2) == -1) {
    perror("Erreur lors de la fermeture de FIFO2.");
    }
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
