#ifndef MAIN_H
#define MAIN_H

/**
 * @file main.h
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras, Benjamín Sanhueza y Johann Fink
 * @brief Definición de las librerías necesarias y macros de color para el proyecto.
 *
 * Contiene las librerías necesarias para el proyecto y macros de color para la consola.
 */

/**
 * Librerías utilizadas en el proyecto.
 * @code
 * #include <math.h>
 * #include <stdlib.h>
 * #include <stdio.h>
 * #include <unistd.h>
 * #include <string.h>
 * #include <time.h>
 * @endcode
 */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/**
 * Librerías propias del proyecto.
 * @code
 * #include "users.h"
 * #include "posts.h"
 * #include "graph.h"
 * #include "log.h"
 * #include "similarity.h"
 * @endcode
 */
#include "users.h"
#include "posts.h"
#include "graph.h"
#include "log.h"
#include "similarity.h"

/**
 * Macros utilizadas en el proyecto.
 * @code
 * #define RESET "\033[0m"
 * #define GREEN "\033[32m"
 * #define YELLOW "\033[33m"
 * #define CYAN "\033[36m"
 * #define RED "\033[31m"
 * @endcode
 */
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RED "\033[31m"

#endif