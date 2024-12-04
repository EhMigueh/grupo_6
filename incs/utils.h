#ifndef UTILS_H
#define UTILS_H

#include "users.h"

/* Funciones dedicadas a eficiencia en busqueda de matches */
void quicksort(Match matches[], int, int);
int partition(Match matches[], int, int);

#endif