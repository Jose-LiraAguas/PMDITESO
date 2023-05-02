/**
 * @author José Manuel Lira Aguas
 * @date martes, 29 de noviembre de 2022
*/

#include "DGraph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 Crea una nueva instancia de un contenedor DGraph.
 data_size : Numero de bytes que usara la variable `data` en el grafo.
 label_size : Numero de bytes que usara la variable `label` en el grafo.
*/
DGraph createDGraph(size_t data_size, size_t label_size)
{
    //Generar el vector de vertices
    DGraph DG = (DGraph) malloc( sizeof(struct strDGraph)); //Reservar memoria para crear el grafo
    if (DG == NULL) return NULL;                            //Por si no encuentra

    DG-> maxVertices= 1;                            
    DG-> numVertices= 0;                                    //Inicializar el contador de vertices

    //Generar listas de aristas
    DG->adjLists = (Node *) malloc(sizeof(Node) * DG->maxVertices); //Reservar memoria
    if (!DG->adjLists) {                
        free(DG);                                                   //Si no hay memoria se libera
        return NULL;
    }

    for (int i = 0; i < DG->maxVertices; i++)
        *(DG-> adjLists+ i)= NULL;                     //Se genera una lista para cada vertice que de momento apunta a NULL
    
    DG->data_size = data_size;
    DG->label_size = label_size;

    return DG;
}

/*
Retorna el número de vértices que existen en el grafo.
*/
int sizeDGraph(DGraph DG)
{
    return DG->numVertices;                 //Solo regresa el numero de vertices
}

/*
 Verificamos si existe una arista entre X y Y.
- X es el primer vertice, Y el segundo
- Regresa True si hay alguna arista de X a Y o de Y a X, False si no hay
*/
bool adjacent(DGraph DG, Type X, Type Y)
{
    //Caso 1: Se busca X en el vector de nodos
    for (int i= 0; i < DG->numVertices; i++) {
        if (memcmp(X, (*(DG->adjLists + i))-> data, DG-> data_size) == 0 ) {
            Node current = *(DG->adjLists + i);                                 //Se recorre la lista de aristas 
            while (current->next != NULL) {
                if ( memcmp(Y, (current->next)->data, DG->data_size) == 0 )     //Si se encuentren una arista que vaya a Y son adyacentes
                    return true;
                current = current->next;
            }
        }
    //Caso 2: Se busca Y en el vector de nodos, se hace lo mismo que en el caso anterior
        if ( memcmp(Y, (*(DG->adjLists + i))->data, DG->data_size) == 0 ) {
            Node current = *(DG->adjLists + i);
            while (current->next != NULL) {
                if ( memcmp(X, (current->next)->data, DG->data_size) == 0 )
                    return true;
                current = current->next;
            }
        }
    }
    //Si no se encuentran no hay adyacencias
    return false;
}

/*
 Regresa los datos que se encuentran en los vertices vecinos a `X`.

*/
Type neighbors(DGraph DG, Type X,  int *n)
{
    int i, j;
    *n = 0;

    // Se hace lo mismo que al buscar adyacencia
    for (i = 0; i < DG->numVertices; i++) {
        if (memcmp(X, (*(DG->adjLists + i))->data, DG->data_size) == 0 ) {
            Node current = *(DG->adjLists + i);

            // Se cuentan los vecinos de `X`.
            while (current->next != NULL) {
                (*n)++;
                current = current->next;
            }

            break;
        }
    }
    if (i == DG->numVertices) {
        printf("El vertices no existe.\n");
        return NULL;
    }
    
    Type data = malloc(DG->data_size * (*n));
    if (data == NULL) {
        *n = 0;
        return NULL;
    }
    // Se crea una copia de la lista de adyacencia de X
    Node current = *(DG->adjLists + i);
    j = 0;
    while (current->next != NULL) {
        memcpy(data + j * DG->data_size, (current->next)->data, DG->data_size);     //se copia cada valor de los vecinos de x
        j++;
        current = current->next;
    }

    return data;
}

