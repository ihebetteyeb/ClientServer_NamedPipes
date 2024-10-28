#ifndef SERVER_CLI_FIFO_H
#define SERVER_CLI_FIFO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NMAX 20

#define FIFO1 "FIFO1"  // Tube nommé pour les questions du client vers le serveur
#define FIFO2 "FIFO2"  // Tube nommé pour les réponses du serveur vers le client

// Structure de données pour une question
typedef struct {
    int client_id;  // Numéro du client
    int n;          // Nombre aléatoire
} Question;

// Structure de données pour une réponse
typedef struct {
    int client_id;  // Numéro du client
    int nombres [NMAX] ;
    int server_id; // Réponse à la question
} Reponse;

// Prototypes de fonctions
void read_question_from_fifo(const char* fifo_name, Question* q);
void send_response_to_fifo(const char* fifo_name, const Reponse* r, int client_id);
void send_signal_to_client(int signal, int client_id);

#endif

