#include "header.h"

// Inicializar lista de publicaciones.
void init_post_list(Post_List *post_list)
{
    post_list->head = NULL;
    post_list->postCount = 0;
}

// Crear una nueva publicación.
Post *create_post(int user_Id, const char *username, const char *content)
{
    // Validar longitud de contenido.
    if (strlen(content) >= MAX_POST_LENGTH)
    {
        fprintf(stderr, "Error: Contenido de publicación demasiado largo.\n");
        return NULL;
    }

    Post *newPost = malloc(sizeof(Post));
    if (!newPost)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para la publicación.\n");
        return NULL;
    }

    // Generar ID único de publicación
    static int post_Id_Counter = 1;
    newPost->post_Id = post_Id_Counter++;

    // Copiar datos con seguridad
    newPost->user_Id = user_Id;
    strncpy(newPost->username, username, MAX_NAME_LENGTH - 1);
    newPost->username[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(newPost->content, content, MAX_POST_LENGTH - 1);
    newPost->content[MAX_POST_LENGTH - 1] = '\0';

    // Establecer marca de tiempo
    newPost->timestamp = time(NULL);
    newPost->likes = 0;
    newPost->comments_count = 0;
    newPost->next = NULL;

    return newPost;
}

// Publicar en el muro global (pasar la lista de publicaciones como parámetro)
void publish_post(Post_List *post_list, const User *user, const char *content)
{
    Post *newPost = create_post(user->id, user->username, content);
    if (newPost)
    {
        // Agregar al inicio de la lista global
        newPost->next = post_list->head;
        post_list->head = newPost;
        post_list->postCount++;
    }
}

// Mostrar todas las publicaciones de la red social
void display_all_posts(const Post_List *post_list)
{
    fprintf(stdout, RED "\nPublicaciones:\n\n" RESET);

    Post *current = post_list->head;
    while (current)
    {
        // Formatear timestamp legible
        char timeStr[64];
        struct tm *tm_info = localtime(&current->timestamp);
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);

        fprintf(stdout, CYAN "Publicación %d" RESET "\n", current->post_Id);
        fprintf(stdout, GREEN "Usuario: %s (ID: %d)\n" RESET, current->username, current->user_Id);
        fprintf(stdout, YELLOW "Contenido: %s\n" RESET, current->content);
        fprintf(stdout, "Fecha: %s\n", timeStr);

        current = current->next;
    }
}

// Mostrar publicaciones de un usuario específico
void displayUserPosts(const Post_List *post_list, int user_Id)
{
    fprintf(stdout, YELLOW "\n=== Publicaciones de Usuario %d ===" RESET "\n", user_Id);

    Post *current = post_list->head;
    int userPostCount = 0;

    while (current)
    {
        if (current->user_Id == user_Id)
        {
            // Formatear timestamp legible
            char timeStr[64];
            struct tm *tm_info = localtime(&current->timestamp);
            strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);

            printf(CYAN "--- Publicación %d ---" RESET "\n", current->post_Id);
            printf("Contenido: %s\n", current->content);
            printf("Fecha: %s\n", timeStr);
            printf("Likes: %d\n", current->likes);
            printf("Comentarios: %d\n\n", current->comments_count);

            userPostCount++;
        }
        current = current->next;
    }

    if (userPostCount == 0)
        fprintf(stdout, "No hay publicaciones para este usuario.\n");
}

// Dar like a una publicación
int likePost(Post_List *post_list, int post_Id)
{
    Post *current = post_list->head;

    while (current)
    {
        if (current->post_Id == post_Id)
        {
            current->likes++;
            fprintf(stdout, GREEN "Has dado like a la publicación %d" RESET "\n", post_Id);
            return 1;
        }
        current = current->next;
    }

    fprintf(stdout, RED "Publicación no encontrada." RESET "\n");
    return 0;
}

// Liberar memoria de las publicaciones
void free_all_posts(Post_List *post_list)
{
    Post *current = post_list->head;

    while (current)
    {
        Post *temp = current;
        current = current->next;
        free(temp);
    }

    post_list->head = NULL;
    post_list->postCount = 0;
}

// Función para cargar publicaciones desde un archivo
void load_post_templates(char post_templates[MAX_FILE_LINES][MAX_POST_LENGTH], int *post_count)
{
    FILE *file = fopen("post_templates.txt", "r");
    if (!file)
    {
        fprintf(stderr, "Error al abrir el archivo post_templates.txt, saliendo...\n");
        exit(EXIT_FAILURE);
    }

    *post_count = 0;
    char line[MAX_POST_LENGTH];

    while (*post_count < MAX_FILE_LINES && fgets(line, sizeof(line), file))
    {
        size_t len = strcspn(line, "\n");
        line[len] = '\0';

        if (len >= MAX_POST_LENGTH)
            len = MAX_POST_LENGTH - 1;

        memcpy(post_templates[*post_count], line, len);
        post_templates[*post_count][len] = '\0';
        (*post_count)++;
    }

    fclose(file);
}

void generate_random_posts(User users[MAX_USERS], int num_users, int max_posts_per_user, Post_List *post_list)
{
    char post_templates[MAX_FILE_LINES][MAX_POST_LENGTH];
    int post_template_count = 0;

    // Cargar plantillas de publicaciones
    load_post_templates(post_templates, &post_template_count);

    if (post_template_count == 0)
    {
        fprintf(stderr, "No se encontraron plantillas de publicaciones.\n");
        return;
    }

    // Seleccionar un usuario aleatorio
    int random_user_index = rand() % num_users;

    // Número aleatorio de publicaciones para este usuario (1-max_posts_per_user)
    int num_posts = rand() % max_posts_per_user + 1;

    for (int j = 0; j < num_posts; j++)
    {
        // Seleccionar una plantilla de publicación aleatoria
        int template_index = rand() % post_template_count;

        // Publicar utilizando la plantilla seleccionada para el usuario aleatorio
        publish_post(post_list, &users[random_user_index], post_templates[template_index]);
    }
}
