#include "header.h"



int get_personality_group(const char *personality)
{
    if (personality == NULL || strlen(personality) < 5)
        return 0;

    // 
    if (strncmp(personality, "INT", 3) == 0 || strncmp(personality, "ENT", 3) == 0)
        return 1;  // Analistas
    else if (strncmp(personality, "INF", 3) == 0 || strncmp(personality, "ENF", 3) == 0)
        return 2;  // Diplomaticos
    else if (strncmp(personality, "IST", 3) == 0 || strncmp(personality, "EST", 3) == 0)
        return 3;  // Sentinelas
    else if (strncmp(personality, "ISF", 3) == 0 || strncmp(personality, "ESF", 3) == 0)
        return 4;  // Exploradores

    return 0;
}

void explain_personality_compatibility(const User *user1, const User *user2) {
    const char *group_names[] = {
        "Sin grupo", 
        "Analistas (Racionales)", 
        "Diplomáticos (Idealistas)", 
        "Centinelas (Conservadores)", 
        "Exploradores (Artísticos)"
    };

    int group1 = get_personality_group(user1->personality);
    int group2 = get_personality_group(user2->personality);

    if (group1 == 0 || group2 == 0) {
        fprintf(stdout, " - Compatibilidad no determinada \n");
        return;
    }

    if (group1 == group2) {
        fprintf(stdout, "- Compatibilidad alta por mismo grupo: %s\n", group_names[group1]);
    } else {
        fprintf(stdout, " - Compatibilidad moderada por grupos diferentes:\n");
        fprintf(stdout, "    *%s: %s\n", user1->username, group_names[group1]);
        fprintf(stdout, "    *%s: %s\n", user2->username,  group_names[group2]);
    }
}




double calculate_personality_multiplier(int group1, int group2)
{
    double personality_multiplier = 1.0; // Inicializa el multiplicador de personalidad en 1.0

    if (group1 == group2)                // Si ambos pertenecen al mismo grupo de personalidad
        personality_multiplier = 1.2;    // Aumenta en un 20% el multiplicador
    else if (group1 == 0 || group2 == 0) // Si alguno de los grupos no está reconocido
        personality_multiplier = 1.0;    // multiplicador sigue siendo el normal
    else                                 // Si pertenecen a grupos completamente diferentes
        // Penalización leve por no tener afinidad de grupos
        personality_multiplier = 0.8; // Reduce el multiplicador en un 20% (penalización)

    return personality_multiplier;
}

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

