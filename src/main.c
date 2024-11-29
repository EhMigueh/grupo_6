#include "header.h"

int main(int argc, char *argv[])
{
    int opt;
    int num_users = 0;

    while ((opt = getopt(argc, argv, "hu:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            fprintf(stdout, "\nUso del programa:\n");
            fprintf(stdout, "  -u <numero_de_usuarios> : Número de usuarios a crear.\n");
            fprintf(stdout, "  -h : Muestra esta ayuda.\n\n");
            exit(EXIT_SUCCESS);
        case 'u':
            num_users = atoi(optarg);
            break;
        case '?':
            fprintf(stderr, "Opción no reconocida: -%c\n", optopt);
            exit(EXIT_FAILURE);
        default:
            fprintf(stderr, "Uso: %s [-u numero_de_usuarios]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Validar que el número de usuarios sea un valor positivo y menor o igual a 50.
    if (num_users <= 0 || num_users > MAX_USERS)
    {
        fprintf(stderr, "Error se debe especificar un valor para -u. Saliendo...\n");
        fprintf(stderr, "Uso: %s [-u numero_de_usuarios]\n", argv[0]);
        fprintf(stderr, "Para más información, ejecute: %s -h\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    srandom((unsigned int)time(NULL));

    char male_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH];     // Arreglo de nombres de usuario masculinos.
    char female_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH];   // Arreglo de nombres de usuario femeninos.
    char hobbies_list[MAX_FILE_LINES][MAX_HOBBIE_LENGTH];     // Arreglo de hobbies.
    char personalities_list[MAX_FILE_LINES][MAX_PERS_LENGTH]; // Arreglo de personalidades.
    int male_count = 0;
    int female_count = 0;
    int hobby_count = 0;
    int personality_count = 0;

    // Cargar los archivos de texto que contiene los nombres de usuarios (masculinos y femeninos) y hobbies.
    load_file("male_usernames.txt", male_usernames, &male_count);
    load_file("female_usernames.txt", female_usernames, &female_count);
    load_file("hobbies.txt", hobbies_list, &hobby_count);
    load_file("personalities.txt", personalities_list, &personality_count);

    User users[MAX_USERS]; // Arreglo de usuarios.

    // Generar usuarios aleatorios.
    for (int i = 0; i < num_users; i++)
        generate_random_users(&users[i], i + 1, male_usernames, male_count, female_usernames, female_count, hobbies_list, hobby_count, personalities_list, personality_count);

    // Imprimir los usuarios generados.
    for (int i = 0; i < num_users; i++)
    {
        fprintf(stdout, GREEN "\nUsuario %d:\n" RESET, i + 1);
        log_output(&users[i]);
        print_users(&users[i]);
    }

    // Inicialiaz el grafo con el numero de usuarios.
    Graph *socialNetwork = initialize_graph(num_users, users);
    if (!socialNetwork)
    {
        fprintf(stderr, "Error al intentar inicializar el grafo. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    double threshold = 0.3; // Umbral de similitud para conectar usuarios.

    recommend_users(users, num_users);

    // Depuración: Asegurarse de que se crean las conexiones...
    fprintf(stdout, "\nCreando conexiones.....\n");
    create_connections(users, num_users, socialNetwork, threshold);

    // Depuración: Imprimir el número de usuarios...
    fprintf(stdout, "\nNúmero de usuarios: %d\n", num_users);

    /*
        // Agregar conexiones de prueba
        printf("\nAgregando conexiones de prueba manuales...\n");
        for (int i = 0; i < num_users - 1; i++)
        {
            addConnection(socialNetwork, i, i + 1);
        }
    */

    // Mostrar el grafo.
    fprintf(stdout, "\nMostrando grafo:\n");
    display_graph(socialNetwork);

    // Generar imagen del grafo.
    fprintf(stdout, "\nGuardando grafo en un archivo EPS...\n");
    generate_eps_graph(socialNetwork, "social_network.eps");

    // Liberar memoria del grafo.
    free_graph(socialNetwork);

    return EXIT_SUCCESS;
}
