#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void loadConnectionsFromFile(Graph* graph, const char* filename);

int main() {
    int numUsers = 10; // Cambiar por variable si es dinámico
    Graph* socialNetwork = initializeGraph(numUsers);

    if (!socialNetwork) {
        fprintf(stderr, "Error: No se pudo inicializar el grafo.\n");
        return EXIT_FAILURE;
    }

    loadConnectionsFromFile(socialNetwork, "connections.txt");

    displayGraph(socialNetwork);

    freeGraph(socialNetwork);
    return 0;
}

void loadConnectionsFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int user1, user2;
    while (fscanf(file, "%d %d", &user1, &user2) == 2) {
        if (user1 < 0 || user1 >= graph->numUsers || user2 < 0 || user2 >= graph->numUsers) {
            fprintf(stderr, "Advertencia: Conexión inválida (%d, %d) fuera del rango de usuarios.\n", user1, user2);
            continue; // Saltar esta conexión
        }
        addConnection(graph, user1, user2);
    }

    fclose(file);
}

