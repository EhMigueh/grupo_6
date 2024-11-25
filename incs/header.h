// Librerías.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Macros.
#define MAX_USERS 50         // Cantidad máxima de usuarios.
#define MAX_NAME_LENGTH 50   // Largo máximo del nombre del usuario.
#define MAX_GENDER 10        // Largo máximo de genero (masculino - femenino).
#define MAX_HOBBIES 10       // Cantidad máxima de hobbies.
#define MAX_HOBBIE_LENGTH 50 // Largo máximo del nombre del hobbie.
#define MAX_POST 10          // Cantidad máxima de mensajes.
#define MAX_POST_LENGTH 256  // Largo máximo del mensaje.
#define MAX_FILE_LINES 100   // Cantidad máxima de líneas dentro del archivo.
#define MAX_AGE 60           // Edad máxima de un usuario.
#define MIN_AGE 18           // Edad mínima de un usuario.
#define MAX_PERS_LENGTH 50   // Largo máximo de la personalidad.

/* Estructura del Usuario */
typedef struct User
{
    int id;                                       // Id de usuario.
    char username[MAX_NAME_LENGTH];               // Nombre del usuario.
    int age;                                      // Edad del usuario.
    char gender[MAX_GENDER];                      // Género del usuario.
    char hobbies[MAX_HOBBIES][MAX_HOBBIE_LENGTH]; // Hobbies del usuario.
    char personality[MAX_PERS_LENGTH];            // Personalidad del usuario.
} User;

/* Estructura de Afinidad */
typedef struct
{
    int user_index;    // Índice del usuario con el que se encontró la coincidencia.
    double similarity; // Similitud calculada entre los hobbies de los dos usuarios (Índice de Jaccard).
    int age_diff;      // Diferencia de edad entre los dos usuarios en años.
} Match;

typedef struct Node
{
    int id;            // ID del usuario conectado.
    struct Node *next; // Apuntador al siguiente nodo.
} Node;

typedef struct Graph
{
    int numUsers;         // Número de usuarios.
    Node **adjacencyList; // Lista de adyacencia.
} Graph;

/* Funciones dedicadas a la creación de Usuarios */
void load_file(const char *, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int *);
void generate_random_users(User *, int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int, char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);
void generate_random_hobbies(char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int);
void generate_random_personality(char *, char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);
void print_users(const User *);

/* Funciones dedicadas a la Similitud */
double calculate_jaccard_similarity(const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, const char hobbies2[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, int, int);
void find_common_hobbies(const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int);
void recommend_users(const User users[MAX_USERS], int);
double calculate_age_weight(int, int);
const char *get_age_compatibility_level(int);

/* Funciones dedicadas al historial de Usuarios */
void get_users_log(const User *);

/* Funciones dedicadas a la conexiones del Grafo */
Graph *initializeGraph(int);
void addConnection(Graph *, int, int);
void displayGraph(Graph *);
void freeGraph(Graph *);
void create_connections(const User users[MAX_USERS], int, Graph *, double);
