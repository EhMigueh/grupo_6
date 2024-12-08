/**
 * @file parameters.c
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras, Benjamin Sanhueza y Johann Fink
 * @brief Funciones para la comparación y recomendación de usuarios basadas en la personalidad, edad y hobbies.
 */
#include "main.h"

/**
 * @brief Determina el grupo de personalidad de un usuario,compara las primeras tres letras de la personalidad del usuario y devuelve un grupo.
 * @param personality La personalidad del usuario.
 * @return El grupo de personalidad correspondiente (1: Analistas, 2: Diplomáticos, 3: Sentinelas, 4: Exploradores, 0 si no se encuentra).
 */
int get_personality_group(const char *personality)
{
    if (personality == NULL || strlen(personality) < 5)
        return 0;

    // Compara las primeras 3 letras de la personalidad
    if (strncmp(personality, "INT", 3) == 0 || strncmp(personality, "ENT", 3) == 0)
        return 1; // Analistas
    else if (strncmp(personality, "INF", 3) == 0 || strncmp(personality, "ENF", 3) == 0)
        return 2; // Diplomaticos
    else if (strncmp(personality, "IST", 3) == 0 || strncmp(personality, "EST", 3) == 0)
        return 3; // Sentinelas
    else if (strncmp(personality, "ISF", 3) == 0 || strncmp(personality, "ESF", 3) == 0)
        return 4; // Exploradores

    return 0;
}
/**
 * @brief Explica la compatibilidad de personalidad entre dos usuarios,Compara los grupos de personalidad de dos usuarios e imprime su nivel de compatibilidad.
 * @param user1 El primer usuario.
 * @param user2 El segundo usuario.
 */
void explain_personality_compatibility(const User *user1, const User *user2)
{
    const char *group_names[] = {"Sin grupo", "Analistas (Racionales)", "Diplomáticos (Idealistas)", "Centinelas (Conservadores)", "Exploradores (Artísticos)"};

    int group1 = get_personality_group(user1->personality);
    int group2 = get_personality_group(user2->personality);

    if (group1 == 0 || group2 == 0)
    {
        fprintf(stdout, "   - Compatibilidad no determinada \n");
        return;
    }

    if (group1 == group2)
        fprintf(stdout, "   - Compatibilidad alta por mismo grupo: %s\n", group_names[group1]);
    else
        fprintf(stdout, "   - Compatibilidad BAJA por grupos diferentes: %s: %s - %s: %s\n", user1->username, group_names[group1], user2->username, group_names[group2]);
}

/**
 * @brief Calcula el multiplicador de personalidad entre dos usuarios.Si ambos usuarios pertenecen al mismo grupo de personalidad, se aumenta el multiplicador. Si no, se reduce.
 * @param group1 El grupo de personalidad del primer usuario.
 * @param group2 El grupo de personalidad del segundo usuario.
 * @return Un valor flotante que representa el multiplicador de compatibilidad de personalidad.
 */
double calculate_personality_multiplier(int group1, int group2)
{
    double personality_multiplier = 1.0; // Inicializa el multiplicador de personalidad en 1.0

    if (group1 == group2)                // Si ambos pertenecen al mismo grupo de personalidad
        personality_multiplier = 1.2;    // Aumenta en un 20% el multiplicador
    else if (group1 == 0 || group2 == 0) // Si alguno de los grupos no está reconocido
        personality_multiplier = 1.0;    // multiplicador sigue siendo el normal
    else                                 // Si pertenecen a grupos completamente diferentes
        personality_multiplier = 0.8;    // Reduce el multiplicador en un 20% (penalización)

    return personality_multiplier;
}


/**
 * @brief Obtiene el nivel de compatibilidad basado en la diferencia de edad.
 * @param age_diff La diferencia de edad entre dos usuarios.
 * @return Una cadena de texto que indica el nivel de compatibilidad basado en la diferencia de edad.
 */
// Función para obtener una descripción del nivel de compatibilidad por edad.
const char *get_age_compatibility_level(int age_diff)
{
    if (age_diff <= 5)
        return "Excelente";
    else if (age_diff <= 10)
        return "Buena";
    else if (age_diff <= 15)
        return "Moderada";
    else if (age_diff <= 20)
        return "Baja";
    else
        return "Muy baja";
}


