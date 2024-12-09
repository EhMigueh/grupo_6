#ifndef POSTS_H
#define POSTS_H

/**
 * @file posts.h
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras, Benjamín Sanhueza y Johann Fink
 * @brief Definición de funciones y estructuras para manejar las publicaciones de usuarios.
 *
 * Contiene los prototipos de las funciones dedicadas a la creación, publicación y visualización de publicaciones.
 */
#include "users.h"

/**
 * Macros utilizadas en el proyecto.
 * @code
 * #define MAX_POST 10
 * #define MAX_POST_LENGTH 256
 * #define MAX_FILE_LINES 100
 * #define MAX_POSTS 3
 * @endcode
 */
#define MAX_POST 10
#define MAX_POST_LENGTH 256
#define MAX_FILE_LINES 100
#define MAX_POSTS 3

/**
 * @struct Post
 * @brief Estructura que representa una publicación de un usuario.
 * Esta estructura contiene la información relacionada con una publicación, incluyendo un identificador único,
 * el ID del usuario que la crea, el contenido de la publicación, una marca de tiempo, y un puntero al siguiente
 * post en una lista enlazada.
 * @code
 * typedef struct Post
 * {
 *      int post_Id;
 *      int user_Id;
 *      char username[MAX_NAME_LENGTH];
 *      char content[MAX_POST_LENGTH];
 *      time_t timestamp;
 *      struct Post *next;
 * } Post;
 * @endcode
 */
typedef struct Post
{
  int post_Id;
  int user_Id;
  char username[MAX_NAME_LENGTH];
  char content[MAX_POST_LENGTH];
  time_t timestamp;
  struct Post *next;
} Post;

/**
 * @struct Post_List
 * @brief Estructura que representa una lista de publicaciones.
 * Esta estructura contiene un puntero a la cabeza de la lista de publicaciones y el contador de publicaciones.
 * @code
 * typedef struct Post_List
 * {
 *      Post *head;
 *      int postCount;
 * } Post_List;
 * @endcode
 */
/* Estructura de Lista de Publicaciones */
typedef struct Post_List
{
  Post *head;
  int postCount;
} Post_List;

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