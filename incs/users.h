#ifndef USERS_H
#define USERS_H
/** 
 * @file users.h
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras. Benjamin Sanhueza y Johann Fink
 * @brief Definición de estructuras y funciones para manejar usuarios.
 * Este archivo contiene las constantes, estructuras y funciones necesarias para manejar la creación, inicialización y administración de usuarios en el sistema.
 */
/* Constantes Relacionadas a usuarios*/
#define MAX_USERS 51             // Número máximo de usuarios permitidos.
#define MAX_NAME_LENGTH 50       // Longitud máxima del nombre de usuario.
#define MAX_GENDER 10            // Longitud máxima para el género del usuario.
#define MAX_HOBBIES 10           // Número máximo de hobbies que puede tener un usuario.
#define MAX_HOBBIE_LENGTH 50     // Longitud máxima de cada hobby.
#define MAX_AGE 60               // Edad máxima de un usuario.
#define MIN_AGE 18               // Edad mínima de un usuario.
#define MAX_PERS_LENGTH 50       // Longitud máxima de la personalidad de un usuario.
#define NUM_PERSONALITY_TYPES 16 // Número de tipos de personalidad disponibles.
#define MAX_FILE_LINES 100       // Número máximo de líneas que se pueden leer desde un archivo.

/** 
 * @struct User
 * @brief Estructura que representa a un usuario.
 * Esta estructura contiene la información básica de un usuario, como su ID, nombre,
 * edad, género, hobbies y personalidad.
 */
/* Estructura del Usuario */
typedef struct User
{
    int id;                                       // Id de usuario.
    char username[MAX_NAME_LENGTH];               // Nombre del usuario.
    int age;                                      // Edad del usuario.
    char gender[MAX_GENDER];                      // Género del usuario.
    char hobbies[MAX_HOBBIES][MAX_HOBBIE_LENGTH]; // Hobbies del usuario.
    char personality[MAX_PERS_LENGTH];            // Personalidad del usuario.
} User;


/** 
 * @struct Match
 * @brief Estructura que representa una coincidencia entre dos usuarios.
 * Esta estructura se utiliza para almacenar la similitud de hobbies y la diferencia de edad
 * entre dos usuarios que se han emparejado en el sistema.
 */
/* Estructura de Afinidad */
typedef struct
{
    int user_index;    // Índice del usuario con el que se encontró la coincidencia.
    double similarity; // Similitud calculada entre los hobbies de los dos usuarios (Índice de Jaccard).
    int age_diff;      // Diferencia de edad entre los dos usuarios en años.
} Match;

/* Funciones dedicadas a la creación,inicializacion, administracion de post  */

/** 
 * @brief Carga un archivo de texto en un arreglo.
 * Lee un archivo de texto y almacena cada línea en un arreglo bidimensional de cadenas.
 * @param filename Nombre del archivo a cargar.
 * @param file_array Arreglo donde se almacenarán las líneas leídas del archivo.
 * @param count Puntero a la variable donde se almacenará el número de líneas leídas.
 */
void load_file(const char *, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int *);

/** 
 * @brief Genera un usuario aleatorio.
 * Crea un usuario con información aleatoria, como nombre, edad, género, hobbies y personalidad, seleccionados de listas predefinidas.
 * @param user Puntero al usuario a generar.
 * @param id ID único que se asignará al usuario.
 * @param male_usernames Lista de nombres masculinos disponibles.
 * @param male_count Número de nombres masculinos en la lista.
 * @param female_usernames Lista de nombres femeninos disponibles.
 * @param female_count Número de nombres femeninos en la lista.
 * @param hobbies_list Lista de hobbies disponibles.
 * @param hobby_count Número de hobbies en la lista.
 * @param personalities_list Lista de personalidades disponibles.
 * @param personality_count Número de personalidades en la lista.
 */
void generate_random_users(User *, int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int, char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);

/** 
 * @brief Genera hobbies aleatorios para un usuario.
 * Selecciona aleatoriamente un número de hobbies de una lista predefinida y los asigna al usuario.
 * @param hobbies Arreglo donde se almacenarán los hobbies generados.
 * @param hobbies_list Lista de hobbies disponibles para la selección.
 * @param hobby_count Número total de hobbies disponibles en la lista.
 */
void generate_random_hobbies(char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int);

/** 
 * @brief Genera una personalidad aleatoria para un usuario.
 * Selecciona aleatoriamente una personalidad de una lista predefinida y la asigna al usuario.
 * @param personality Puntero a la cadena donde se almacenará la personalidad generada.
 * @param personalities_list Lista de personalidades disponibles para la selección.
 * @param personality_count Número total de personalidades disponibles en la lista.
 */
void generate_random_personality(char *, char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);

/** 
 * @brief Imprime la información de un usuario.
 * Imprime los detalles de un usuario, incluyendo su ID, nombre, género, edad, personalidad y hobbies en la salida estándar.
 * @param user Puntero al usuario cuya información se desea imprimir.
 */
void print_users(const User *);

#endif