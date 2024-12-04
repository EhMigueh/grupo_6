#ifndef SIMILARITY_H
#define SIMILARITY_H

#include "users.h"

/* Funciones dedicadas a la Similitud */
double calculate_jaccard_similarity(
    const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, 
    const char hobbies2[MAX_HOBBIE_LENGTH][MAX_HOBBIE_LENGTH], int, 
    int, int, const char *, const char *);

void find_common_hobbies(
    const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, 
    const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int);

void recommend_users(const User users[MAX_USERS], int);

double calculate_age_weight(int, int);
const char *get_age_compatibility_level(int);
double calculate_personality_multiplier(int, int);
void explain_personality_compatibility(const User *, const User *);
int get_personality_group(const char *);

/* Algoritmos para la ordenacion eficiente de matches */
void quicksort(Match matches[], int, int);
int partition(Match matches[], int, int);
#endif