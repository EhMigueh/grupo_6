#include "header.h"

// Función que crea un historial de los usuarios.
void get_users_log(const User *user)
{
    // Abre archivo en modo append.
    FILE *file = fopen("users_log.txt", "a");
    if (!file)
    {
        fprintf(stderr, "Error al crear el historial de usuarios, saliendo...\n");
        exit(EXIT_FAILURE);
    }

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
