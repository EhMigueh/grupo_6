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

    srand(time(NULL));

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

    // Dibujar nodos (usuarios). FALTA LA MANERA DE PODER COLOCAR EL NOMBRE AL NODO...
    for (int i = 0; i < graph->numUsers; i++)
    {
        double red = (rand() % 128 + 127) / 255.0;
        double green = (rand() % 128 + 127) / 255.0;
        double blue = (rand() % 128 + 127) / 255.0;
        fprintf(file, "%f %f %f setrgbcolor\n", red, green, blue);
        fprintf(file, "%d %d 10 circle\n", positions[i][0], positions[i][1]);

        fprintf(file, "0 setgray\n");
        fprintf(file, "/Courier findfont 10 scalefont setfont\n");

        fprintf(file, "newpath %d %d moveto (%d) show\n",
                positions[i][0] - 15, positions[i][1] - 3, i + 1);
    }

    fclose(file);
    fprintf(stdout, "El grafo ha sido guardado en el archivo %s.\n\n", filename);

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

    // Crear comando para convertir el archivo EPS a JPG.
    char command[256];
    snprintf(command, sizeof(command), "gs -dSAFER -dBATCH -dNOPAUSE -dEPSCrop -sDEVICE=png16m -r300 -sOutputFile=%s.png %s", filename, filename);

    // Ejecutar comando.
    int result = system(command);
    if (result != 0)
    {
        fprintf(stderr, "Error al intentar convertir el archivo %s a PNG.\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "\nEl archivo %s ha sido convertido a formato JPG.\n\n", filename);
}