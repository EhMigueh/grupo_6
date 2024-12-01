#include "header.h"

int find_user_with_most_friends(Graph *graph) {
    int maxFriends = -1; // Mayor número de amigos encontrado
    int userIndex = -1;  // Índice del usuario con más amigos
    int i;
    if (!graph || graph->numUsers == 0) {
        printf(RED "El grafo está vacío o no inicializado.\n" RESET);
        return -1;
    }
    for (i = 0; i < graph->numUsers; i++) {
        
	int friendCount = 0;    
	Node *current = graph->adjacencyList[i];

        // Contar las conexiones del usuario actual
        while (current) {
            friendCount++;
            current = current->next;
        }

        // Actualizar si el usuario actual tiene más amigos
        if (friendCount > maxFriends) {
            maxFriends = friendCount;
            userIndex = i;
        }
    }

    if (userIndex != -1) {
        printf(GREEN "El usuario con más amigos es: %s con %d amigos.\n" RESET,
               graph->user_names[userIndex], maxFriends);
    } else {
        printf(YELLOW "No se encontraron usuarios con amigos.\n" RESET);
    }

    return userIndex;
}

void print_friends_of_user(Graph *graph, int userIndex) {
    if (!graph || userIndex < 0 || userIndex >= graph->numUsers) {
        printf(RED "Índice de usuario inválido o grafo no inicializado.\n" RESET);
        return;
    }

    Node *current = graph->adjacencyList[userIndex];
    printf(CYAN "Amigos de %s:\n" RESET, graph->user_names[userIndex]);

    while (current) {
        printf("- %s\n", graph->user_names[current->id]);
        current = current->next;
    }
}
