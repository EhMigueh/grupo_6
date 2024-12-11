# Simulador de Red Social

Este proyecto simula una **Red Social**, utilizando estructuras de datos complejas como los grafos, listas enlazadas y tablas hash, aparte de algoritmos vistos anteriormente como quicksort, Jaccard y Dijkstra.

## Resumen

El simulador se puede resumir de la siguiente manera:

- Creación de usuarios aleatorios.
- Calculo del índice de Jaccard para comparar la similitud entre los usuarios.
- Creación de las conexiones entre los nodos.
- Simulación de las publicaciones.
- Creación de una imagen gráfica del grafo.

## Uso del Programa

Antes de ejecutar el programa, es necesario compilarlo de manera adecuada y seguir los pasos recomendados a continuación:

### 1. Recomendación Inicial

Apenas posea el programa en su computador, se recomienda que el primer paso a ejecutar sea el comando `make clean`, ubicado en el directorio raíz.

### 2. Compilación del Programa

Para compilar el proyecto completo, ejecute el comando `make` en el directorio raíz del proyecto. Esto utilizará el archivo `Makefile`.

### 3. Limpieza del Historial

El proyecto cuenta con un historial para poder guardar los usuarios anteriormente creados, este historial está límitado a `50 usuarios`, por ende, si quiere seguir utilizando el programa desde cero, debe ejecutar el comando `make clear-log`, esto hará que se limpie el archivo txt que contiene el historial.

### 4. Ejecución

Para poder ejecutar el funcionamiento del proyecto debe utilizar el comando `make run`, esto utiliza el archivo `Makefile`, dentro de este se especifica la cantidad de usuarios que genera, si quiere cambiar la cantidad, debe ingresar al archivo `Makefile` y cambiar el valor allí.

### 5. Documentación

Ejecute el comando `make dxygn` en el directorio raíz del proyecto para generar la documentación automática en formato HTML y LaTeX.

Una vez generados los archivos con Doxygen con el comando `make dxygn`, puede convertir la documentación en un archivo PDF utilizando LaTeX. Para hacerlo, ejecute `make ltx`.

### 6. Ubicación de los archivos PDF y HTML    

El archivo PDF generado estará disponible en el directorio docs/latex/ o en la ubicación configurada en el `Makefile`. El archivo se llama `refman.pdf`.

Los archivos HTML generados se encontrarán en el directorio docs/html/. Para visualizar la documentación, abra el archivo index.html con su navegador. El archivo se llama `index.html`.

### 7. Ubicación del Gráfico y Archivos TXT

El gráfico generado por el programa al final de la ejecución se encuentra en el directorio `output` (visto desde el directorio raíz).

Los archivos .txt que contienen las listas de nombres, hobbies, personalidades e historial, se encuentran en el directorio `input` (visto desde el directorio raíz).