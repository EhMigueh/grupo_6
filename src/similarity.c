#include "header.h"

//  Calcular el índice de Jaccard entre dos conjuntos de hobbies
double calculate_jaccard_similarity(const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int count1,
                                     const char hobbies2[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int count2)
{
    int intersection = 0, union_count = 0;

    // Crear un arreglo para marcar si ya hemos contado un hobby
    char seen[MAX_HOBBIES][MAX_HOBBIE_LENGTH] = {0};
    int seen_count = 0;

    // Contar intersección
    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count2; j++) {
            if (strcmp(hobbies1[i], hobbies2[j]) == 0) {
                intersection++;
                break;
            }
        }
    }

    // Contar unión
    for (int i = 0; i < count1; i++) {
        strcpy(seen[seen_count++], hobbies1[i]);
    }

    for (int j = 0; j < count2; j++) {
        int found = 0;
        for (int k = 0; k < seen_count; k++) {
            if (strcmp(hobbies2[j], seen[k]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(seen[seen_count++], hobbies2[j]);
        }
    }

    union_count = seen_count;

    // Retornar índice de Jaccard
    return union_count > 0 ? (double)intersection / union_count : 0.0;
}

//  Encontrar los hobbies comunes entre dos usuarios.
void find_common_hobbies(const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int count1,
                         const char hobbies2[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int count2)
{
    fprintf(stdout, " - Hobbies en común: ");
    int found_common = 0;

    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count2; j++) {
            if (strcmp(hobbies1[i], hobbies2[j]) == 0) {
                if (found_common) {
                    fprintf(stdout, ", ");
                }
                fprintf(stdout, "%s", hobbies1[i]);
                found_common = 1;
                break;
            }
        }
    }
    if (!found_common) {
        fprintf(stdout, "Ninguno");
    }
    fprintf(stdout, "\n");
}

//  Recomendar usuarios basados en hobbies comunes
void recommend_users(const User users[MAX_USERS], int num_users)
{
    for (int i = 0; i < num_users; i++) {
        // Separador entre recomendaciones
        fprintf(stdout, "\n----------------------------------------\n");

        fprintf(stdout, "Recomendaciones para el usuario %d (%s):\n", users[i].id, users[i].username);

        double max_similarity = 0.0;
        int best_match = -1;
        int count1 = 0, count2 = 0;

        // Calcular el número de hobbies para el usuario i
        for (int k = 0; k < MAX_HOBBIES && strlen(users[i].hobbies[k]) > 0; k++) {
            count1++;
        }

        for (int j = 0; j < num_users; j++) {
            if (i == j) continue; // No comparar un usuario consigo mismo

            // Calcular el número de hobbies para el usuario j
            count2 = 0;
            for (int k = 0; k < MAX_HOBBIES && strlen(users[j].hobbies[k]) > 0; k++) {
                count2++;
            }

            // Calcular índice de Jaccard
            double similarity = calculate_jaccard_similarity(users[i].hobbies, count1, users[j].hobbies, count2);

            if (similarity > max_similarity) {
                max_similarity = similarity;
                best_match = j;
            }
        }

        // Mostrar la mejor coincidencia y los hobbies comunes
        if (best_match != -1) {
            fprintf(stdout, " - Usuario recomendado: %s (Índice de Jaccard: %.2f)\n", users[best_match].username, max_similarity);

            // Pasar los hobbies comunes a find_common_hobbies
            find_common_hobbies(users[i].hobbies, count1, users[best_match].hobbies, count2);
        } else {
            fprintf(stdout, " - No hay usuarios recomendados.\n");
        }
    }
}
