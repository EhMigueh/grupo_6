#include "header.h"

int main(int argc, char *argv[])
{
    int opt;
    int num_users = 0;
    Graph *socialNetwork = initializeGraph(num_users); 
    if (!socialNetwork) {
    	fprintf(stderr, "Error: No se pudo inicializar el grafo.\n");
    	return EXIT_FAILURE;
	}

    while ((opt = getopt(argc, argv, "hu:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            fprintf(stdout, "\nUso del programa:\n");
            fprintf(stdout, "  -u <numero_de_usuarios> : Número de usuarios a crear.\n");
            fprintf(stdout, "  -h : Muestra esta ayuda.\n\n");
            exit(EXIT_SUCCESS);
            break;
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
        fprintf(stderr, "Error: Debes especificar un valor positivo para -u.\n");
        fprintf(stderr, "Uso: %s [-u numero_de_usuarios]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

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
        generate_random_users(&users[i], i + 1, male_usernames, male_count, female_usernames, female_count,
                              hobbies_list, hobby_count, personalities_list, personality_count);

    // Imprimir los usuarios generados.
    for (int i = 0; i < num_users; i++)
    {
        fprintf(stdout, "\nUsuario %d:\n", i + 1);
        get_users_log(&users[i]); // Historial de Usuarios {Hacer su propio bucle for?}
        print_users(&users[i]);
    }

    double threshold = 0.5; // Umbral de similitud para conectar usuarios
    //create_connections(users, num_users, socialNetwork, threshold);

    recommend_users(users, num_users);


     // Mostrar el grafo
    displayGraph(socialNetwork);

    // Liberar memoria del grafo
    freeGraph(socialNetwork);
    return EXIT_SUCCESS;
}
