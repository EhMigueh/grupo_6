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
