#ifndef POSTS_H
#define POSTS_H

#include "users.h"

// Constantes dedicadas a los post
#define MAX_POST 10              
#define MAX_POST_LENGTH 256      
#define MAX_FILE_LINES 100       
#define MAX_POSTS 3              

/* Estructura de Publicaciones */
typedef struct Post
{
    int post_Id;                    // Identificador único de publicación
    int user_Id;                    // ID del usuario que crea la publicación
    char username[MAX_NAME_LENGTH]; // Nombre de usuario
    char content[MAX_POST_LENGTH];  // Contenido de la publicación
    time_t timestamp;               // Marca de tiempo de la publicación
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
void free_all_posts(Post_List *);
void load_post_templates(char post_templates[MAX_FILE_LINES][MAX_POST_LENGTH], int *);
void generate_random_posts(User users[MAX_USERS], int, Post_List *);
time_t generate_random_timestamp();


#endif