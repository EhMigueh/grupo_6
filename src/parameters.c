#include "header.h"

// Tabla hash estática para almacenar los grupos de personalidad.
static int PERSONALITY_GROUP_HASH[HASH_SIZE] = {0};

// Función para calcular el hash de una cadena
unsigned int hash(const char *str)
{
    unsigned int hash = 0;
    while (*str)
    {
        // Calcula el valor del hash acumulando los caracteres.
        hash = (hash * 31 + *str) % HASH_SIZE;
        str++;
    }
    return hash;
}

// Función para inicializar la tabla hash con los grupos de personalidad.
void initialize_personality_hash()
{
    // Tipos de personalidad del grupo "Analistas"
    PERSONALITY_GROUP_HASH[hash("INTJA")] = 1;
    PERSONALITY_GROUP_HASH[hash("INTPA")] = 1;
    PERSONALITY_GROUP_HASH[hash("ENTJA")] = 1;
    PERSONALITY_GROUP_HASH[hash("ENTPA")] = 1;

    // Tipos de personalidad del grupo "Diplomáticos"
    PERSONALITY_GROUP_HASH[hash("INFJA")] = 2;
    PERSONALITY_GROUP_HASH[hash("INFPA")] = 2;
    PERSONALITY_GROUP_HASH[hash("ENFJA")] = 2;
    PERSONALITY_GROUP_HASH[hash("ENFPA")] = 2;

    // Tipos de personalidad del grupo "Centinelas"
    PERSONALITY_GROUP_HASH[hash("ISTJA")] = 3;
    PERSONALITY_GROUP_HASH[hash("ISFJA")] = 3;
    PERSONALITY_GROUP_HASH[hash("ESTJA")] = 3;
    PERSONALITY_GROUP_HASH[hash("ESFJA")] = 3;

    // Tipos de personalidad del grupo "Exploradores"
    PERSONALITY_GROUP_HASH[hash("ISTPA")] = 4;
    PERSONALITY_GROUP_HASH[hash("ISFPA")] = 4;
    PERSONALITY_GROUP_HASH[hash("ESTPA")] = 4;
    PERSONALITY_GROUP_HASH[hash("ESFPA")] = 4;
}

// Función para obtener el grupo de un tipo de personalidad
int get_personality_group(const char *personality)
{
    // Verifica que la cadena de entrada no sea nula y tenga al menos 5 caracteres
    if (personality == NULL || strlen(personality) < 5)
        return 0; // Retorna 0 si la entrada no es válida

    // Calcula el hash del tipo de personalidad
    unsigned int hash_value = hash(personality);

    // Retorna el grupo correspondiente de la tabla hash
    return PERSONALITY_GROUP_HASH[hash_value];
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