// Librerías.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

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
#define NUM_PERSONALITY_TYPES 16
#define HASH_SIZE 19
// Macros de personalizacion
#define RESET "\033[0m"  // Color predeterminado
#define GREEN "\033[32m" // Color verde para los out

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

/* Estructura del Nodo */
typedef struct Node
{
    int id;            // ID del usuario conectado.
    struct Node *next; // Apuntador al siguiente nodo.
} Node;

/* Estructura del Grafo */
typedef struct Graph
{
    int numUsers;         // Número de usuarios.
    Node **adjacencyList; // Lista de adyacencia.
    char **user_names; // Nombre de usuario
} Graph;



// Funciones auxiliares de hash
void initialize_personality_hash();
unsigned int hash(const char *str);
int get_personality_group(const char *personality);


/* Funciones dedicadas a la creación de Usuarios */
void load_file(const char *, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int *);
void generate_random_users(User *, int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int, char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);
void generate_random_hobbies(char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int);
void generate_random_personality(char *, char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);
void print_users(const User *);

/* Funciones dedicadas a la Similitud */
double calculate_jaccard_similarity(const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int count1, const char hobbies2[MAX_HOBBIE_LENGTH][MAX_HOBBIE_LENGTH], int count2, int age1, int age2, const char *personality1, const char *personality2);
void find_common_hobbies(const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int);
void recommend_users(const User users[MAX_USERS], int);
double calculate_age_weight(int, int);
const char *get_age_compatibility_level(int);
double calculate_personality_multiplier(int group1, int group2);


/* Funciones dedicadas al historial de Usuarios */
int user_count_from_log();
void log_check();
void log_input();
void log_clean();
void log_output(const User *);


/* Funciones dedicadas a la conexiones del Grafo */
Graph *initialize_graph(int numUsers, User *users);
void add_connection(Graph *, int, int);
void display_graph(Graph *);
void free_graph(Graph *);
void create_connections(const User users[MAX_USERS], int, Graph *, double);

/* Funciones dedicadas a la impresión del Grafo en formato EPS */
void generate_eps_graph(Graph *, const char *);
void transform_eps_png(const char *);
