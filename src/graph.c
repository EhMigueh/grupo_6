#include "header.h"

/*
Graph *initializeGraph(int numUsers)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numUsers = numUsers;
    graph->adjacencyList = (Node **)malloc(numUsers * sizeof(Node *));
    for (int i = 0; i < numUsers; i++)
    {
        graph->adjacencyList[i] = NULL;
    }
    return graph;
}

void addConnection(Graph *graph, int user1, int user2)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user2;
    newNode->next = graph->adjacencyList[user1];
    graph->adjacencyList[user1] = newNode;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user1;
    newNode->next = graph->adjacencyList[user2];
    graph->adjacencyList[user2] = newNode;
}

void displayGraph(Graph *graph)
{
    for (int i = 0; i < graph->numUsers; i++)
    {
        fprintf(stdout, "Usuario %d:", i);
        Node *current = graph->adjacencyList[i];
        while (current)
        {
            fprintf(stdout, " -> %d", current->id);
            current = current->next;
        }
        fprintf(stdout, "\n");
    }
}

void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->numUsers; i++)
    {
        Node *current = graph->adjacencyList[i];
        while (current)
        {
            Node *next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->adjacencyList);
    free(graph);
}

void loadConnectionsFromFile(Graph *graph, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int user1, user2;
    while (fscanf(file, "%d %d", &user1, &user2) == 2)
    {
        if (user1 < 0 || user1 >= graph->numUsers || user2 < 0 || user2 >= graph->numUsers)
        {
            fprintf(stderr, "Advertencia: Conexión inválida (%d, %d) fuera del rango de usuarios.\n", user1, user2);
            continue;
        }
        addConnection(graph, user1, user2);
    }

    fclose(file);
}
*/
