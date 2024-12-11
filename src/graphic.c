/**
 * @file graphic.c
 * @date 08-12-2024
 * @authors Miguel Loaiza, Felipe Paillacar, Ignacio Contreras. Benjamin Sanhueza y Johann Fink
 * @brief funciones para dibujar la conexion entre los grafos
 */
#include "main.h"

/**
 * @brief Genera un archivo EPS que representa un grafo y lo convierte a PNG.
 * @param graph Puntero al grafo que se desea visualizar.
 * @param filename Nombre del archivo EPS a generar.
 * @note Si el grafo o el nombre del archivo no son válidos, el programa finaliza con error.
 */
void generate_eps_graph(Graph *graph, const char *filename)
{
    /**
     * @brief Genera un archivo EPS que representa un grafo y lo convierte a PNG.
     * @code
     * if (!graph || !filename) ->error
     * FILE *file = fopen(filename, "w");
     * if (!file) ->error
     * int radius = 200;
     * int centerX = 250;
     * int centerY = 250;
     * double angleStep = 2 * M_PI / graph->numUsers;
     * int positions[MAX_USERS][2];
     * for (int i = 0; i < graph->numUsers; i++)
     *   Almacena las posiciones de cada nodo.
     * for (int i = 0; i < graph->numUsers; i++)
     *   Dibujar nodos (usuarios) y nombres de cada uno.
     * transform_eps_png(filename);
     * @endcode
     */
    if (!graph || !filename)
    {
        fprintf(stderr, "Grafo o Nombre de archivo no válidos. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "No se pudo crear el archivo %s. Saliendo...\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(file, "%%%%BoundingBox: 0 0 500 500\n");
    fprintf(file, "/circle { newpath 0 360 arc closepath fill } def\n");

    int radius = 200;
    int centerX = 250;
    int centerY = 250;
    double angleStep = 2 * M_PI / graph->numUsers;

    int positions[MAX_USERS][2];
    for (int i = 0; i < graph->numUsers; i++)
    {
        double angle = i * angleStep;
        positions[i][0] = centerX + radius * cos(angle);
        positions[i][1] = centerY + radius * sin(angle);
    }

    fprintf(file, "0.8 setgray\n");
    for (int i = 0; i < graph->numUsers; i++)
    {
        Node *current = graph->adjacencyList[i];
        while (current)
        {
            int target = current->id;

            if (i < target)
                fprintf(file, "newpath %d %d moveto %d %d lineto stroke\n", positions[i][0], positions[i][1], positions[target][0], positions[target][1]);

            current = current->next;
        }
    }

    for (int i = 0; i < graph->numUsers; i++)
    {
        double red = (random() % 128 + 127) / 255.0;
        double green = (random() % 128 + 127) / 255.0;
        double blue = (random() % 128 + 127) / 255.0;
        fprintf(file, "%f %f %f setrgbcolor\n", red, green, blue);
        fprintf(file, "%d %d 10 circle\n", positions[i][0], positions[i][1]);

        fprintf(file, "0 setgray\n");
        fprintf(file, "/Courier findfont 10 scalefont setfont\n");

        fprintf(file, "newpath %d %d moveto (%s) show\n",
                positions[i][0] - 20, positions[i][1] - 15, graph->user_names[i]);
    }

    fclose(file);

    fprintf(stdout, "\nLa imagen del grafo ha sido guardado en la ruta:");
    fprintf(stdout, RED " ./output/social_network.png.\n\n" RESET);

    transform_eps_png(filename);
}

/**
 * @brief Convierte un archivo EPS a PNG y elimina el archivo EPS.
 * Utiliza Ghostscript para realizar la conversión y asegura que el archivo EPS
 * se elimine después de completar el proceso.
 * @param filename Nombre del archivo EPS a convertir.
 * @note Si el nombre del archivo no es válido o la conversión falla, el programa finaliza con error.
 */
void transform_eps_png(const char *filename)
{
    /**
     * @brief Convierte un archivo EPS a PNG y elimina el archivo EPS.
     * @code
     * if (!filename) ->error
     * char base_filename[256];
     * strncpy(base_filename, filename, sizeof(base_filename) - 1);
     * base_filename[sizeof(base_filename) - 1] = '\0';
     * char *ext = strrchr(base_filename, '.');
     * if (ext && strcmp(ext, ".eps") == 0)
     *   Eliminar la extensión .eps
     *  char command[512];
     * snprintf(command, sizeof(command), "gs -dSAFER -dBATCH -dNOPAUSE -dEPSCrop -sDEVICE=png16m -r300 -sOutputFile=%s.png %s > /dev/null 2>&1", base_filename, filename);
     * int result = system(command);
     * if (result != 0) ->error
     * if (remove(filename) != 0)
     *   Eliminar el archivo EPS.
     * @endcode
     */
    if (!filename)
    {
        fprintf(stderr, "Nombre de archivo no válido. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    char base_filename[256];
    strncpy(base_filename, filename, sizeof(base_filename) - 1);
    base_filename[sizeof(base_filename) - 1] = '\0';

    char *ext = strrchr(base_filename, '.');
    if (ext && strcmp(ext, ".eps") == 0)
        *ext = '\0';

    char command[512];
    snprintf(command, sizeof(command), "gs -dSAFER -dBATCH -dNOPAUSE -dEPSCrop -sDEVICE=png16m -r300 -sOutputFile=%s.png %s > /dev/null 2>&1", base_filename, filename);

    int result = system(command);
    if (result != 0)
    {
        fprintf(stderr, "Error al intentar convertir el archivo %s a PNG. Saliendo...\n", filename);
        exit(EXIT_FAILURE);
    }

    if (remove(filename) != 0)
    {
        fprintf(stderr, "Error al intentar eliminar el archivo %s. Saliendo...\n", filename);
        exit(EXIT_FAILURE);
    }
}