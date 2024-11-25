#include "header.h"

Graph *initializeGraph(int numUsers)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numUsers = numUsers;
    graph->adjacencyList = (Node **)calloc(numUsers, sizeof(Node *));
    return graph;
}

void addConnection(Graph *graph, int user1, int user2)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user2;
    newNode->next = graph->adjacencyList[user1]; // conecta el primer user
    graph->adjacencyList[user1] = newNode;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user1;
    newNode->next = graph->adjacencyList[user2]; // conecta el segundo user
    graph->adjacencyList[user2] = newNode;
}
void displayGraph(Graph *graph)
{
    printf("Mostrando conexiones del grafo:\n");

    for (int i = 0; i < graph->numUsers; i++)
    {
        printf("Usuario %d: ", i);
        Node *temp = graph->adjacencyList[i]; // funcion que muestra el grafo para las conexiones, deberia estas funcionando las conexiones pero no se muestran los grafos
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
