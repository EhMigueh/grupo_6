#ifndef GRAPH_H
#define GRAPH_H

/**
 * @file graph.h
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras. Benjamin Sanhueza y Johann Fink
 * @brief Prototipos de funciones para la conexion entre usuarios (amistad)
 *
 * Contiene los prototipos de las funciones dedicadas a la creación de conexiones entre usuarios
 */

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

/**
 * @brief Inicializa un grafo con un número específico de usuarios y sus nombres.
 * Reserva memoria y configura una estructura de grafo, inicializando la lista de adyacencia y copiando los nombres de los usuarios.
 * @param numUsers Número total de usuarios en el grafo.
 * @param users Puntero al arreglo de usuarios, cada uno con su nombre.
 * @return Puntero al grafo inicializado.
 */
Graph *initialize_graph(int, User *);

/**
 * @brief Agrega una conexión bidireccional entre dos usuarios en el grafo.
 * Inserta nodos en la lista de adyacencia para conectar a dos usuarios,representando una relación de amistad.
 * @param graph Puntero al grafo donde se desea agregar la conexión.
 * @param user1 Identificador del primer usuario.
 * @param user2 Identificador del segundo usuario.
 */
void add_connection(Graph *, int, int);

/**
 * @brief Muestra las conexiones del grafo utilizando el algoritmo de Dijkstra. 
 * Calcula las rutas más cortas desde un usuario específico al resto utilizando Dijkstra y muestra la distancia y el camino hacia el nodo más lejano alcanzable.
 * @param graph Puntero al grafo.
 * @param source Identificador del usuario desde el cual calcular las rutas.
 */
void display_graph(Graph *, int);

/**
 * @brief Imprime el camino desde un nodo fuente a un nodo destino.
 * Muestra la secuencia de nombres de usuarios que forman la ruta más corta calculada previamente.
 * @param target Identificador del nodo destino.
 * @param previous Arreglo con los nodos previos en el camino calculado por Dijkstra.
 * @param graph Puntero al grafo que contiene los nombres de los usuarios.
 */
void print_path(int, int *, Graph *);

/**
 * @brief Libera toda la memoria asociada con el grafo.
 * Elimina todas las estructuras dinámicas asociadas con la lista de adyacencia y los nombres de los usuarios.
 * @param graph Puntero al grafo a liberar.
 */
void free_graph(Graph *);

/**
 * @brief Genera conexiones aleatorias entre usuarios en el grafo.
 * @param users Arreglo de usuarios disponibles.
 * @param numUsers Número total de usuarios.
 * @param graph Puntero al grafo donde se generarán las conexiones.
 * @param density Densidad de conexiones (valor entre 0 y 1).
 */
void create_connections(const User users[MAX_USERS], int, Graph *, double);

/* Funciones dedicadas a la busqueda de usuario con mas amigo*/
int find_user_with_most_friends(Graph *);
void print_friends_of_user(Graph *, int);

/* Funciones dedicadas a la impresión del Grafo en formato EPS */
void generate_eps_graph(Graph *, const char *);
void transform_eps_png(const char *);

#endif