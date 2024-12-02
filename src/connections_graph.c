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

    // Agregar nombres de usuarios.
    graph->user_names = malloc(numUsers * sizeof(char *));
    for (int i = 0; i < numUsers; i++)
        graph->user_names[i] = strdup(users[i].username);

    // Retornar el grafo inicializado.
    return graph;
}

// Función para agregar una conexión entre dos usuarios.
void add_connection(Graph *graph, int user1, int user2)
{
    // Verificar si el grafo está inicializado.
    if (!graph)
    {
        fprintf(stderr, "Grafo no inicializado. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user2;
    newNode->weight = 1;
    newNode->next = graph->adjacencyList[user1]; // Conecta el primer usuario.
    graph->adjacencyList[user1] = newNode;

    newNode = (Node *)malloc(sizeof(Node));
    newNode->id = user1;
    newNode->weight = 1;
    newNode->next = graph->adjacencyList[user2]; // Conecta el segundo usuario.
    graph->adjacencyList[user2] = newNode;
}

// Función para mostrar las conexiones del grafo usando el algoritmo Dijkstra.
void display_graph(Graph *graph, int source)
{
    double distances[MAX_USERS];
    int previous[MAX_USERS];
    int visited[MAX_USERS] = {0};

    for (int i = 0; i < graph->numUsers; i++)
    {
        distances[i] = INFINITY;
        previous[i] = -1;
    }

    distances[source] = 0;

    for (int count = 0; count < graph->numUsers; count++) // Algoritmo Dijkstra
    {
        int minIndex = -1;
        double minDistance = INFINITY;

        for (int i = 0; i < graph->numUsers; i++)
            if (!visited[i] && distances[i] < minDistance)
            {
                minDistance = distances[i];
                minIndex = i;
            }

        if (minIndex == -1)
            break;

        visited[minIndex] = 1;
        Node *current = graph->adjacencyList[minIndex];

        while (current)
        {
            int neighbor = current->id;
            int weight = current->weight;

            if (!visited[neighbor] && distances[minIndex] + weight < distances[neighbor])
            {
                distances[neighbor] = distances[minIndex] + weight;
                previous[neighbor] = minIndex;
            }

            current = current->next;
        }
    }

    int farthestNode = -1;
    int maxDistance = -1;

    for (int i = 0; i < graph->numUsers; i++)
        if (distances[i] != INFINITY && distances[i] > maxDistance)
        {
            maxDistance = distances[i];
            farthestNode = i;
        }

    if (farthestNode != -1)
    {
        fprintf(stdout, GREEN "%-10s: " RESET, graph->user_names[source]);
        fprintf(stdout, "Distancia: %d , Camino: ", maxDistance);
        print_path(farthestNode, previous, graph);
        fprintf(stdout, "\n");
    }
    else
        fprintf(stdout, RED "No se encontraron caminos desde '%s'.\n" RESET, graph->user_names[source]);
}

// Función para mostrar el camino desde el nodo fuente.
void print_path(int target, int *previous, Graph *graph)
{
    if (previous[target] == -1)
    {
        fprintf(stdout, "%s", graph->user_names[target]);
        return;
    }
    print_path(previous[target], previous, graph);
    fprintf(stdout, " -> %s", graph->user_names[target]);
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
