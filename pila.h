//
//pila.h
//Jesfrin Gonzalez 05/02/19
//201630978 Estrucutura de datos
//

#ifndef pila_h
#define pila_h

#include "elementoDeOperacion.h"
#include<stdio.h>

typedef struct NodoPila{
    ElementoDeOperacion *elementoDeOperacion;
    struct NodoPila* siguiente;
}NodoPila;

typedef struct Pila{
    NodoPila* cima;
}Pila;

NodoPila* crearNodoPila(ElementoDeOperacion* elementoDeOperacion);
void destruirNodoPila(NodoPila* nodo);
Pila* crearPila();
void destruirPila(Pila* pila);
void apilar(Pila* pila, ElementoDeOperacion* elementoDeOperacion);
void desapilar(Pila* pila);
ElementoDeOperacion* cimaDePila(Pila* pila);

#endif // pila_h
