/**
 * @file main.c
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras, Benjamin Sanhueza y Johann Fink-
 * @brief Programa principal que gestiona la creación de usuarios, el grafo de conexiones sociales, y las recomendaciones entre usuarios en base a similitudes,
 * También se encarga de cargar datos desde archivos y generar publicaciones aleatorias.
 */

/**
 * @brief Función principal que gestiona el flujo del programa, incluyendo la inicialización de usuarios, carga de datos,
 * creación del grafo de conexiones y recomendaciones entre usuarios. 
 * @param argc Número de argumentos de la línea de comandos.
 * @param argv Arreglo de argumentos pasados al programa.
 * @return EXIT_SUCCESS si la ejecución fue exitosa, EXIT_FAILURE en caso de error.
 */
#include "main.h"

int main(int argc, char *argv[])
{
    /**
    * @brief  Función principal que gestiona el flujo del programa, incluyendo la inicialización de usuarios, carga de datos,
    * creación del grafo de conexiones y recomendaciones entre usuarios. 
    * @code 
    * int opt;
    * int num_users = 0;
    * int exists_users = 0; 
    * int total_users = 0;
    * while ((opt = getopt(argc, argv, "hu:")) != -1)
    * 
    * if (num_users <= 0 || num_users > MAX_USERS)
    *   Validar que el número de usuarios sea un valor positivo y menor o igual a 50.
    * srandom((unsigned int)time(NULL));
    * Post_List post_list;      
    * init_post_list(&post_list);
    * char male_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH];     
    * char female_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH];         
    * char hobbies_list[MAX_FILE_LINES][MAX_HOBBIE_LENGTH];     
    * char personalities_list[MAX_FILE_LINES][MAX_PERS_LENGTH]; 
    * int male_count = 0;
    * int female_count = 0;
    * int hobby_count = 0;
    * int personality_count = 0;
    * load_file("./input/male_usernames.txt", male_usernames, &male_count);
    * load_file("./input/female_usernames.txt", female_usernames, &female_count);
    * load_file("./input/hobbies.txt", hobbies_list, &hobby_count);
    * load_file("./input/personalities.txt", personalities_list, &personality_count);
    * User users[MAX_USERS]; // Arreglo de usuarios.
    * if (log_check())
    *   Verifica la existencia de un historial.
    * if (total_users > MAX_USERS)
    *   Capacidad maxima de usuarios alcanzada.
    * for (int i = exists_users; i < total_users; i++)
    *   Generar usuarios aleatorios.
    * log_clean(); 
    * fprintf(stdout, RED "\nUsuarios generados:\n" RESET);
    * for (int i = 0; i < total_users; i++)
    *   imprime usuarios generados
    * Graph *socialNetwork = initialize_graph(total_users, users);
    * if (!socialNetwork)
    *   Inicialiaz el grafo con el numero de usuarios.
    * double threshold = 0.3; 
    * fprintf(stdout, RED "\nRecomendaciones para los Usuarios:\n" RESET);
    * recommend_users(users, total_users);
    * fprintf(stdout, RED "\nConexiones creadas:\n" RESET);
    * create_connections(users, total_users, socialNetwork, threshold);
    * fprintf(stdout, RED "\nGrafo de Conexiones:\n\n" RESET);
    * for (int i = 0; i < total_users; i++)
    *    Mostrar el grafo.
    * generate_random_posts(users, total_users, &post_list);
    * display_all_posts(&post_list);
    * fprintf(stdout, RED "Usuario con más amigos:\n" RESET);
    * int userIndex = find_user_with_most_friends(socialNetwork);
    * if (userIndex != -1)
    *    print_friends_of_user(socialNetwork, userIndex);
    * generate_eps_graph(socialNetwork, "./output/social_network.eps");
    * free_graph(socialNetwork);
    * free_all_posts(&post_list);
    * if (total_users >= (MAX_USERS - 10)) -> Warning de cantidad maxima de usuarios cercana.
    * return EXIT_SUCCESS;
    * @endcode
    */
    int opt;
    int num_users = 0;
    int exists_users = 0; // Conteo para el historial.
    int total_users = 0;  // Conteo de usuarios + usuarios existentes.

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

    Post_List post_list;        // Crear la lista de publicaciones.
    init_post_list(&post_list); // Inicializar la lista de publicaciones.

    char male_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH];     // Arreglo de nombres de usuario masculinos.
    char female_usernames[MAX_FILE_LINES][MAX_NAME_LENGTH];   // Arreglo de nombres de usuario femeninos.
    char hobbies_list[MAX_FILE_LINES][MAX_HOBBIE_LENGTH];     // Arreglo de hobbies.
    char personalities_list[MAX_FILE_LINES][MAX_PERS_LENGTH]; // Arreglo de personalidades.
    int male_count = 0;
    int female_count = 0;
    int hobby_count = 0;
    int personality_count = 0;

    // Cargar los archivos de texto que contiene los nombres de usuarios (masculinos y femeninos) y hobbies.
    load_file("./input/male_usernames.txt", male_usernames, &male_count);
    load_file("./input/female_usernames.txt", female_usernames, &female_count);
    load_file("./input/hobbies.txt", hobbies_list, &hobby_count);
    load_file("./input/personalities.txt", personalities_list, &personality_count);

    User users[MAX_USERS]; // Arreglo de usuarios.

    // Verifica la existencia de un historial.
    if (log_check())
    {
        user_count_from_log(&exists_users);
        log_input(users);
        total_users = num_users + exists_users;
    }
    else
        total_users = num_users;

    if (total_users > MAX_USERS)
    {
        fprintf(stderr, RED "\nCapacidad de maxima de usuarios alcanzada. Saliendo...\n\n" RESET);
        exit(EXIT_FAILURE);
    }

    // Generar usuarios aleatorios.
    for (int i = exists_users; i < total_users; i++)
        generate_random_users(&users[i], i + 1, male_usernames, male_count, female_usernames, female_count, hobbies_list, hobby_count, personalities_list, personality_count);

    log_clean(); // Limpia el historial antes de imprimir el nuevo historial

    // Imprimir los usuarios generados.
    fprintf(stdout, RED "\nUsuarios generados:\n" RESET);
    for (int i = 0; i < total_users; i++)
    {
        fprintf(stdout, GREEN "\nUsuario %d:\n" RESET, i + 1);
        log_output(&users[i]); // Imprime el historial
        print_users(&users[i]);
    }

    // Inicialiaz el grafo con el numero de usuarios.
    Graph *socialNetwork = initialize_graph(total_users, users);
    if (!socialNetwork)
    {
        fprintf(stderr, "Error al intentar inicializar el grafo. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    double threshold = 0.3; // Umbral de similitud para conectar usuarios.

    fprintf(stdout, RED "\nRecomendaciones para los Usuarios:\n" RESET);
    recommend_users(users, total_users);

    // Depuración: Asegurarse de que se crean las conexiones...
    fprintf(stdout, RED "\nConexiones creadas:\n" RESET);
    create_connections(users, total_users, socialNetwork, threshold);

    // Mostrar el grafo.
    fprintf(stdout, RED "\nGrafo de Conexiones:\n\n" RESET);
    for (int i = 0; i < total_users; i++)
        display_graph(socialNetwork, i);

    // Generar publicaciones aleatorias.
    generate_random_posts(users, total_users, &post_list);

    // Mostrar todas las publicaciones.
    display_all_posts(&post_list);

    // Mostrar el usuario con más amigos.
    fprintf(stdout, RED "Usuario con más amigos:\n" RESET);
    int userIndex = find_user_with_most_friends(socialNetwork);
    if (userIndex != -1)
        print_friends_of_user(socialNetwork, userIndex);

    // Generar imagen del grafo.
    generate_eps_graph(socialNetwork, "./output/social_network.eps");

    // Liberar memoria del grafo.
    free_graph(socialNetwork);
    free_all_posts(&post_list);

    // Warning de cantidad maxima de usuarios cercana.
    if (total_users >= (MAX_USERS - 10))
        fprintf(stdout, YELLOW "Se esta alcanzando la capacidad máxima de usuarios, %d Usuarios Existentes \n\n" RESET, total_users);

    return EXIT_SUCCESS;
}
