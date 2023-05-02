/**
 * @author José Manuel Lira Aguas
 * @date martes, 29 de noviembre de 2022
*/

#include <stdio.h>
#include <stdlib.h>

#include "DGraph.h"


int main()
{
    // Creamos un grafo de chars.
        DGraph DG = createDGraph(sizeof(char), sizeof(int));
        printf("Grafo construido\n");

    // Tamaño del grafo
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

    // Agregamos vertices.
        char v;

        v = 'A';
        printf("Agregar vertice'%c'\n", v);
        addVertex(DG, (Type)&v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        v = 'B';
        printf("Agregar vertice'%c'\n", v);
        addVertex(DG, (Type)&v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        v = 'C';
        printf("Agregar vertice'%c'\n", v);
        addVertex(DG, (Type)&v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        // Añadimos vértice repetido.
        v = 'B';
        printf("Agregar vertice'%c'\n", v);
        addVertex(DG, (Type)&v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        v = 'D';
        printf("Agregar vertice'%c'\n", v);
        addVertex(DG, (Type)&v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        v = 'E';
        printf("Agregar vertice'%c'\n", v);
        addVertex(DG, (Type)&v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        // Añadimos vértice repetido.
        v = 'A';
        printf("Agregar vertice'%c'\n", v);
        addVertex(DG, (Type)&v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        // Añadimos vértice repetido.
        v = 'E';
        printf("Agregar vertice'%c'\n", v);
        addVertex(DG, (Type)&v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        v = 'F';
        printf("Agregar vertice'%c'\n", v);
        addVertex(DG, (Type)&v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

    // Añadimos aristas
        char v1, v2;
        int e;

        v1 = 'A'; v2 = 'B'; e = 6u;
        printf("Agregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        v1 = 'B'; v2 = 'C'; e = 7u;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        v1 = 'C'; v2 = 'B'; e = 4u;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        v1 = 'C'; v2 = 'A'; e = 5u;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        v1 = 'D'; v2 = 'C'; e = 10;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        v1 = 'E'; v2 = 'F'; e = 3u;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        v1 = 'F'; v2 = 'E'; e = 1;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        // Vertices que no existen.
        v1 = 'F'; v2 = 'G'; e = 1;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        // Vertices que no existen.
        v1 = 'H'; v2 = 'E'; e = 1;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        v1 = 'E'; v2 = 'A'; e = 4u;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        v1 = 'F'; v2 = 'D'; e = 3u;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        // Repetimos aristas
        v1 = 'E'; v2 = 'A'; e = 4u;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        // Repetimos aristas
        v1 = 'F'; v2 = 'D'; e = 3u;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

        v1 = 'C'; v2 = 'E'; e = 13u;
        printf("\nAgregar arista '%d', '%c' -> '%c'\n", e, v1, v2);
        addEdge(DG, (Type)&v1, (Type)&v2, (Type)&e);

    // Vertices adyacentes
        v1 = 'A'; v2 = 'B';
        printf("\n'%c' & '%c' son adyacentes? %d\n\n", v1, v2, adjacent(DG, (Type)&v1, (Type)&v2));

        v1 = 'C'; v2 = 'D';
        printf("'%c' & '%c' son adyacentes? %d\n\n", v1, v2, adjacent(DG, (Type)&v1, (Type)&v2));

        v1 = 'A'; v2 = 'D';
        printf("'%c' & '%c' son adyacentes? %d\n\n", v1, v2, adjacent(DG, (Type)&v1, (Type)&v2));

    // Vecinos
        char *neighbors_data;
        int n;

        v = 'A';
        printf("vecinos de '%c': ", v);
        neighbors_data = (char *)neighbors(DG, (Type)&v, &n);
        if (n != 0) {
            for (int i = 0; i < n; i++)
                printf("'%c', ", *(neighbors_data + i));
            free(neighbors_data);
            printf("\b\b \n\n");
        }
        else {
            printf("Ninguno\n\n");
        }

        v = 'E';
        printf("vecinos de '%c': ", v);
        neighbors_data = (char *)neighbors(DG, (Type)&v, &n);
        if (n != 0) {
            for (int i = 0; i < n; i++)
                printf("'%c', ", *(neighbors_data + i));
            free(neighbors_data);
            printf("\b\b \n\n");
        }
        else {
            printf("None\n\n");
        }

        v = 'F';
        printf("vecinos de '%c': ", v);
        neighbors_data = (char *)neighbors(DG, (Type)&v, &n);
        if (n != 0) {
            for (int i = 0; i < n; i++)
                printf("'%c', ", *(neighbors_data + i));
            free(neighbors_data);
            printf("\b\b \n\n");
        }
        else {
            printf("None\n\n");
        }

    // Eliminamos vértices
        v = 'A';
        printf("Eliiminar vertice '%c'\n", v);
        removeVertex(DG, &v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        v = 'A';
        printf("vecinos de '%c': ", v);
        neighbors_data = (char *)neighbors(DG, (Type)&v, &n);
        if (n != 0) {
            for (int i = 0; i < n; i++)
                printf("'%c', ", *(neighbors_data + i));
            free(neighbors_data);
            printf("\b\b \n\n");
        }
        else {
            printf("None\n\n");
        }
    
        // Vértice con vecino 'A'.
        v = 'E';
        printf("vecinos de '%c': ", v);
        neighbors_data = (char *)neighbors(DG, (Type)&v, &n);
        if (n != 0) {
            for (int i = 0; i < n; i++)
                printf("'%c', ", *(neighbors_data + i));
            free(neighbors_data);
            printf("\b\b \n\n");
        }
        else {
            printf("None\n\n");
        }

        v = 'F';
        printf("Eliiminar vertice '%c'\n", v);
        removeVertex(DG, &v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));

        // Vértice con vecino 'F'.
        v = 'E';
        printf("vecinos de '%c': ", v);
        neighbors_data = (char *)neighbors(DG, (Type)&v, &n);
        if (n != 0) {
            for (int i = 0; i < n; i++)
                printf("'%c', ", *(neighbors_data + i));
            free(neighbors_data);
            printf("\b\b \n\n");
        }
        else {
            printf("Ninguno\n\n");
        }

        // Eliminamos vértice que ya no existe
        v = 'A';
        printf("Eliiminar vertice '%c'\n", v);
        removeVertex(DG, &v);
        printf("Tamaño:: %u v\n\n", sizeDGraph(DG));
    
    // Eliminamos aristas
        v = 'C';
        printf("vecinos de '%c': ", v);
        neighbors_data = (char *)neighbors(DG, (Type)&v, &n);
        if (n != 0) {
            for (int i = 0; i < n; i++)
                printf("'%c', ", *(neighbors_data + i));
            free(neighbors_data);
            printf("\b\b \n");
        }
        else {
            printf("Ninguno\n");
        }

        v1 = 'C'; v2 = 'E';
        printf("\nEliiminar arista'%c' -> '%c'\n", v1, v2);
        removeEdge(DG, (Type)&v1, (Type)&v2);

        v = 'C';
        printf("\nvecinos de '%c': ", v);
        neighbors_data = (char *)neighbors(DG, (Type)&v, &n);
        if (n != 0) {
            for (int i = 0; i < n; i++)
                printf("'%c', ", *(neighbors_data + i));
            free(neighbors_data);
            printf("\b\b \n");
        }
        else {
            printf("Ninguno\n");
        }

        // Arista no existente
        v1 = 'E'; v2 = 'C';
        printf("\nEliiminar arista'%c' -> '%c'\n", v1, v2);
        removeEdge(DG, (Type)&v1, (Type)&v2);

        // Arista ya eliminada
        v1 = 'C'; v2 = 'E';
        printf("\nEliiminar arista'%c' -> '%c'\n", v1, v2);
        removeEdge(DG, (Type)&v1, (Type)&v2);
     
    // Edge Label
        Type vv;
        v1 = 'C'; v2 = 'D';
        printf("\nEtiqueta de '%c' -> '%c': ", v1, v2);
        vv = getEdgeLabel(DG, (Type)&v1, (Type)&v2);
        if (vv != NULL)
            printf("%u\n", *((int *)vv));

        v1 = 'D'; v2 = 'C';
        printf("\nEtiqueta de '%c' -> '%c': ", v1, v2);
        vv = getEdgeLabel(DG, (Type)&v1, (Type)&v2);
        if (vv != NULL)
            printf("%u\n", *((int *)vv));

        v1 = 'A'; v2 = 'Z';
        printf("\nEtiqueta de '%c' -> '%c': ", v1, v2);
        vv = getEdgeLabel(DG, (Type)&v1, (Type)&v2);
        if (vv != NULL)
            printf("%u\n", *((int *)vv));
        
        v1 = 'Z'; v2 = 'A';
        printf("\nEtiqueta de '%c' -> '%c': ", v1, v2);
        vv = getEdgeLabel(DG, (Type)&v1, (Type)&v2);
        if (vv != NULL)
            printf("%u\n", *((int *)vv));

    // Eliminamos el grafo.

        destroyDGraph(DG);
        printf("Grafo destruido\n");
    
    return 0;
}
