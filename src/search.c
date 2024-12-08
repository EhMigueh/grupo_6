/**
 * @file search.c
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras, Benjamin Sanhueza y Johann Fink
 * @brief Funciones para la busqueda del usuario con mas amigos
 */
#include "main.h"
/**
 * @brief Encuentra al usuario con más amigos en el grafo.
 * Recorre el grafo y cuenta las conexiones (amigos) de cada usuario, devolviendo el índice del usuario con más amigos.
 * @param graph Puntero al grafo de usuarios donde se buscan los amigos.
 * @return El índice del usuario con más amigos. Si no se encuentra ningún usuario, devuelve -1.
 */
int find_user_with_most_friends(Graph *graph)
{
    int maxFriends = -1; // Mayor número de amigos encontrado
    int userIndex = -1;  // Índice del usuario con más amigos
    int i;

    if (!graph || graph->numUsers == 0)
    {
        fprintf(stderr, RED "El grafo está vacío o no inicializado.\n" RESET);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < graph->numUsers; i++)
    {
        int friendCount = 0;
        Node *current = graph->adjacencyList[i];

        // Contar las conexiones del usuario actual
        while (current)
        {
            friendCount++;
            current = current->next;
        }

        // Actualizar si el usuario actual tiene más amigos
        if (friendCount > maxFriends)
        {
            maxFriends = friendCount;
            userIndex = i;
        }
    }

    if (userIndex != -1)
        fprintf(stdout, GREEN "\nEl usuario con más amigos es: %s con %d amigos.\n\n" RESET, graph->user_names[userIndex], maxFriends);
    else
        fprintf(stdout, YELLOW "No se encontraron usuarios con amigos.\n" RESET);

    return userIndex;
}

/**
 * @brief Imprime los amigos de un usuario dado en el grafo.
 * Muestra en pantalla los amigos (conexiones) del usuario especificado por su índice en el grafo.
 * @param graph Puntero al grafo que contiene la información de los usuarios y sus amigos.
 * @param userIndex Índice del usuario en el grafo del cual se desean imprimir los amigos.
 */

void print_friends_of_user(Graph *graph, int userIndex)
{
    if (!graph || userIndex < 0 || userIndex >= graph->numUsers)
    {
        fprintf(stderr, RED "Índice de usuario inválido o grafo no inicializado.\n" RESET);
        return;
    }

    Node *current = graph->adjacencyList[userIndex];
    fprintf(stdout, CYAN "Amigos de %s:\n" RESET, graph->user_names[userIndex]);

    while (current)
    {
        fprintf(stdout, "- %s\n", graph->user_names[current->id]);
        current = current->next;
    }
}
