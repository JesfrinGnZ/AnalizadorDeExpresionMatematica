#ifndef lista_h
#define lista_h

#include <stdio.h>
#include "elementoDeOperacion.h"

typedef struct Nodo{
    ElementoDeOperacion elemento;
    struct Nodo* siguiente;
}Nodo;

typedef struct Lista{
    Nodo* cabeza;
}Lista;

#endif

