#include "header.h"

Graph *initializeGraph(int numUsers)
{
    // Reservar memoria para el grafo
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    // Asignar el número de usuarios al grafo
    graph->numUsers = numUsers;
    // Inicializar la lista de adyacencia con nodos nulos
    graph->adjacencyList = (Node **)calloc(numUsers + 1, sizeof(Node *));

    // Retornar el grafo inicializado
    return graph;
}


void addConnection(Graph *graph, int user1, int user2)
{
  
    printf("Agregando conexión entre el usuario %d y el usuario %d\n", user1, user2);

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user2;
    newNode->next = graph->adjacencyList[user1]; // conecta el primer usuario
    graph->adjacencyList[user1] = newNode;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user1;
    newNode->next = graph->adjacencyList[user2]; // conecta el segundo usuario
    graph->adjacencyList[user2] = newNode;
}

void displayGraph(Graph *graph)
{
    printf("Mostrando conexiones del grafo:\n");

    for (int i = 0; i < graph->numUsers; i++)
    {
        printf("Índice de Usuario %d: ", i);
        Node *temp = graph->adjacencyList[i];
        while (temp)
        {
            printf("%d -> ", temp->id);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}



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
