#include "main.h"

void user_count_from_log(int *user_count)
{
    FILE *file = fopen("./input/users_log.txt", "r");
    const char *key_word = "ID:";
    char buffer[100];

    if (file == NULL)
    {
        fprintf(stderr, "No se puede acceder al historial para el conteo de usuarios. Saliendo...");
        exit(EXIT_FAILURE);
    }

    // Leer palabra por palabra del archivo
    while (fscanf(file, "%99s", buffer) == 1)
        if (strcasecmp(buffer, key_word) == 0) // Compara la palabra leída
            (*user_count)++;

    fclose(file);
}

int log_check()
{
    FILE *file = fopen("./input/users_log.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "No se puede acceder al historial para su checkeo. Saliendo...");
        exit(EXIT_FAILURE);
    }

    int char_file = fgetc(file);

    fclose(file);

    return (char_file != EOF); // Retorna 1 si hay historial
}

void log_input(User users[])
{

    char line[256];
    int user_count = 0;  // Contador de usuarios cargados.
    int hobby_count = 0; // Contador de hobbies para el usuario actual.

    FILE *file = fopen("./input/users_log.txt", "r");
    if (!file)
    {
        fprintf(stderr, "No se pudo abrir el archivos del historial para el ingreso de usuarios. Saliendo...");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file) && user_count < MAX_USERS)
    {
        if (strncmp(line, "ID:", 3) == 0) // Detecta si la línea comienza con "ID:"
        {
            sscanf(line, "ID: %d", &users[user_count].id);
            hobby_count = 0; // Contador de hobbies para cada usuario
        }
        else if (strncmp(line, "Nombre:", 7) == 0) // Si la línea comienza con "Nombre:" guarda la informacion
            sscanf(line, "Nombre: %12[^\n]", users[user_count].username);
        else if (strncmp(line, "Género:", 7) == 0) // Si la línea comienza con "Género:" guarda la informacion
            sscanf(line, "Género: %12[^\n]", users[user_count].gender);
        else if (strncmp(line, "Edad:", 5) == 0) // Si la línea comienza con "Edad:" guarda la informacion
            sscanf(line, "Edad: %d", &users[user_count].age);
        else if (strncmp(line, "Personalidad:", 13) == 0) // Si la línea comienza con "Personalidad:" guarda la informacion
            sscanf(line, "Personalidad: %6[^\n]", users[user_count].personality);
        else if (strncmp(line, " - ", 3) == 0) // Si la línea comienza con " - " pasa a leer los hobbies
        {
            if (hobby_count < MAX_HOBBIES)
            {
                sscanf(line, " - %50[^\n]", users[user_count].hobbies[hobby_count]);
                hobby_count++;
            }
        }
        else if (strncmp(line, "---", 3) == 0) // Separador de usuarios en el txt
            user_count++;                      // Siguiente usuario
    }

    fclose(file);
}

void log_clean()
{
    FILE *file = fopen("./input/users_log.txt", "w");

    if (file == NULL)
    {
        fprintf(stderr, "Error al abrir el archivo para limpieza del historial. Saliendo...");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

// Función que crea un historial de los usuarios.
void log_output(const User *user)
{
    // Abre archivo en modo append.
    FILE *file = fopen("./input/users_log.txt", "a");
    if (!file)
    {
        fprintf(stderr, "Error al crear el historial de usuarios. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    // Guarda los datos del usuario en "users_log.txt"
    fprintf(file, "ID: %d\n", user->id);
    fprintf(file, "Nombre: %s\n", user->username);
    fprintf(file, "Género: %s\n", user->gender);
    fprintf(file, "Edad: %d\n", user->age);
    fprintf(file, "Personalidad: %s\n", user->personality);

    for (int i = 0; i < MAX_HOBBIES && user->hobbies[i][0] != '\0'; i++)
        fprintf(file, " - %s\n", user->hobbies[i]);

    fprintf(file, "---\n");
    fclose(file);
}