/*
Añade un nuevo vértice X.
*/
void addVertex(DGraph DG, Type X)
{
    // Se verficia que no exista.
    for ( int i = 0; i < DG->numVertices; i++) {
        if ( memcmp(X, (*(DG->adjLists + i))->data, DG->data_size) == 0 ){ 
            printf("El vertice ya existe\n");
            return;
        }
    }

    (DG->numVertices)++;

    // se verifica que se tienen la memoria suficiente para añadir el nuevo vértice.
    // se agrega un elemento mas al vector
    // para asegurarnos que los nuevos vertices tengan espacio en el arreglo `adjLists`.
    if (DG->numVertices > DG->maxVertices) {
        DG->maxVertices += 1;
        Node *more_nodes = (Node *) realloc(DG->adjLists, sizeof(Node) * DG->maxVertices);
        if (more_nodes != NULL) {
            DG->adjLists = more_nodes;
        }
        else {
            free(DG->adjLists);
            DG->adjLists = NULL;
            return;
        }
    }

    // se crea y agrega el nuevo vértice en el arreglo `adjLists`.
    Node newVertex = (Node) malloc(sizeof(struct strNode));
    if (newVertex == NULL) {
        (DG->numVertices)--;
        return;
    }

    newVertex->data = malloc(DG->data_size);
    newVertex->label = NULL;
    newVertex->next = NULL;

    memcpy(newVertex->data, X, DG->data_size);

    *(DG->adjLists + DG->numVertices - 1) = newVertex;
}

/*
 Eliminamos el vértice X.
*/
void removeVertex(DGraph DG, Type X)
{
     int i;

    // se busca el vértice `X` en `adjLists`.
    for (i = 0; i < DG->numVertices; i++) {
        if ( memcmp(X, (*(DG->adjLists + i))->data, DG->data_size) == 0 )
            break;
    }
    if (i == DG->numVertices){
        printf("El vertice no existe.\n");
        return;
    }
    Node current = *(DG->adjLists + i);
    Node aux;

    // sobre la lista del nodo `X` se eliminan los nodos
    while (current != NULL) {
        aux = current;
        current = current->next;

        if (aux->data != NULL) free(aux->data);
        if (aux->label != NULL) free(aux->label);
        free(aux);
    }
    DG->numVertices--;

    // Recorremos los elementos del arreglo `adjLists` que estaban delante del vértice `X`.
    for (i = i; i < DG->numVertices; i++) {
        *(DG->adjLists + i) = *(DG->adjLists + (i + 1));
    }

    // Buscamos aristas que apuntaban al vértice `X` y eliminamos.
    for (i = 0; i < DG->numVertices; i++) {
        current = *(DG->adjLists + i);

        while (current->next != NULL) {
            if ( memcmp(X, (current->next)->data, DG->data_size) == 0 ) {
                aux = current->next;
                current->next = aux->next;

                if (aux->data != NULL) free(aux->data);
                if (aux->label != NULL) free(aux->label);
                free(aux);

                break;
            }
            current = current->next;
        }
    }
}

/* 
Agrega una arista del vértice `X` al vértice `Y` con valor `label`. 
*/
void addEdge(DGraph DG, Type X, Type Y, Type label)
{
     int i;

    // Verificamos que existe el vértice `Y`.
    for (i = 0; i < DG->numVertices; i++) {
        if ( memcmp(Y, (*(DG->adjLists + i))->data, DG->data_size) == 0 )
            break;
    }
    if (i == DG->numVertices) {
        printf("El segundo vertice no existe.\n");
        return;
    }
    // Buscamos el vértice `X`.
    for (i = 0; i < DG->numVertices; i++) {
        if ( memcmp(X, (*(DG->adjLists + i))->data, DG->data_size) == 0 ) {
            Node current = *(DG->adjLists + i);

            // Verificamos que no exista arista al vértice `Y`.
            while (current->next != NULL) {
                if ( memcmp(Y, (current->next)->data, DG->data_size) == 0 ){
                    printf("La arista ya existe.\n");
                    return;
                }
                current = current->next;
            }

            // Creamos y añadimos nodo al final de la lista del vértice `X`.
            Node newNode = (Node) malloc(sizeof(struct strNode));
            if (newNode == NULL) return;

            newNode->data = malloc(DG->data_size);
            newNode->label = malloc(DG->label_size);
            newNode->next = NULL;

            memcpy(newNode->data, Y, DG->data_size);
            memcpy(newNode->label, label, DG->label_size);

            current->next = newNode;
            return;
        }
    }
    if (i == DG->numVertices) {
        printf("El primer vertice no existe.\n");
    }
   
}

