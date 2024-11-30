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

void log_input(User users[]) {

    char line[256];     // Línea temporal para almacenar el contenido leído.
    int user_count = 0; // Contador de usuarios cargados.
    int hobby_count = 0; // Contador de hobbies para el usuario actual.
    FILE *file = fopen("users_log.txt", "r"); // Abre el archivo en modo lectura.

    if (!file) 
    { // Si el archivo no se puede abrir, mostramos un error y terminamos.
        fprintf(stderr,"No se pudo abrir el archivos del historial para el ingreso de usuarios. Saliendo...");
        exit(EXIT_FAILURE);
    }


    // Bucle que lee línea por línea hasta el final del archivo o hasta llenar el arreglo de usuarios.
    while (fgets(line, sizeof(line), file) && user_count < MAX_USERS) {
        // Si la línea comienza con "ID:", extraemos el ID del usuario.
        if (strncmp(line, "ID:", 3) == 0) {
            sscanf(line, "ID: %d", &users[user_count].id);
            hobby_count = 0; // Reiniciamos el contador de hobbies para este usuario.
        }
        // Si la línea comienza con "Nombre:", extraemos el nombre del usuario.
        else if (strncmp(line, "Nombre:", 7) == 0) {
            sscanf(line, "Nombre: %[^\n]", users[user_count].username);
        }
        // Si la línea comienza con "Género:", extraemos el género del usuario.
        else if (strncmp(line, "Género:", 7) == 0) {
            sscanf(line, "Género: %[^\n]", users[user_count].gender);
        }
        // Si la línea comienza con "Edad:", extraemos la edad del usuario.
        else if (strncmp(line, "Edad:", 5) == 0) {
            sscanf(line, "Edad: %d", &users[user_count].age);
        }
        // Si la línea comienza con "Personalidad:", extraemos el tipo de personalidad.
        else if (strncmp(line, "Personalidad:", 13) == 0) {
            sscanf(line, "Personalidad: %[^\n]", users[user_count].personality);
        }
        // Si la línea comienza con " - ", es un hobby, lo almacenamos.
        else if (strncmp(line, " - ", 3) == 0) {
            if (hobby_count < MAX_HOBBIES) { // Verificamos que no exceda el límite de hobbies.
                sscanf(line, " - %[^\n]", users[user_count].hobbies[hobby_count]);
                hobby_count++; // Incrementamos el contador de hobbies.
            }
        }
        // Si la línea es "---", significa que terminamos de leer un usuario.
        else if (strncmp(line, "---", 3) == 0) {
            user_count++; // Pasamos al siguiente usuario.
        }
    }

    fclose(file); // Cerramos el archivo al terminar.
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
