#ifndef GRAPH_H
#define GRAPH_H

#include "users.h"

/* Estructura del Nodo */
typedef struct Node
{
    int id;            // ID del usuario conectado.
    int weight;        // Peso de la conexión
    struct Node *next; // Apuntador al siguiente nodo.
} Node;

/* Estructura del Grafo */
typedef struct Graph
{
    int numUsers;         // Número de usuarios.
    Node **adjacencyList; // Lista de adyacencia.
    char **user_names;    // Nombre de usuario
} Graph;

/* Funciones dedicadas a la conexiones del Grafo */
Graph *initialize_graph(int, User *);
void add_connection(Graph *, int, int);
void display_graph(Graph *, int);
void print_path(int, int *, Graph *);
void free_graph(Graph *);
void create_connections(const User users[MAX_USERS], int, Graph *, double);

/* Funciones dedicadas a la busqueda de usuario con mas amigo*/
int find_user_with_most_friends(Graph *);
void print_friends_of_user(Graph *, int);

/* Funciones dedicadas a la impresión del Grafo en formato EPS */
void generate_eps_graph(Graph *, const char *);
void transform_eps_png(const char *);

#endif