#include "header.h"

// Función para inicializar el Grafo.
Graph *initialize_graph(int numUsers, User *users)
{
    if (numUsers <= 0)
    {
        fprintf(stderr, "No se puede inicializar un grafo sin usuarios. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    // Reservar memoria para el grafo.
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    // Asignar el número de usuarios al grafo.
    graph->numUsers = numUsers;

    // Inicializar la lista de adyacencia con nodos nulos.
    graph->adjacencyList = (Node **)calloc(numUsers + 1, sizeof(Node *));

    // Agregar nombres de usuarios
    graph->user_names = malloc(numUsers * sizeof(char *));
    for (int i = 0; i < numUsers; i++)
        graph->user_names[i] = strdup(users[i].username);

    // Retornar el grafo inicializado
    return graph;
}

// Función para agregar una conexión entre dos usuarios.
void add_connection(Graph *graph, int user1, int user2)
{
    if (!graph)
    {
        fprintf(stderr, "Grafo no inicializado. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

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
void display_graph(Graph *graph)
{
    for (int i = 0; i < graph->numUsers; i++)
    {
        fprintf(stdout, GREEN "%s -> " RESET, graph->user_names[i]);
        Node *temp = graph->adjacencyList[i];

        while (temp)
        {
            fprintf(stdout, "%s -> ", graph->user_names[temp->id]);
            temp = temp->next;
        }

        fprintf(stdout, "NULL\n");
    }
}
// Función para liberar la memoria del grafo.
void free_graph(Graph *graph)
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

        // Liberar nombres de usuarios.
        free(graph->user_names[i]);
    }

    free(graph->user_names);
    free(graph->adjacencyList);
    free(graph);
}