/*
Elimina la arista del vértice `X` al vértice `Y`.
*/
void removeEdge(DGraph DG, Type X, Type Y)
{
     int i;

    // Verificamos que existe el vértice `Y`.
    for (i = 0; i < DG->numVertices; i++) {
        if ( memcmp(Y, (*(DG->adjLists + i))->data, DG->data_size) == 0 )
            break;
    }
    if (i == DG->numVertices) {
        printf("El segundo vertice no existe.\n");
        return;
    }

    // Buscamos el vértice `X`.
    for (i = 0; i < DG->numVertices; i++) {
        if ( memcmp(X, (*(DG->adjLists + i))->data, DG->data_size) == 0 ) {
            Node current = *(DG->adjLists + i);

            // Buscamos arista al vértice `Y`.
            while (current->next != NULL) {
                if ( memcmp(Y, (current->next)->data, DG->data_size) == 0 ) {
                    Node aux = current->next;
                    current->next = aux->next;

                    if (aux->data != NULL) free(aux->data);
                    if (aux->label != NULL) free(aux->label);
                    free(aux);

                    return;
                }
                current = current->next;
            }

            printf("La arista no existe\n");
            return;
        }
    }
    if (i == DG->numVertices) {
        printf("El primer vertice no existe.\n");
    }
}


/**
 * Regresa la etiqueta asociada a la arista que une `X` a `Y`.
La etiqueta `label` asociada a la arista de `X` a `Y`.
*/
Type getEdgeLabel(DGraph DG, Type X, Type Y)
{
     int i;

    // Verificamos que existe el vértice `Y`.
    for (i = 0; i < DG->numVertices; i++) {
        if ( memcmp(Y, (*(DG->adjLists + i))->data, DG->data_size) == 0 )
            break;
    }
    if (i == DG->numVertices) {
        printf("El segundo vertice no existe\n");
        return NULL;
    }

    // Buscamos el vértice `X`.
    for (i = 0; i < DG->numVertices; i++) {
        if ( memcmp(X, (*(DG->adjLists + i))->data, DG->data_size) == 0 ) {
            Node current = *(DG->adjLists + i);

            // Buscamos la arista de `X` a `Y`.
            while (current->next != NULL) {
                if ( memcmp(Y, (current->next)->data, DG->data_size) == 0 )
                    return current->next->label;
                current = current->next;
            }

            printf("La arista no existe\n");
            return NULL;
        }
    }
    if (i == DG->numVertices) {
        printf("El primer vertice no existe\n");
    }

    return NULL;
}

/**
 * Destruye la instancia de un contenedor DGraph, liberando toda la memoria dinámica.
*/
void destroyDGraph(DGraph DG)
{
    if (DG == NULL) return;
    
    if (DG->adjLists == NULL) {
        free(DG);
        return;
    }

    // Iteramos sobre el arreglo `adjLists`.
    for ( int i = 0; i < DG->numVertices; i++) {
        Node current = *(DG->adjLists + i);
        Node aux;

        // Iteramos sobre la lista en `i` y eliminamos los nodos de esta.
        while (current != NULL) {
            aux = current;
            current = current->next;

            if (aux->data != NULL) free(aux->data);
            if (aux->label != NULL) free(aux->label);
            free(aux);
        }
    }

    free(DG->adjLists);

    free(DG);
}
