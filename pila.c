#include "pila.h"
#include <stdlib.h>

NodoPila* crearNodoPila(ElementoDeOperacion* elementoDeOperacion){
    NodoPila* nodo = (NodoPila*) malloc(sizeof(NodoPila));
    nodo->elementoDeOperacion= elementoDeOperacion;
    nodo->siguiente=NULL;
    return nodo;
}

void destruirNodoPila(NodoPila* nodo){
    nodo->elementoDeOperacion=NULL;
    nodo->siguiente=NULL;
    free(nodo);
}

Pila* crearPila(){
    Pila* pila =(Pila *)malloc(sizeof(Pila));
    pila->cima=NULL;
    return pila;
}

void destruirPila(Pila* pila){
    while(pila->cima!=NULL){
        desapilar(pila);
    }
    free(pila);
}

void apilar(Pila* pila, ElementoDeOperacion* elementoDeOperacion){
    NodoPila* nodo=crearNodoPila(elementoDeOperacion);
    nodo->siguiente=pila->cima;
    pila->cima=nodo;

}

void desapilar(Pila* pila){
    if(pila->cima !=NULL){
        NodoPila* eliminar = pila->cima;
        pila->cima=pila->cima->siguiente;
        destruirNodoPila(eliminar);
    }
}

ElementoDeOperacion* cimaDePila(Pila* pila){
    if(pila->cima==NULL){
        return NULL;
    }else{
        return pila->cima->elementoDeOperacion;
    }

}



