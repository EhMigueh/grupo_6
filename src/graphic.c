#include "header.h"

// Función para imprimir el Grafo en formato EPS.
void generate_eps_graph(Graph *graph, const char *filename)
{
    // Verificar si el grafo y el nombre de archivo son válidos
    if (!graph || !filename)
    {
        fprintf(stderr, "Grafo o Nombre de archivo no válidos. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    // Crear archivo EPS.
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "No se pudo crear el archivo %s. Saliendo...\n", filename);
        exit(EXIT_FAILURE);
    }

    // Cabecera del archivo EPS.
    fprintf(file, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(file, "%%%%BoundingBox: 0 0 500 500\n");
    fprintf(file, "/circle { newpath 0 360 arc closepath fill } def\n");

    // Radio del círculo donde se posicionan los nodos.
    int radius = 200;
    int centerX = 250;
    int centerY = 250;
    double angleStep = 2 * M_PI / graph->numUsers;

    // Almacena las posiciones de cada nodo.
    int positions[MAX_USERS][2];
    for (int i = 0; i < graph->numUsers; i++)
    {
        double angle = i * angleStep;
        positions[i][0] = centerX + radius * cos(angle);
        positions[i][1] = centerY + radius * sin(angle);
    }

    // Dibujar conexiones (amistad).
    fprintf(file, "0.8 setgray\n");
    for (int i = 0; i < graph->numUsers; i++)
    {
        Node *current = graph->adjacencyList[i];
        while (current)
        {
            int target = current->id;

            // Evita dibujar líneas duplicadas
            if (i < target)
                fprintf(file, "newpath %d %d moveto %d %d lineto stroke\n", positions[i][0], positions[i][1], positions[target][0], positions[target][1]);

            current = current->next;
        }
    }

    // Dibujar nodos (usuarios) y nombres de cada uno.
    for (int i = 0; i < graph->numUsers; i++)
    {
        // Color aleatorio para cada nodo.
        double red = (random() % 128 + 127) / 255.0;
        double green = (random() % 128 + 127) / 255.0;
        double blue = (random() % 128 + 127) / 255.0;
        fprintf(file, "%f %f %f setrgbcolor\n", red, green, blue);
        fprintf(file, "%d %d 10 circle\n", positions[i][0], positions[i][1]);

        // Agregar nombre del usuario
        fprintf(file, "0 setgray\n");
        fprintf(file, "/Courier findfont 10 scalefont setfont\n");

        fprintf(file, "newpath %d %d moveto (%s) show\n",
                positions[i][0] - 20, positions[i][1] - 15, graph->user_names[i]);
    }

    fclose(file);

    fprintf(stdout, "\nLa imagen del grafo ha sido guardado en la ruta:");
    fprintf(stdout, RED " ./output/social_network.png.\n\n" RESET);

    // Convertir el archivo EPS a JPG.
    transform_eps_png(filename);
}

void transform_eps_png(const char *filename)
{
    // Verificar si el nombre de archivo es válido
    if (!filename)
    {
        fprintf(stderr, "Nombre de archivo no válido. Saliendo...\n");
        exit(EXIT_FAILURE);
    }

    // Crear una copia del nombre de archivo para manipularlo.
    char base_filename[256];
    strncpy(base_filename, filename, sizeof(base_filename) - 1);
    base_filename[sizeof(base_filename) - 1] = '\0';

    // Busca la extensión del archivo .eps y eliminarla.
    char *ext = strrchr(base_filename, '.');
    if (ext && strcmp(ext, ".eps") == 0)
        *ext = '\0'; // Eliminar la extensión .eps

    // Crear comando para convertir el archivo EPS a JPG.
    char command[512];
    snprintf(command, sizeof(command), "gs -dSAFER -dBATCH -dNOPAUSE -dEPSCrop -sDEVICE=png16m -r300 -sOutputFile=%s.png %s > /dev/null 2>&1", base_filename, filename);

    // Ejecutar comando.
    int result = system(command);
    if (result != 0)
    {
        fprintf(stderr, "Error al intentar convertir el archivo %s a PNG. Saliendo...\n", filename);
        exit(EXIT_FAILURE);
    }

    // Eliminar el archivo EPS.
    if (remove(filename) != 0)
    {
        fprintf(stderr, "Error al intentar eliminar el archivo %s. Saliendo...\n", filename);
        exit(EXIT_FAILURE);
    }
}