/**
 * @file user.c
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras, Benjamin Sanhueza y Johann Fink
 * @brief Implementación de funciones para generar y gestionar usuarios. Incluye la creación de usuarios aleatorios, carga de archivos con información de usuarios, y la impresión de los datos de los usuarios.
 */
#include "main.h"

/**
 * @brief Carga un archivo de texto en un arreglo.
 * Esta función lee un archivo de texto y almacena cada línea en un arreglo bidimensional, hasta un máximo de líneas especificado por MAX_FILE_LINES.
 * @param filename Nombre del archivo a cargar.
 * @param file_array Arreglo donde se almacenarán las líneas del archivo.
 * @param count Puntero a la variable que almacena el número de líneas leídas.
 */
// Función para cargar un archivo de texto en un arreglo.
void load_file(const char *filename, char file_array[MAX_FILE_LINES][MAX_NAME_LENGTH], int *count)
{
    // Abrir el archivo en modo lectura, en caso de no poder abrirlo, se imprime un mensaje de error y se termina el programa.
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        // Abrir el archivo en modo lectura, en caso de no poder abrirlo, se imprime un mensaje de error y se termina el programa.
        fprintf(stderr, "Error al abrir el archivo %s, saliendo...\n", filename);
        exit(EXIT_FAILURE);
    }

    *count = 0;
    char line[MAX_NAME_LENGTH];

    // Leer el archivo línea por línea y almacenar cada línea en el arreglo
    while (*count < MAX_FILE_LINES && fgets(line, sizeof(line), file))
    {
        size_t len = strcspn(line, "\n");
        line[len] = '\0';

        if (len > MAX_NAME_LENGTH)
            len = MAX_NAME_LENGTH - 1;

        memcpy(file_array[*count], line, len);
        file_array[*count][len] = '\0';
        (*count)++;
    }

    fclose(file);
}


/**
 * @brief Genera un usuario aleatorio.
 * Esta función crea un usuario con información aleatoria como el género, nombre, edad, personalidad y hobbies, basándose en listas de datos predefinidas.
 * @param user Puntero al usuario que se generará.
 * @param id ID único que se asignará al usuario.
 * @param male_usernames Lista de nombres de usuario masculinos disponibles.
 * @param male_count Número de nombres masculinos en la lista.
 * @param female_usernames Lista de nombres de usuario femeninos disponibles.
 * @param female_count Número de nombres femeninos en la lista.
 * @param hobbies_list Lista de hobbies disponibles.
 * @param hobby_count Número de hobbies en la lista.
 * @param personalities_list Lista de personalidades disponibles.
 * @param personality_count Número de personalidades en la lista.
 */
