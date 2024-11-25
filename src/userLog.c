#include "header.h"

// Función que crea un historial de los usuarios.
void get_users_log(const User *user)
{
    // Abre archivo en modo append.
    FILE *file = fopen("userLogs.txt", "a");
    if (!file)
    {
        fprintf(stderr, "Error al crear el historial de usuarios, saliendo...\n");
        return;
    }

    fprintf(file, "ID: %d\n", user->id);
    fprintf(file, "Nombre: %s\n", user->username);
    fprintf(file, "Género: %s\n", user->gender);
    fprintf(file, "Edad: %d\n", user->age);
    fprintf(file, "---\n");

    fclose(file);
}
