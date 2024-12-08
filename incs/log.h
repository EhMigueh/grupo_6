#ifndef LOG_H
#define LOG_H


/** 
 * @file log.h
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras. Benjamin Sanhueza y Johann Fink
 * @brief Definición de funciones para manejar el historial de usuarios y registros.
 */

#include "users.h"


/* Funciones dedicadas al historial de Usuarios */

/**
 * @brief Función que cuenta el número de usuarios registrados en el archivo de logs.
 * @param count Puntero a la variable donde se almacenará el número de usuarios.
 */
void user_count_from_log(int *);

/**
 * @brief Función que verifica el estado del archivo de logs.
 * @return Retorna 1 si el archivo de log es accesible, 0 si no lo es.
 */
int log_check();

/**
 * @brief Función que registra la entrada de un usuario en el archivo de log.
 * @param user Puntero al usuario que se está registrando.
 */
void log_input(User *);

/**
 * @brief Función que limpia el archivo de logs, eliminando todos los registros de usuarios.
 */
void log_clean();


/**
 * @brief Función que imprime la información de un usuario desde el log.
 * @param user Puntero al usuario cuya información se imprimirá.
 */
void log_output(const User *);

#endif