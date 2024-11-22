#include "header.h"

// Función para cargar un archivo de texto en un arreglo.
void load_file(const char *filename, char file_array[MAX_FILE_LINES][MAX_NAME_LENGTH], int *count)
{
    // Abrir el archivo en modo lectura, en caso de no poder abrirlo, se imprime un mensaje de error y se termina el programa.
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error al abrir el archivo %s, saliendo...\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_NAME_LENGTH];

    // Leer el archivo línea por línea y almacenar cada línea en el arreglo.
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        strcpy(file_array[*count], line);
        (*count)++;
    }

    fclose(file);
}

// Función para generar usuarios aleatorios.
void generate_random_users(User *user, int id, char male_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH], int male_count, char female_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH], int female_count, char hobbies_list[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int hobby_count)
{
    user->id = id;

    int gender_choice = rand() % 2; // 0 para masculino, 1 para femenino.

    if (gender_choice == 0 && male_count > 0)
    {
        strcpy(user->gender, "Masculino");
        strcpy(user->username, male_usernames[rand() % male_count]);
    }
    else if (female_count > 0)
    {
        strcpy(user->gender, "Femenino");
        strcpy(user->username, female_usernames[rand() % female_count]);
    }

    generate_random_hobbies(user->hobbies, hobbies_list, hobby_count); // Generar hobbies aleatorios.
}

// Función para generar hobbies aleatorios.
void generate_random_hobbies(char hobbies[MAX_HOBBIES][MAX_HOBBIE_LENGTH], char hobbies_list[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int hobby_count)
{
    int num_hobbies = rand() % MAX_HOBBIES + 1; // Tiene que tener al menos un hobby.

    for (int i = 0; i < num_hobbies; i++)
        strcpy(hobbies[i], hobbies_list[rand() % hobby_count]);
}

// Función para imprimir los usuarios.
void print_users(const User *user)
{
    fprintf(stdout, "ID: %d\n", user->id);
    fprintf(stdout, "Nombre: %s\n", user->username);
    fprintf(stdout, "Género: %s\n", user->gender);
    fprintf(stdout, "Hobbies:\n");
    for (int i = 0; i < MAX_HOBBIES && strlen(user->hobbies[i]) > 0; i++)
        fprintf(stdout, " - %s\n", user->hobbies[i]);
}