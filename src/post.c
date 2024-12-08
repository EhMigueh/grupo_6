/**
 * @file post.c
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras, Benjamin Sanhueza y Johann Fink
 * @brief Implementación de funciones para la gestión y visualización de publicaciones en la red social.
 */
#include "main.h"

/**
 * @brief Inicializa la lista de publicaciones, configura el encabezado de la lista de publicaciones a NULL y establece el contador de publicaciones en 0.
 * @param post_list Puntero a la lista de publicaciones a inicializar.
 */
// Inicializar lista de publicaciones.
void init_post_list(Post_List *post_list)
{
    post_list->head = NULL;
    post_list->postCount = 0;
}


/**
 * @brief Crea una nueva publicación,esta función genera una nueva publicación con un ID único, la información del usuario,
   el contenido de la publicación y una marca de tiempo aleatoria.
 * @param user_Id ID del usuario que realiza la publicación.
 * @param username Nombre de usuario del autor de la publicación.
 * @param content Contenido textual de la publicación.
 * @return Un puntero a la nueva publicación creada.
 */
// Crear una nueva publicación.
Post *create_post(int user_Id, const char *username, const char *content)
{
    // Validar longitud de contenido.
    if (strlen(content) >= MAX_POST_LENGTH)
    {
        fprintf(stderr, "El contenido de publicación demasiado largo. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    Post *newPost = malloc(sizeof(Post));
    if (!newPost)
    {
        fprintf(stderr, "No se pudo asignar memoria para la publicación. Saliendo...\n");
        exit(EXIT_FAILURE);
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
    newPost->timestamp = generate_random_timestamp();
    newPost->next = NULL;

    return newPost;
}

/**
 * @brief Publica una nueva entrada en el muro global-Crea una publicación usando la información de un usuario y agrega la publicación al inicio de la lista global de publicaciones.
 * @param post_list Puntero a la lista de publicaciones global.
 * @param user Puntero a la estructura del usuario que realiza la publicación.
 * @param content Contenido textual de la publicación.
 */
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

/**
 * @brief Muestra todas las publicaciones en la red social. Imprime en consola la lista completa de publicaciones, mostrando la ID, el usuario, el contenido y la fecha.
 * @param post_list Puntero a la lista de publicaciones que se mostrarán.
 */
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
        fprintf(stdout, "\n");
        current = current->next;
    }
}

/**
 * @brief Libera la memoria ocupada por todas las publicaciones. Recorre la lista de publicaciones y libera la memoria de cada una de ellas.
 * @param post_list Puntero a la lista de publicaciones que se deben liberar.
 */
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

/**
 * @brief Carga plantillas de publicaciones desde un archivo.
 * Lee un archivo de plantillas de publicaciones y almacena las plantillas en un arreglo.
 * @param post_templates Arreglo donde se almacenarán las plantillas de publicaciones.
 * @param post_count Puntero a la variable que contará las plantillas cargadas.
 */
// Función para cargar publicaciones desde un archivo
void load_post_templates(char post_templates[MAX_FILE_LINES][MAX_POST_LENGTH], int *post_count)
{
    FILE *file = fopen("./input/post_templates.txt", "r");
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

        if (len > MAX_POST_LENGTH)
            len = MAX_POST_LENGTH - 1;

        memcpy(post_templates[*post_count], line, len);
        post_templates[*post_count][len] = '\0';
        (*post_count)++;
    }

    fclose(file);
}

/**
 * @brief Genera publicaciones aleatorias usando usuarios y plantillas.
 * Esta función selecciona aleatoriamente usuarios y plantillas de publicaciones, creando publicaciones y agregándolas al muro global hasta alcanzar el número máximo de publicaciones.
 * @param users Arreglo de usuarios disponibles para generar publicaciones.
 * @param num_users Número de usuarios disponibles.
 * @param post_list Puntero a la lista de publicaciones donde se agregarán las nuevas publicaciones generadas.
 */
void generate_random_posts(User users[MAX_USERS], int num_users, Post_List *post_list)
{
    char post_templates[MAX_FILE_LINES][MAX_POST_LENGTH];
    int post_template_count = 0;

    // Cargar plantillas de publicaciones
    load_post_templates(post_templates, &post_template_count);

    if (post_template_count == 0)
    {
        fprintf(stderr, "No se encontraron plantillas de publicaciones.\n");
        exit(EXIT_FAILURE);
    }

    //  Arreglo para marcar usuarios ya seleccionados y evitar repeticiones
    int used_users[MAX_USERS] = {0};
    int unique_posts_created = 0;
    // Generar publicaciones aleatorias hasta alcanzar el límite o usar todos los usuarios
    while (unique_posts_created < MAX_POSTS && unique_posts_created < num_users)
    {
        // Seleccionar Usuario aleatorio que no haya sido usado
        int random_user_index;
        do
        {
            random_user_index = rand() % num_users;
        } while (used_users[random_user_index]);

        // Marcar usuario como usado
        used_users[random_user_index] = 1;

        // Seleccionar una plantilla de publicación aleatoria.
        int template_index = rand() % post_template_count;

        // Publicar utilizando la plantilla seleccionada para el usuario aleatorio.
        publish_post(post_list, &users[random_user_index], post_templates[template_index]);

        unique_posts_created++;
    }
}

/**
 * @brief Genera un timestamp aleatorio.
 * Calcula un timestamp aleatorio basado en el tiempo actual, con una desviación de hasta 7 días.
 * @return El timestamp generado aleatoriamente.
 */
time_t generate_random_timestamp()
{
    // Obtener tiempo actual del sistema
    time_t current_time = time(NULL);

    // Generar horas aleatorias hasta 7 días
    int random_hours = rand() % (24 * 7);

    // Generar minutos aleatorios
    int random_minutes = rand() % 60;

    // Generar segundos aleatorios
    int random_seconds = rand() % 60;

    // Calcular y restar tiempo aleatorio del tiempo actual
    time_t random_time = current_time - (random_hours * 3600 + random_minutes * 60 + random_seconds);

    return random_time;
}