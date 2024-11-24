
#include "header.h"


void get_users_log(const User *user){
    FILE *file = fopen("userLogs.txt","a"); // Abre archivo en modo append

    if(!file)
    {
        perror("Error al crear el historial de usuarios\n");
        return;
    }

    
        fprintf(file, "ID: %d\n", user->id);
        fprintf(file, "Nombre: %s\n", user->username);
        fprintf(file, "Género: %s\n", user->gender);
        fprintf(file, "Edad: %d\n", user->age);
        fprintf(file,"---\n");
    
    fclose(file);

}
