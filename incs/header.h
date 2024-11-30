// Librerías.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

// Macros.
#define MAX_USERS 50             // Cantidad máxima de usuarios.
#define MAX_NAME_LENGTH 50       // Largo máximo del nombre del usuario.
#define MAX_GENDER 10            // Largo máximo de genero (masculino - femenino).
#define MAX_HOBBIES 10           // Cantidad máxima de hobbies.
#define MAX_HOBBIE_LENGTH 50     // Largo máximo del nombre del hobbie.
#define MAX_POST 10              // Cantidad máxima de mensajes.
#define MAX_POST_LENGTH 256      // Largo máximo del mensaje.
#define MAX_FILE_LINES 100       // Cantidad máxima de líneas dentro del archivo.
#define MAX_AGE 60               // Edad máxima de un usuario.
#define MIN_AGE 18               // Edad mínima de un usuario.
#define MAX_PERS_LENGTH 50       // Largo máximo de la personalidad.
#define NUM_PERSONALITY_TYPES 16 // Número de tipos de personalidad.
#define HASH_SIZE 19             // Tamaño de la tabla hash.
#define MAX_USER_POST 1          // Maximo de posts que puede hacer un usuario

// Macros de  colores
#define RESET "\033[0m"   // Default
#define GREEN "\033[32m"  // Verde
#define YELLOW "\033[33m" // Amarillo
#define CYAN "\033[36m"   // Cian
#define RED "\033[31m"    // Rojo

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
    char **user_names;    // Nombre de usuario
} Graph;

/* Estructura de Publicaciones */
typedef struct Post
{
    int post_Id;                    // Identificador único de publicación
    int user_Id;                    // ID del usuario que crea la publicación
    char username[MAX_NAME_LENGTH]; // Nombre de usuario
    char content[MAX_POST_LENGTH];  // Contenido de la publicación
    time_t timestamp;               // Marca de tiempo de la publicación
    int likes;                      // Número de likes
    int comments_count;             // Número de comentarios
    struct Post *next;              // Enlace a siguiente publicación
} Post;

/* Estructura de Lista de Publicaciones */
typedef struct Post_List
{
    Post *head;    // Apuntador a la primera publicación
    int postCount; // Número total de publicaciones
} Post_List;

/* Funciones dedicadas a la creación,inicializacion, administracion de post  */
void init_post_list(Post_List *);
Post *create_post(int, const char *, const char *);
void publish_post(Post_List *, const User *, const char *);
void display_all_posts(const Post_List *);
void display_user_posts(const Post_List *, int);
void free_all_posts(Post_List *);
void load_post_templates(char post_templates[MAX_FILE_LINES][MAX_POST_LENGTH], int *);
void generate_random_posts(User users[MAX_USERS], int, int, Post_List *);

/* Funciones dedicadas a la creación de Usuarios */
void load_file(const char *, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int *);
void generate_random_users(User *, int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int, char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);
void generate_random_hobbies(char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int);
void generate_random_personality(char *, char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);
void print_users(const User *);

/* Funciones dedicadas a la Similitud */
double calculate_jaccard_similarity(const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, const char hobbies2[MAX_HOBBIE_LENGTH][MAX_HOBBIE_LENGTH], int, int, int, const char *, const char *);
void find_common_hobbies(const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int);
void recommend_users(const User users[MAX_USERS], int);

// auxiliares
double calculate_age_weight(int, int);
const char *get_age_compatibility_level(int);
double calculate_personality_multiplier(int, int);
void explain_personality_compatibility(const User *, const User *);
int get_personality_group(const char *);

/* Funciones dedicadas al historial de Usuarios */
void user_count_from_log(int *);
int log_check();
void log_input(User users[]);
void log_clean();
void log_output(const User *);

/* Funciones dedicadas a la conexiones del Grafo */
Graph *initialize_graph(int, User *);
void add_connection(Graph *, int, int);
void display_graph(Graph *);
void free_graph(Graph *);
void create_connections(const User users[MAX_USERS], int, Graph *, double);

/* Funciones dedicadas a la impresión del Grafo en formato EPS */
void generate_eps_graph(Graph *, const char *);
void transform_eps_png(const char *);
