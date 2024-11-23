#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_USERS 50         // Cantidad máxima de usuarios.
#define MAX_NAME_LENGTH 50   // Largo máximo del nombre del usuario.
#define MAX_GENDER 10        // Largo máximo de genero (masculino - femenino).
#define MAX_HOBBIES 10       // Cantidad máxima de hobbies.
#define MAX_HOBBIE_LENGTH 50 // Largo máximo del nombre del hobbie.
#define MAX_POST 10          // Cantidad máxima de mensajes.
#define MAX_POST_LENGTH 256  // Largo máximo del mensaje.
#define MAX_FILE_LINES 100   // Cantidad máxima de líneas dentro del archivo.
#define MAX_AGE 60           // Edad máxima de un usuario.

/* Estructura del Usuario */
typedef struct User
{
    int id;                                       // Id de usuario.
    char username[MAX_NAME_LENGTH];               // Nombre del usuario.
    int age;                                      // Edad del usuario.
    char gender[MAX_GENDER];                      // Género del usuario.
    char hobbies[MAX_HOBBIES][MAX_HOBBIE_LENGTH]; // Hobbies del usuario.
} User;

/*
typedef struct Node
{
    int id;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numUsers;
    Node **adjacencyList;
} Graph;
*/

/* Funciones dedicadas a la creación de Usuarios */
void load_file(const char *, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int *);
void generate_random_users(User *, int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int);
void generate_random_hobbies(char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int);
void print_users(const User *);

/* Funciones dedicadas a la Similitud */
double calculate_jaccard_similarity(const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int);
void find_common_hobbies(const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int);
void recommend_users(const User users[MAX_USERS], int);

/*
Graph *initializeGraph(int numUsers);
void addConnection(Graph *graph, int user1, int user2);
void displayGraph(Graph *graph);
void freeGraph(Graph *graph);
void loadConnectionsFromFile(Graph *graph, const char *filename);
*/
