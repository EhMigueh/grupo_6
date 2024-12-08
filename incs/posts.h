#ifndef POSTS_H
#define POSTS_H
/** 
 * @file posts.h
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras. Benjamin Sanhueza y Johann Fink
 * @brief Definición de funciones y estructuras para manejar las publicaciones de usuarios.
 */
#include "users.h"

/* Constantes Relacionadas a los posts */
#define MAX_POST 10              
#define MAX_POST_LENGTH 256      
#define MAX_FILE_LINES 100   
#define MAX_POSTS 3              

/** 
 * @struct Post
 * @brief Estructura que representa una publicación de un usuario.
 * Esta estructura contiene la información relacionada con una publicación, incluyendo un identificador único,
   el ID del usuario que la crea, el contenido de la publicación, una marca de tiempo, y un puntero al siguiente 
   post en una lista enlazada.
 */
/* Estructura de Publicaciones */
typedef struct Post
{
    int post_Id;                    // Identificador único de publicación.
    int user_Id;                    // ID del usuario que crea la publicación.
    char username[MAX_NAME_LENGTH]; // Nombre de usuario.
    char content[MAX_POST_LENGTH];  // Contenido de la publicación.
    time_t timestamp;               // Marca de tiempo de la publicación.
    struct Post *next;              // Enlace a siguiente publicación.
} Post;


/** 
 * @struct Post_List
 * @brief Estructura que representa una lista de publicaciones.
 * Esta estructura contiene un puntero a la cabeza de la lista de publicaciones y el contador de publicaciones.
 */
/* Estructura de Lista de Publicaciones */
typedef struct Post_List
{
    Post *head;    // Apuntador a la primera publicación.
    int postCount; // Número total de publicaciones.
} Post_List;

/* Funciones dedicadas a la creación,inicializacion, administracion de post  */

/**
 * @brief Inicializa una lista de publicaciones.
 * Esta función inicializa la lista de publicaciones configurando el puntero `head` a NULL y el contador 
 * postCount` a 0.
 * @param list Puntero a la lista de publicaciones a inicializar.
 */
void init_post_list(Post_List *);

/**
 * @brief Crea una nueva publicación.
 * Esta función crea una nueva publicación, asignando un ID único, y copiando el nombre de usuario y contenido 
 * proporcionado. La marca de tiempo es generada al momento de la creación.
 * @param userId ID del usuario que publica.
 * @param username Nombre del usuario.
 * @param content Contenido de la publicación.
 * @return Un puntero a la nueva publicación creada.
 */
Post *create_post(int, const char *, const char *);

/**
 * @brief Publica un nuevo post en la lista.
 * Esta función agrega una nueva publicación al final de la lista de publicaciones.
 * @param postList Puntero a la lista de publicaciones.
 * @param user Puntero a la estructura del usuario que publica.
 * @param content Contenido de la publicación.
 */
void publish_post(Post_List *, const User *, const char *);

/**
 * @brief Muestra todas las publicaciones en la lista.
 * Esta función imprime el contenido de todas las publicaciones almacenadas en la lista.
 * @param postList Puntero a la lista de publicaciones.
 */
void display_all_posts(const Post_List *);

/**
 * @brief Libera la memoria ocupada por todas las publicaciones de la lista.
 * Esta función recorre la lista de publicaciones y libera la memoria de cada publicación.
 * @param postList Puntero a la lista de publicaciones.
 */
void free_all_posts(Post_List *);

/**
 * @brief Carga plantillas de publicaciones desde un archivo.
 * Esta función carga las plantillas de publicaciones desde un archivo de texto, donde cada línea corresponde a una plantilla.
 * @param post_templates Arreglo donde se almacenarán las plantillas de publicaciones.
 * @param count Número de plantillas cargadas.
 */
void load_post_templates(char post_templates[MAX_FILE_LINES][MAX_POST_LENGTH], int *);

/**
 * @brief Genera publicaciones aleatorias para un conjunto de usuarios.
 * Esta función genera un número de publicaciones aleatorias para los usuarios en el arreglo `users`.
 * @param users Arreglo de usuarios para generar las publicaciones.
 * @param numPosts Número de publicaciones a generar.
 * @param postList Puntero a la lista de publicaciones.
 */
void generate_random_posts(User users[MAX_USERS], int, Post_List *);

/**
 * @brief Genera una marca de tiempo aleatoria.
 * Esta función genera una marca de tiempo aleatoria para simular el momento de publicación de una publicación.
 * @return La marca de tiempo aleatoria generada.
 */
time_t generate_random_timestamp();

#endif