#ifndef lista_h
#define lista_h

#include <stdio.h>
#include "elementoDeOperacion.h"

typedef struct NodoLista{
    double numero;
    int posicion;
    struct NodoLista* siguiente;
}NodoLista;

typedef struct Lista{
    NodoLista* cabeza;
}Lista;

NodoLista* crearNodoLista(double numero,int posicion);
void destruirNodoLista(NodoLista* nodoLista);
Lista* crearLista();
NodoLista* obtenerUltimoElementoDeLista(Lista* lista);
void recorrerLista(Lista* lista);
void anadirALista(Lista* lista,double numero, int posicion);
NodoLista* buscarNodoEnPosicion(Lista* lista,int posicion);

#endif

