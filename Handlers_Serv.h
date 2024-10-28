#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Handler pour informer le  serveur suite à la réception du signal SIGUSR1
void hand_reveil(int sig) {
    printf("Signal SIGUSR1 reçu du client , le client a terminé la lecture \n");

}

// Handler pour la fin du serveur suite à la réception d'un signal quelconque
void fin_serveur(int sig) {
    printf("Signal SIGINT reçu. Terminaison du serveur... \n");
    exit(0);
}

#endif