/**
 * @brief Calcula el peso de la compatibilidad basado en la diferencia de edad, dependiendo de la diferencia de edad, se aplica un factor de penalización.
 * @param age1 La edad del primer usuario.
 * @param age2 La edad del segundo usuario.
 * @return Un valor flotante que representa el peso de la compatibilidad basado en la diferencia de edad.
 */
double calculate_age_weight(int age1, int age2)
{
    int age_diff = abs(age1 - age2);

    // Diferentes factores según el rango de diferencia de edad.
    if (age_diff <= 5)
        return 1.0; // Diferencia pequeña: sin penalización.
    else if (age_diff <= 10)
        return 0.8; // Diferencia moderada: penalización media.
    else if (age_diff <= 15)
        return 0.6; // Diferencia significativa: penalización alta.
    else if (age_diff <= 20)
        return 0.4; // Diferencia grande: penalización muy alta.
    else
        return 0.2; // Diferencia muy grande: penalización máxima.
}
/**
 * @brief Encuentra los hobbies comunes entre dos usuarios, compara los hobbies de ambos usuarios e imprime los que son comunes.
 * @param hobbies1 Lista de hobbies del primer usuario.
 * @param count1 El número de hobbies del primer usuario.
 * @param hobbies2 Lista de hobbies del segundo usuario.
 * @param count2 El número de hobbies del segundo usuario.
 */
//  Encontrar los hobbies comunes entre dos usuarios.
void find_common_hobbies(const char hobbies1[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int count1, const char hobbies2[MAX_HOBBIES][MAX_HOBBIE_LENGTH], int count2)
{
    fprintf(stdout, "   - Hobbies en común: ");
    int found_common = 0;

    // Usar un conjunto para los hobbies del primer usuario
    char seen[MAX_HOBBIES][MAX_HOBBIE_LENGTH];
    int seen_count = 0;

    // Almacenar los hobbies del primer usuario
    for (int i = 0; i < count1; i++)
        strcpy(seen[seen_count++], hobbies1[i]);

    // Verificar los hobbies del segundo usuario
    for (int j = 0; j < count2; j++)
    {
        for (int k = 0; k < seen_count; k++)
        {
            if (strcmp(hobbies2[j], seen[k]) == 0)
            {
                if (found_common)
                    fprintf(stdout, ", ");

                fprintf(stdout, "%s", hobbies2[j]);
                found_common = 1;
                break;
            }
        }
    }

    if (!found_common)
        fprintf(stdout, "Ninguno");

    fprintf(stdout, "\n");
}


/**
 * @brief Ordena un arreglo de matches utilizando el algoritmo de quicksort, el arreglo se ordena de mayor a menor según la similitud entre los usuarios.
 * @param matches El arreglo de matches a ordenar.
 * @param low El índice más bajo del subarreglo.
 * @param high El índice más alto del subarreglo.
 */
// Ordenar matches de mayor a menor
void quicksort(Match matches[], int low, int high)
{
    if (low < high)
    {
        // Encontrar el índice del pivote
        int pivot_index = partition(matches, low, high);

        // Ordenar recursivamente las dos mitades
        quicksort(matches, low, pivot_index - 1);
        quicksort(matches, pivot_index + 1, high);
    }
}
/**
 * @brief Realiza la partición del arreglo para el algoritmo quicksort.
 * @param matches El arreglo de matches a ordenar.
 * @param low El índice más bajo del subarreglo.
 * @param high El índice más alto del subarreglo.
 * @return El índice de partición que divide el arreglo en dos subarreglos.
 */
// Realiza la partición del arreglo para el algoritmo
int partition(Match matches[], int low, int high)
{
    // Escoger el último elemento como pivote
    double pivot = matches[high].similarity;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (matches[j].similarity >= pivot)
        {
            i++;
            // Intercambiar elementos
            Match temp = matches[i];
            matches[i] = matches[j];
            matches[j] = temp;
        }
    }

    // Colocar el pivote en su posición final
    Match temp = matches[i + 1];
    matches[i + 1] = matches[high];
    matches[high] = temp;

    return i + 1;
}







