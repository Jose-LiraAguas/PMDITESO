/**
 * @author José Manuel Lira Aguas
 * @date martes, 29 de noviembre de 2022
*/

#ifndef __DGRAPH_H__
#define __DGRAPH_H__

#include <stddef.h>

typedef enum {false, true } bool;
typedef void * Type;

struct strNode
{
    Type data;
    Type label;
    struct strNode *next;
};

struct strDGraph
{
    struct strNode **adjLists;      //lista de adyacencia de cada vertice
    int maxVertices;                //se genera un espacio extra en el vector para poder agregar vertices
    int numVertices;                //numero de vertices existentes
    size_t data_size;               //tamaño del dato a guardar
    size_t label_size;              //tamaño de la arista que se genera para conectar un vertice a su lista
};

typedef struct strNode * Node;
typedef struct strDGraph * DGraph;

DGraph createDGraph(size_t data_size, size_t label_size);
int sizeDGraph(DGraph DG);
bool adjacent(DGraph DG, Type X, Type Y);
Type neighbors(DGraph DG, Type X, int *n);
void addVertex(DGraph DG, Type X);
void removeVertex(DGraph DG, Type X);
void addEdge(DGraph DG, Type X, Type Y, Type label);
void removeEdge(DGraph DG, Type X, Type Y);
//Type getVertexData(DGraph DG, Type X);
//void setVertexData(DGraph DG, Type X);
Type getEdgeLabel(DGraph DG, Type X, Type Y);
//void setEdgeLabel(DGraph DG, Type X, Type Y, Type label);
void destroyDGraph(DGraph DG);

#endif // __DGRAPH_H__