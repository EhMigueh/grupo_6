#include "main.h"

//  Calcular el índice de Jaccard entre dos conjuntos de hobbies considerando su edad y personalidad
double calculate_jaccard_similarity(const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int count1, const char hobbies2[MAX_HOBBIE_LENGTH][MAX_HOBBIE_LENGTH], int count2, int age1, int age2, const char *personality1, const char *personality2)
{
    int intersection = 0, union_count = 0;

    // Crear un arreglo para marcar si ya hemos contado un hobby.
    char seen[MAX_HOBBIES][MAX_HOBBIE_LENGTH] = {0};
    int seen_count = 0;

    // Contar intersección.
    for (int i = 0; i < count1; i++)
        for (int j = 0; j < count2; j++)
            if (strcmp(hobbies1[i], hobbies2[j]) == 0)
            {
                intersection++;
                break;
            }

    // Contar unión.
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

    // Calcular similitud de Jaccard base.
    double jaccard = union_count > 0 ? (double)intersection / union_count : 0.0;

    // Aplicar el factor de ponderación por edad.
    double age_weight = calculate_age_weight(age1, age2);

    // Obtener grupos de personalidad
    int group1 = get_personality_group(personality1);
    int group2 = get_personality_group(personality2);

    // Obtener el multiplicador de personalidad
    double personality_multiplier = calculate_personality_multiplier(group1, group2);

    // Calcular y retornar el puntaje ajustado
    return jaccard * age_weight * personality_multiplier; // Retorna el puntaje ajustado por edad y el multiplicador de personalidad
}

void recommend_users(const User users[MAX_USERS], int num_users)
{
    for (int i = 0; i < num_users; i++)
    {
        fprintf(stdout, CYAN "\nUsuario %d (%s, %d años):" RESET, users[i].id, users[i].username, users[i].age);

        Match matches[MAX_USERS];
        int match_count = 0;
        int count1 = 0, count2 = 0;

        // Calcular el número de hobbies para el usuario i.
        for (int k = 0; k < MAX_HOBBIES && strlen(users[i].hobbies[k]) > 0; k++)
            count1++;

        // Encontrar todas las coincidencias.
        for (int j = 0; j < num_users; j++)
        {
            if (i == j)
                continue;

            count2 = 0;

            for (int k = 0; k < MAX_HOBBIES && strlen(users[j].hobbies[k]) > 0; k++)
                count2++;

            double similarity = calculate_jaccard_similarity(users[i].hobbies, count1, users[j].hobbies, count2, users[i].age, users[j].age, users[i].personality, users[j].personality);

            // Almacenar todas las coincidencias con similitud > 0.
            if (similarity > 0)
            {
                matches[match_count].user_index = j;
                matches[match_count].similarity = similarity;
                matches[match_count].age_diff = abs(users[i].age - users[j].age);
                match_count++;
            }
        }

        // Ordenar las coincidencias por similitud (método quicksort).
        if (match_count > 1)
        {
            quicksort(matches, 0, match_count - 1);
        }
        // Mostrar las mejores coincidencias (hasta 3)
        int show_matches = match_count > 3 ? 3 : match_count;

        if (show_matches > 0)
        {
            fprintf(stdout, "\nMejores coincidencias:\n");

            for (int m = 0; m < show_matches; m++)
            {
                int j = matches[m].user_index;

                // Mostrar id junto con el nombre y edad
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

void create_connections(const User users[MAX_USERS], int num_users, Graph *graph, double threshold)
{
    int connections_found = 0; // Variable para verificar si se encuentran conexiones

    for (int i = 0; i < num_users; i++)
        for (int j = i + 1; j < num_users; j++)
        {
            int count1 = 0, count2 = 0;

            // Contar hobbies para ambos usuarios.
            for (int k = 0; k < MAX_HOBBIES && strlen(users[i].hobbies[k]) > 0; k++)
                count1++;

            for (int k = 0; k < MAX_HOBBIES && strlen(users[j].hobbies[k]) > 0; k++)
                count2++;

            // Calcular la similitud.
            double similarity = calculate_jaccard_similarity(users[i].hobbies, count1, users[j].hobbies, count2, users[i].age, users[j].age, users[i].personality, users[j].personality);

            // Verificar si la similitud supera el umbral.
            if (similarity >= threshold)
            {
                // Si encontramos una conexión, actualizamos la variable connections_found
                connections_found = 1;

                // Mostrar nombres de los usuarios conectados y sus IDs
                fprintf(stdout, CYAN "\nConectando a los usuarios %s y %s (Índice de Jaccard: %.2f)\n" RESET, users[i].username, users[j].username, similarity);

                // Realizar la conexión entre los usuarios
                add_connection(graph, i, j);
            }
        }

    // Si no se encontraron conexiones, mostrar un mensaje
    if (!connections_found)
        fprintf(stdout, CYAN "\nNingún usuario con Índice de Jaccard por encima de %.2f\n" RESET, threshold);
}
