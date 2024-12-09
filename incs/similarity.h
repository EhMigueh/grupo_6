#ifndef SIMILARITY_H
#define SIMILARITY_H

/**
 * @file similarity.h
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras, Benjamín Sanhueza y Johann Fink
 * @brief Definición de funciones para calcular la similitud entre usuarios.
 * Este archivo contiene funciones que permiten calcular la similitud entre usuarios basándose en sus hobbies, edad y personalidad. Además, incluye algoritmos para recomendar usuarios y
 * ordenar las coincidencias de manera eficiente.
 */
#include "users.h"

/**
 * @brief Calcula la similitud de Jaccard entre dos conjuntos de hobbies.
 * Esta función calcula la similitud de Jaccard entre los hobbies de dos usuarios, tomando en cuenta el número de hobbies comunes y el número total de hobbies.
 * @param hobbies1 Hobbies del primer usuario.
 * @param hobbies1_count Número de hobbies del primer usuario.
 * @param hobbies2 Hobbies del segundo usuario.
 * @param hobbies2_count Número de hobbies del segundo usuario.
 * @param common_hobbies_count Número de hobbies comunes entre los dos usuarios.
 * @param total_hobbies_count Número total de hobbies combinados de ambos usuarios.
 * @param personality1 Personalidad del primer usuario.
 * @param personality2 Personalidad del segundo usuario.
 * @return Valor numérico que representa la similitud de Jaccard entre los hobbies de ambos usuarios.
 */
/* Funciones dedicadas a la Similitud */
double calculate_jaccard_similarity(const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, const char hobbies2[MAX_HOBBIE_LENGTH][MAX_HOBBIE_LENGTH], int, int, int, const char *, const char *);

/**
 * @brief Encuentra los hobbies comunes entre dos usuarios.
 * Esta función compara los hobbies de dos usuarios y encuentra aquellos que coinciden.
 * @param hobbies1 Hobbies del primer usuario.
 * @param hobbies1_count Número de hobbies del primer usuario.
 * @param hobbies2 Hobbies del segundo usuario.
 * @param hobbies2_count Número de hobbies del segundo usuario.
 */
void find_common_hobbies(const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int, const char[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int);

/**
 * @brief Recomienda usuarios basándose en la similitud.
 * Compara todos los usuarios entre sí y recomienda aquellos con mayor compatibilidad basada en la similitud de hobbies, edad y personalidad.
 * @param users Arreglo de usuarios en el sistema.
 * @param user_count Número de usuarios en el sistema.
 */
void recommend_users(const User users[MAX_USERS], int);

/**
 * @brief Calcula un factor de ponderación basado en la diferencia de edad entre dos usuarios.
 * La diferencia de edad se convierte en un valor numérico para ajustar la similitud entre usuarios.
 * @param age1 Edad del primer usuario.
 * @param age2 Edad del segundo usuario.
 * @return Un valor de ponderación basado en la diferencia de edad.
 */
double calculate_age_weight(int, int);

/**
 * @brief Obtiene el nivel de compatibilidad de edad entre dos usuarios.
 * Esta función clasifica la compatibilidad de edad entre dos usuarios en categorías.
 * @param age_diff Diferencia de edad entre los dos usuarios.
 * @return Una cadena que describe el nivel de compatibilidad de edad.
 */
const char *get_age_compatibility_level(int);

/**
 * @brief Calcula un multiplicador de personalidad entre dos usuarios.
 * Compara las personalidades de dos usuarios y devuelve un multiplicador que indica cuán compatibles son sus personalidades.
 * @param personality1 Personalidad del primer usuario.
 * @param personality2 Personalidad del segundo usuario.
 * @return Un valor numérico que representa la compatibilidad de personalidad.
 */
double calculate_personality_multiplier(int, int);

/**
 * @brief Explica la compatibilidad de personalidad entre dos usuarios.
 * Imprime una descripción detallada de cómo las personalidades de dos usuarios son compatibles.
 * @param user1 Puntero al primer usuario.
 * @param user2 Puntero al segundo usuario.
 */
void explain_personality_compatibility(const User *, const User *);

/**
 * @brief Obtiene el grupo de personalidad al que pertenece un usuario.
 * La personalidad de un usuario se clasifica en un grupo de personalidades predefinido.
 * @param personality Personalidad del usuario.
 * @return El grupo al que pertenece la personalidad del usuario.
 */
int get_personality_group(const char *);

/**
 * @brief Ordena un arreglo de coincidencias de usuarios utilizando el algoritmo QuickSort.
 * Este algoritmo organiza las coincidencias de acuerdo con su similitud, de mayor a menor.
 * @param matches Arreglo de coincidencias entre usuarios.
 * @param low Índice bajo del arreglo.
 * @param high Índice alto del arreglo.
 */
void quicksort(Match matches[], int, int);

/**
 * @brief Particiona un arreglo de coincidencias para el algoritmo QuickSort.
 * Se utiliza para reorganizar el arreglo y preparar el pivote para la ordenación.
 * @param matches Arreglo de coincidencias entre usuarios.
 * @param low Índice bajo del arreglo.
 * @param high Índice alto del arreglo.
 * @return El índice del pivote después de la partición.
 */
int partition(Match matches[], int, int);

#endif