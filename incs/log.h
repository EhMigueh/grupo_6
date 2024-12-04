#ifndef LOG_H
#define LOG_H

#include "users.h"

/* Funciones dedicadas al historial de Usuarios */
void user_count_from_log(int *);
int log_check();
void log_input(User *);
void log_clean();
void log_output(const User *);

#endif