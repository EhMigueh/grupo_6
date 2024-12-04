#ifndef MAIN_H
#define MAIN_H


// Librerias 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "users.h"      // Tipos de usuarios y funciones relacionadas con usuarios
#include "posts.h"      // Tipos de publicaciones y funciones relacionadas con publicaciones
#include "graph.h"      // Tipos de grafos y funciones relacionadas con grafos
#include "log.h"        // Funciones de registro
#include "similarity.h" // Similitud entre usuarios y funciones de recomendación

// Macros para colores
#define RESET "\033[0m"   // Default
#define GREEN "\033[32m"  // Verde
#define YELLOW "\033[33m" // Amarillo
#define CYAN "\033[36m"   // Cian
#define RED "\033[31m"    // Rojo


#endif