#include "header.h"

int main()
{
    srand(time(NULL));

    char male_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH];   // Arreglo de nombres de usuario masculinos.
    char female_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH]; // Arreglo de nombres de usuario femeninos.
    char hobbies_list[MAX_FILE_LINES][MAX_HOBBIE_LENGTH];   // Arreglo de hobbies.
    int male_count = 0;
    int female_count = 0;
    int hobby_count = 0;

    // Cargar los archivos de texto que contiene los nombres de usuarios (masculinos y femeninos) y hobbies
    load_file("male_usernames.txt", male_usernames, &male_count);
    load_file("female_usernames.txt", female_usernames, &female_count);
    load_file("hobbies.txt", hobbies_list, &hobby_count);

    User users[MAX_USERS]; // Arreglo de usuarios.
    int numUsers = 10;     // Cantidad de usuarios a generar.

    // Generar usuarios aleatorios.
    for (int i = 0; i < numUsers; i++)
        generate_random_users(&users[i], i + 1, male_usernames, male_count, female_usernames, female_count, hobbies_list, hobby_count);

    // Imprimir los usuarios generados.
    for (int i = 0; i < numUsers; i++)
    {
        fprintf(stdout, "\nUsuario %d:\n", i + 1);
        print_users(&users[i]);
    }

    /*
    Graph *socialNetwork = initializeGraph(numUsers);
    if (!socialNetwork)
    {
        fprintf(stderr, "Error: No se pudo inicializar el grafo.\n");
        return EXIT_FAILURE;
    }
    loadConnectionsFromFile(socialNetwork, "connections.txt");
    displayGraph(socialNetwork);
    freeGraph(socialNetwork);
    */

    return EXIT_SUCCESS;
}
