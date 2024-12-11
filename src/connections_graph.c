/**
 * @file connections_graph.c
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras. Benjamin Sanhueza y Johann Fink-
 * @brief Funciones para la gestión y visualización de grafos de conexiones entre usuarios.
 */

#include "main.h"

/**
 * @brief Inicializa un grafo con un número específico de usuarios y sus nombres.
 * @param numUsers Número total de usuarios en el grafo.
 * @param users Puntero al arreglo de usuarios, cada uno con su nombre.
 * @return Puntero al grafo inicializado.
*/
// Función para inicializar el Grafo.
Graph *initialize_graph(int numUsers, User *users)
{
     /**
    * @brief Inicializa un grafo con un número específico de usuarios y sus nombres.
    * @code 
    * if (numUsers <= 0) ->error
    * Graph *graph = (Graph *)malloc(sizeof(Graph));
    * graph->numUsers = numUsers;
    * graph->adjacencyList = (Node **)calloc(numUsers + 1, sizeof(Node *));
    * graph->user_names = malloc(numUsers * sizeof(char *));
    * for (int i = 0; i < numUsers; i++)
        Agregar nombres de usuarios.
    * return graph;

    * @endcode
    */
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
/**
 * @brief Agrega una conexión bidireccional entre dos usuarios en el grafo.
 * @param graph Puntero al grafo donde se agregarán las conexiones.
 * @param user1 Identificador del primer usuario.
 * @param user2 Identificador del segundo usuario. 
 */
void add_connection(Graph *graph, int user1, int user2)
{
     /**
    * @brief Agrega una conexión bidireccional entre dos usuarios en el grafo.
    * @code 
    * if (!graph) ->error
    * Node *newNode = (Node *)malloc(sizeof(Node));
    * newNode->id = user2;
    * newNode->weight = 1;
    * newNode->next = graph->adjacencyList[user1]; 
    * graph->adjacencyList[user1] = newNode;
    * newNode = (Node *)malloc(sizeof(Node));
    * newNode->id = user1;
    * newNode->weight = 1;
    * newNode->next = graph->adjacencyList[user2]; 
    * graph->adjacencyList[user2] = newNode;
    * @endcode
    */
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
/**
 * @brief Muestra las conexiones del grafo y el camino más largo desde un nodo fuente utilizando Dijkstra.
 * 
 * @param graph Puntero al grafo cuyas conexiones se mostrarán.
 * @param source Identificador del nodo fuente desde el cual calcular las distancias.
 */
// Función para mostrar las conexiones del grafo usando el algoritmo Dijkstra.
void display_graph(Graph *graph, int source)
{
     /**
    * @brief Muestra las conexiones del grafo y el camino más largo desde un nodo fuente utilizando Dijkstra.
    * @code 
    * double distance[MAX_USERS];
    * int prev_node[MAX_USERS];
    * int visited_node[MAX_USERS] = {0};
    * for(int i=0;i<graph->numUsers;i++)
    *   Aqui se inicializan las distancias de los nodos desde el nodo fuente y cual es el nodo previo
    * distance[source]=0;
    * for(int i=0;i<graph->numUsers;i++)
    *    Algoritmo Dijkstra
    * int farthest_node=-1;
    * int max_distance=-1;
    *
    * @endcode
    */
    double distance[MAX_USERS];
    int prev_node[MAX_USERS];
    int visited_node[MAX_USERS] = {0};

    for(int i=0;i<graph->numUsers;i++) //Aqui se inicializan las distancias de los nodos desde el nodo fuente y cual es el nodo previo
    {
        distance[i]=INFINITY;
        prev_node[i]=-1;
    }
    distance[source]=0;

    for(int i=0;i<graph->numUsers;i++) // Algoritmo Dijkstra
    {
        int min_index=-1;
        double min_distance=INFINITY;

        for(int i=0;i<graph->numUsers;i++)
            if(!visited_node[i]&&distance[i]<min_distance)
            {
                min_distance=distance[i];
                min_index=i;
            }
        if(min_index==-1)
            break;
        visited_node[min_index]=1;
        Node *current=graph->adjacencyList[min_index];

        while(current)
        {
            int neighbor=current->id;
            int weight=current->weight;

            if(!visited_node[neighbor]&&distance[min_index]+weight<distance[neighbor])
            {
                distance[neighbor]=distance[min_index]+weight;
                prev_node[neighbor]=min_index;
            }

            current=current->next;
        }
    }

    int farthest_node=-1;
    int max_distance=-1;

    for(int i=0;i<graph->numUsers;i++)
        if(distance[i]!=INFINITY&&distance[i]>max_distance)
        {
            max_distance=distance[i];
            farthest_node=i;
        }

    if(farthest_node!=-1)
    {
        fprintf(stdout,GREEN"%-10s: "RESET,graph->user_names[source]);
        fprintf(stdout,"Distancia: %d , Camino: ",max_distance);
        print_path(farthest_node,prev_node,graph);
        fprintf(stdout,"\n");
    }
    else
        fprintf(stdout,RED"No se encontraron caminos desde '%s'.\n"RESET,graph->user_names[source]);
}
/**
 * @brief Muestra el camino desde un nodo fuente hasta un objetivo.
 * @param target Nodo objetivo.
 * @param prev_node Arreglo con los predecesores de cada nodo.
 * @param graph Puntero al grafo.
 */
void print_path(int target, int *prev_node, Graph *graph)
{
     /**
    * @brief Muestra el camino desde un nodo fuente hasta un objetivo.
    * @code 
    * if (prev_node[target] == -1)
    *   fprintf(stdout, "%s", graph->user_names[target]);
    *   return;
    * print_path(prev_node[target], prev_node, graph);
    * fprintf(stdout, " -> %s", graph->user_names[target]);
    * @endcode
    */
    if (prev_node[target] == -1)
    {
        fprintf(stdout, "%s", graph->user_names[target]);
        return;
    }
    print_path(prev_node[target], prev_node, graph);
    fprintf(stdout, " -> %s", graph->user_names[target]);
}
/**
 * @brief Libera toda la memoria asignada al grafo. 
 * @param graph Puntero al grafo a liberar.
 */
void free_graph(Graph *graph)
{
     /**
    * @brief Libera toda la memoria asignada al grafo
    * @code 
    * for (int i = 0; i < graph->numUsers; i++)
    *   libera nombres de usuarios
    * free(graph->user_names);
    * free(graph->adjacencyList);
    * free(graph);
    * @endcode
    */
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
