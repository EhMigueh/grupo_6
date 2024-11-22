#include "header.h"

void loadConnectionsFromFile(Graph *graph, const char *filename);

int main()
{
    int numUsers = 10;
    Graph *socialNetwork = initializeGraph(numUsers);

    if (!socialNetwork)
    {
        fprintf(stderr, "Error: No se pudo inicializar el grafo.\n");
        return EXIT_FAILURE;
    }

    loadConnectionsFromFile(socialNetwork, "connections.txt");

    displayGraph(socialNetwork);

    freeGraph(socialNetwork);
    return 0;
}
