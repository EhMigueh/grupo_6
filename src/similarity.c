/**
 * @file similitary.c
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras, Benjamin Sanhueza y Johann Fink
 * @brief Contiene funciones para calcular similitudes entre usuarios basadas en sus hobbies, edad y personalidad, así como para crear conexiones entre usuarios mediante un grafo y recomendar usuarios similares.
 */
#include "main.h"

/**
 * @brief Calcula el índice de similitud de Jaccard entre dos conjuntos de hobbies.
 * Compara dos usuarios basándose en sus hobbies, edad y personalidad, ajustando el puntaje de similitud según estos factores.
 * @param hobbies1 Conjunto de hobbies del primer usuario.
 * @param count1 Número de hobbies del primer usuario.
 * @param hobbies2 Conjunto de hobbies del segundo usuario.
 * @param count2 Número de hobbies del segundo usuario.
 * @param age1 Edad del primer usuario.
 * @param age2 Edad del segundo usuario.
 * @param personality1 Personalidad del primer usuario.
 * @param personality2 Personalidad del segundo usuario.
 * @return Un valor entre 0 y 1 que representa la similitud entre los dos usuarios.
 */
double calculate_jaccard_similarity(const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int count1, const char hobbies2[MAX_HOBBIE_LENGTH][MAX_HOBBIE_LENGTH], int count2, int age1, int age2, const char *personality1, const char *personality2)
{
    /**
     * @brief Calcula el índice de similitud de Jaccard entre dos conjuntos de hobbies.
     * @code
     * int intersection = 0, union_count = 0;
     * char seen[MAX_HOBBIES][MAX_HOBBIE_LENGTH] = {0};
     * int seen_count = 0;
     * for (int i = 0; i < count1; i++)
     *   for (int j = 0; j < count2; j++)
     *       contar interseccion
     * for (int i = 0; i < count1; i++)
     * for (int j = 0; j < count2; j++)
     *   contar union
     * union_count = seen_count;
     * double jaccard = union_count > 0 ? (double)intersection / union_count : 0.0;
     * double age_weight = calculate_age_weight(age1, age2);
     * int group1 = get_personality_group(personality1);
     * int group2 = get_personality_group(personality2);
     * double personality_multiplier = calculate_personality_multiplier(group1, group2);
     * return jaccard * age_weight * personality_multiplier; -> Retorna el puntaje ajustado por edad y el multiplicador de personalidad
     * @endcode
     */
    int intersection = 0, union_count = 0;

    char seen[MAX_HOBBIES][MAX_HOBBIE_LENGTH] = {0};
    int seen_count = 0;

    for (int i = 0; i < count1; i++)
        for (int j = 0; j < count2; j++)
            if (strcmp(hobbies1[i], hobbies2[j]) == 0)
            {
                intersection++;
                break;
            }

    for (int i = 0; i < count1; i++)
        strcpy(seen[seen_count++], hobbies1[i]);

    for (int j = 0; j < count2; j++)
    {
        int found = 0;
        for (int k = 0; k < seen_count; k++)
            if (strcmp(hobbies2[j], seen[k]) == 0)
            {
                found = 1;
                break;
            }

        if (!found)
            strcpy(seen[seen_count++], hobbies2[j]);
    }

    union_count = seen_count;

    double jaccard = union_count > 0 ? (double)intersection / union_count : 0.0;
    double age_weight = calculate_age_weight(age1, age2);

    int group1 = get_personality_group(personality1);
    int group2 = get_personality_group(personality2);

    double personality_multiplier = calculate_personality_multiplier(group1, group2);

    return jaccard * age_weight * personality_multiplier;
}

/**
 * @brief Recomienda usuarios basándose en la similitud de hobbies, edad y personalidad.
 * Compara un usuario con todos los demás y muestra los usuarios más similares.
 * @param users Arreglo de usuarios a evaluar.
 * @param num_users Número total de usuarios.
 */