// Función para generar usuarios aleatorios.
void generate_random_users(User *user, int id, char male_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH], int male_count, char female_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH], int female_count, char hobbies_list[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int hobby_count, char personalities_list[MAX_FILE_LINES][MAX_PERS_LENGTH], int personality_count)
{
    if (!user)
    {
        fprintf(stderr, "No se puede generar un usuario nulo. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    user->id = id;

    // Inicializar hobbies
    for (int i = 0; i < MAX_HOBBIES; i++)
        user->hobbies[i][0] = '\0';

    // Generar edad aleatoria
    user->age = random() % MAX_AGE + MIN_AGE;

    int gender_choice = random() % 2;

    if (gender_choice == 0 && male_count > 0)
    {
        strncpy(user->gender, "Masculino", MAX_GENDER - 1);
        user->gender[MAX_GENDER - 1] = '\0';
        int name_index = random() % male_count;
        strncpy(user->username, male_usernames[name_index], MAX_NAME_LENGTH - 1);
        user->username[MAX_NAME_LENGTH - 1] = '\0';
    }
    else if (female_count > 0)
    {
        strncpy(user->gender, "Femenino", MAX_GENDER - 1);
        user->gender[MAX_GENDER - 1] = '\0';
        int name_index = random() % female_count;
        strncpy(user->username, female_usernames[name_index], MAX_NAME_LENGTH - 1);
        user->username[MAX_NAME_LENGTH - 1] = '\0';
    }

    generate_random_hobbies(user->hobbies, hobbies_list, hobby_count);
    generate_random_personality(user->personality, personalities_list, personality_count);
}

/**
 * @brief Genera hobbies aleatorios para un usuario.
 * Esta función selecciona aleatoriamente un número de hobbies de una lista predefinida, y los asigna al arreglo de hobbies del usuario.
 * @param hobbies Arreglo donde se almacenarán los hobbies generados.
 * @param hobbies_list Lista de hobbies disponibles para selección.
 * @param hobby_count Número total de hobbies disponibles en la lista.
 */
// Función para generar hobbies aleatorios.
void generate_random_hobbies(char hobbies[MAX_HOBBIES][MAX_HOBBIE_LENGTH], char hobbies_list[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int hobby_count)
{
    if (hobby_count <= 0)
    {
        fprintf(stderr, "No hay hobbies disponibles. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    // Inicializar array de hobbies
    for (int i = 0; i < MAX_HOBBIES; i++)
        hobbies[i][0] = '\0';

    // Crear array para tracking de hobbies seleccionados.
    int *hobbie_selected = calloc(hobby_count, sizeof(int));

    if (!hobbie_selected)
        return;

    int num_hobbies = (random() % MAX_HOBBIES) + 1;
    int added_hobbies = 0;

    // Seleccionar hobbies aleatorios
    for (int i = 0; i < num_hobbies && added_hobbies < MAX_HOBBIES; i++)
    {
        int hobbie_index = random() % hobby_count;

        if (!hobbie_selected[hobbie_index])
        {
            strncpy(hobbies[added_hobbies], hobbies_list[hobbie_index], MAX_HOBBIE_LENGTH - 1);
            hobbies[added_hobbies][MAX_HOBBIE_LENGTH - 1] = '\0';
            hobbie_selected[hobbie_index] = 1;
            added_hobbies++;
        }
    }

    free(hobbie_selected);
}


/**
 * @brief Genera una personalidad aleatoria para un usuario.
 * Esta función selecciona aleatoriamente una personalidad de una lista predefinida y
 * la asigna al campo de personalidad del usuario.
 * @param personality Puntero a una cadena donde se almacenará la personalidad generada.
 * @param personalities_list Lista de personalidades disponibles para selección.
 * @param personality_count Número total de personalidades disponibles en la lista.
 */
// Función para generar personalidad aleatoria.
void generate_random_personality(char *personality, char personalities_list[MAX_FILE_LINES][MAX_PERS_LENGTH], int personality_count)
{
    if (personality_count <= 0)
    {
        fprintf(stderr, "No hay personalidades disponibles. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    // Inicializar personalidad
    personality[0] = '\0';

    strcpy(personality, personalities_list[random() % personality_count]);
}

/**
 * @brief Imprime la información de un usuario.
 * Esta función imprime en la salida estándar (consola) los detalles de un usuario,
 * incluyendo su ID, nombre, género, edad, personalidad y hobbies.
 * @param user Puntero al usuario que se desea imprimir.
 */
// Función para imprimir los usuarios.
void print_users(const User *user)
{
    if (!user)
    {
        fprintf(stderr, "No se puede imprimir un usuario nulo. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "ID: %d\n", user->id);
    fprintf(stdout, "Nombre: %s\n", user->username);
    fprintf(stdout, "Género: %s\n", user->gender);
    fprintf(stdout, "Edad: %d\n", user->age);
    fprintf(stdout, "Personalidad: %s\n", user->personality);
    fprintf(stdout, "Hobbies:\n");

    for (int i = 0; i < MAX_HOBBIES && user->hobbies[i][0] != '\0'; i++)
        fprintf(stdout, " - %s\n", user->hobbies[i]);
}