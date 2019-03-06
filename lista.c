//
//lista.c
//Jesfrin Gonzalez 05/02/19
//201630978 Estrucutura de datos
//


#include "lista.h"
#include <stdlib.h>

NodoLista* crearNodoLista(double numero,int posicion){
    NodoLista* nodo = (NodoLista *)malloc(sizeof(NodoLista));
    nodo->numero=numero;
    nodo->posicion=posicion;
    nodo->siguiente=NULL;
    return nodo;
}

void destruirNodoLista(NodoLista* nodoLista){
    nodoLista->numero=0;
    nodoLista->siguiente=NULL;
    free(nodoLista);
}


Lista* crearLista(){
    Lista* lista =(Lista*)malloc(sizeof(Lista));
    lista->cabeza = NULL;//Aun no exisen valores
    return lista;
}

NodoLista* obtenerUltimoElementoDeLista(Lista* lista){
    if(lista->cabeza==NULL){
        return NULL;
    }else{
       NodoLista* nodo=lista->cabeza;
        while(nodo->siguiente!=NULL){
            nodo=nodo->siguiente;
        }
        return nodo;
    }
}

void recorrerLista(Lista* lista){
    NodoLista* nodo = lista->cabeza;
    if(nodo==NULL){
        printf("La lista esta vacia");
    }else{
        while(nodo->siguiente!=NULL){
            printf("Valor der nodo %f y posicion %d\n",nodo->numero,nodo->posicion);
            nodo=nodo->siguiente;
        }
            printf("Valor der nodo %f y posicion %d\n",nodo->numero,nodo->posicion);
    }
}

void anadirALista(Lista* lista,double numero, int posicion){
    NodoLista* nodo =crearNodoLista(numero,posicion);
    if(lista->cabeza==NULL){//Primer elemento
        lista->cabeza=nodo;
    }else{
        NodoLista* ultimoNodo=obtenerUltimoElementoDeLista(lista);
        ultimoNodo->siguiente=nodo;
    }
}

NodoLista* buscarNodoEnPosicion(Lista* lista,int posicion){
    NodoLista* nodo = lista->cabeza;
    while(nodo->siguiente!=NULL){
        if(nodo->posicion==posicion){
            return nodo;
        }
        nodo=nodo->siguiente;
    }
    if(nodo->posicion==posicion){
            return nodo;
        }
    return NULL;
}


