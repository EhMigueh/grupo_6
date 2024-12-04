#ifndef USERS_H
#define USERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User-related Constants
#define MAX_USERS 51             
#define MAX_NAME_LENGTH 50       
#define MAX_GENDER 10            
#define MAX_HOBBIES 10           
#define MAX_HOBBIE_LENGTH 50     
#define MAX_AGE 60               
#define MIN_AGE 18               
#define MAX_PERS_LENGTH 50       
#define NUM_PERSONALITY_TYPES 16 
#define MAX_FILE_LINES 100

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

/* Estructura de Afinidad */
typedef struct
{
    int user_index;    // Índice del usuario con el que se encontró la coincidencia.
    double similarity; // Similitud calculada entre los hobbies de los dos usuarios (Índice de Jaccard).
    int age_diff;      // Diferencia de edad entre los dos usuarios en años.
} Match;

/* Funciones dedicadas a la creación,inicializacion, administracion de post  */

void load_file(const char *, char[MAX_FILE_LINES][MAX_NAME_LENGTH], int *);
void generate_random_users(User *, int, 
    char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, 
    char[MAX_FILE_LINES][MAX_NAME_LENGTH], int, 
    char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int, 
    char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);
void generate_random_hobbies(char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], 
    char[MAX_FILE_LINES][MAX_HOBBIE_LENGTH], int);
void generate_random_personality(char *, 
    char[MAX_FILE_LINES][MAX_PERS_LENGTH], int);
void print_users(const User *);

#endif