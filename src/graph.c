#include "header.h"

// Función para inicializar el Grafo.
Graph *initializeGraph(int numUsers)
{
    // Reservar memoria para el grafo.
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    // Asignar el número de usuarios al grafo.
    graph->numUsers = numUsers;

    // Inicializar la lista de adyacencia con nodos nulos.
    graph->adjacencyList = (Node **)calloc(numUsers + 1, sizeof(Node *));

    // Retornar el grafo inicializado
    return graph;
}

// Función para agregar una conexión entre dos usuarios.
void addConnection(Graph *graph, int user1, int user2)
{
    fprintf(stdout, "Agregando conexión entre el usuario %d y el usuario %d\n", user1 + 1, user2 + 1);

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user2;
    newNode->next = graph->adjacencyList[user1]; // Conecta el primer usuario.
    graph->adjacencyList[user1] = newNode;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user1;
    newNode->next = graph->adjacencyList[user2]; // Conecta el segundo usuario.
    graph->adjacencyList[user2] = newNode;
}

// Función para mostrar las conexiones del grafo.
void displayGraph(Graph *graph)
{
    fprintf(stdout, "Mostrando conexiones del grafo:\n");

    for (int i = 0; i < graph->numUsers; i++)
    {
        fprintf(stdout, "Índice de Usuario %d: ", i + 1);
        Node *temp = graph->adjacencyList[i];

        while (temp)
        {
            printf("%d -> ", temp->id + 1);
            temp = temp->next;
        }

        fprintf(stdout, "NULL\n");
    }
}

// Función para liberar la memoria del grafo.
void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->numUsers; i++)
    {
        Node *temp = graph->adjacencyList[i];
        while (temp)
        {
            Node *toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }

    free(graph->adjacencyList);
    free(graph);
}
