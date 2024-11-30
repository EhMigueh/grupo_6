#include "header.h"


void user_count_from_log(int *user_count)
{

    FILE *file = fopen("users_log.txt", "r");
    const char *key_word = "ID:";
    char buffer[200];


    if (file == NULL) 
    {
        fprintf(stderr,"No se puede acceder al historial para el conteo de usuarios. Saliendo...");
        exit(EXIT_FAILURE);
    }

    // Leer palabra por palabra del archivo
    while (fscanf(file, "%99s", buffer) == 1) 
    { // Lee hasta 199 caracteres por palabra
        // Compara la palabra leída ignorando mayúsculas y minúsculas
        if (strcasecmp(buffer, key_word) == 0) 
        {   
            (*user_count)++; // Incrementa el contador al encontrar la palabra
        }
    }

    fclose(file); // Cierra el archivo
}


int log_check()
{
    FILE *file = fopen("users_log.txt", "r"); // Abrir el archivo en modo lectura
    if (file == NULL) 
    {
        fprintf(stderr,"No se puede acceder al historial para su checkeo. Saliendo...");
        exit(EXIT_FAILURE);
    }

    int char_file = fgetc(file); // Leer el primer carácter
    fclose(file); // Cerrar el archivo

    return (char_file != EOF); // Retorna 1 si hay al menos un carácter, 0 si no
}

void log_input()
{

}

void log_clean()
{
    FILE *file = fopen("users_log.txt","w");

    if (file == NULL) 
    {
        fprintf(stderr,"Error al abrir el archivo para limpieza del historial. Saliendo...");
        exit(EXIT_FAILURE);
    }

}

// Función que crea un historial de los usuarios.
void log_output(const User *user){
    // Abre archivo en modo append.
    FILE *file = fopen("users_log.txt", "a");
    if (!file)
    {
        fprintf(stderr, "Error al crear el historial de usuarios. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    //Guarda los datos del usuario en "users_log.txt"
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