void recommend_users(const User users[MAX_USERS], int num_users)
{
    /**
     * @brief Recomienda usuarios basándose en la similitud de hobbies, edad y personalidad.
     * @code
     * for (int i = 0; i < num_users; i++)
     *  fprintf(stdout, CYAN "\nUsuario %d (%s, %d años):" RESET, users[i].id, users[i].username, users[i].age);
     *  Match matches[MAX_USERS];
     *  int match_count = 0;
     *  int count1 = 0, count2 = 0;
     *  for (int k = 0; k < MAX_HOBBIES && strlen(users[i].hobbies[k]) > 0; k++)
     *       Calcular el número de hobbies para el usuario i.
     *  for (int j = 0; j < num_users; j++)
     *       Encontrar todas las coincidencias.
     *  if (match_count > 1) -> Ordenar las coincidencias por similitud (método quicksort).
     *  int show_matches = match_count > 3 ? 3 : match_count;
     *  if (show_matches > 0) -> Mostrar las mejores coincidencias (hasta 3)
     * @endcode
     */
    for (int i = 0; i < num_users; i++)
    {
        fprintf(stdout, CYAN "\nUsuario %d (%s, %d años):" RESET, users[i].id, users[i].username, users[i].age);

        Match matches[MAX_USERS];
        int match_count = 0;
        int count1 = 0, count2 = 0;

        for (int k = 0; k < MAX_HOBBIES && strlen(users[i].hobbies[k]) > 0; k++)
            count1++;

        for (int j = 0; j < num_users; j++)
        {
            if (i == j)
                continue;

            count2 = 0;

            for (int k = 0; k < MAX_HOBBIES && strlen(users[j].hobbies[k]) > 0; k++)
                count2++;

            double similarity = calculate_jaccard_similarity(users[i].hobbies, count1, users[j].hobbies, count2, users[i].age, users[j].age, users[i].personality, users[j].personality);

            if (similarity > 0)
            {
                matches[match_count].user_index = j;
                matches[match_count].similarity = similarity;
                matches[match_count].age_diff = abs(users[i].age - users[j].age);
                match_count++;
            }
        }

        if (match_count > 1)
            quicksort(matches, 0, match_count - 1);

        int show_matches = match_count > 3 ? 3 : match_count;

        if (show_matches > 0)
        {
            fprintf(stdout, "\nMejores coincidencias:\n");

            for (int m = 0; m < show_matches; m++)
            {
                int j = matches[m].user_index;

                fprintf(stdout, GREEN "\n%d. Nombre: %s (%d años)\n" RESET, m + 1, users[j].username, users[j].age);
                fprintf(stdout, YELLOW "   - Similitud total: %.2f\n" RESET, matches[m].similarity);
                fprintf(stdout, "   - Compatibilidad por edad: %s (diferencia %d años)\n", get_age_compatibility_level(matches[m].age_diff), matches[m].age_diff);
                explain_personality_compatibility(&users[i], &users[j]);
                find_common_hobbies(users[i].hobbies, count1, users[j].hobbies, count2);
            }
        }
        else
            fprintf(stdout, " No hay usuarios recomendados.\n");
    }
}

/**
 * @brief Crea conexiones entre usuarios que tienen un índice de similitud de Jaccard por encima de un umbral.
 * Recorre todos los usuarios y crea conexiones entre ellos si su similitud de Jaccard es mayor o igual al umbral.
 * @param users Arreglo de usuarios a evaluar.
 * @param num_users Número total de usuarios.
 * @param graph Grafo donde se almacenarán las conexiones.
 * @param threshold Valor mínimo de similitud de Jaccard para crear una conexión.
 */
void create_connections(const User users[MAX_USERS], int num_users, Graph *graph, double threshold)
{
    /**
     * @brief Crea conexiones entre usuarios que tienen un índice de similitud de Jaccard por encima de un umbral.
     * @code
     * int connections_found = 0;
     * for (int i = 0; i < num_users; i++)
     *   for (int j = i + 1; j < num_users; j++)
     *        int count1 = 0, count2 = 0;
     *        double similarity = calculate_jaccard_similarity(users[i].hobbies, count1, users[j].hobbies, count2, users[i].age, users[j].age, users[i].personality, users[j].personality);
     *        if (similarity >= threshold)
     *           connections_found = 1;
     *           fprintf(stdout, CYAN "\nConectando a los usuarios %s y %s (Índice de Jaccard: %.2f)\n" RESET, users[i].username, users[j].username, similarity);
     *           add_connection(graph, i, j);
     * if (!connections_found) ->error
     * @endcode
     */
    int connections_found = 0;

    for (int i = 0; i < num_users; i++)
        for (int j = i + 1; j < num_users; j++)
        {
            int count1 = 0, count2 = 0;

            for (int k = 0; k < MAX_HOBBIES && strlen(users[i].hobbies[k]) > 0; k++)
                count1++;

            for (int k = 0; k < MAX_HOBBIES && strlen(users[j].hobbies[k]) > 0; k++)
                count2++;

            double similarity = calculate_jaccard_similarity(users[i].hobbies, count1, users[j].hobbies, count2, users[i].age, users[j].age, users[i].personality, users[j].personality);

            if (similarity >= threshold)
            {
                connections_found = 1;
                fprintf(stdout, CYAN "\nConectando a los usuarios %s y %s (Índice de Jaccard: %.2f)\n" RESET, users[i].username, users[j].username, similarity);
                add_connection(graph, i, j);
            }
        }

    if (!connections_found)
        fprintf(stdout, CYAN "\nNingún usuario con Índice de Jaccard por encima de %.2f\n" RESET, threshold);
}
