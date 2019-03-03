#include "cola.h"
#include <stdlib.h>

NodoCola* crearNodoCola(ElementoDeOperacion* elementoDeOperacion){
    NodoCola* nodo = (NodoCola *)malloc(sizeof(NodoCola));
    nodo->elementoDeOperacion=elementoDeOperacion;
    nodo->siguiente=NULL;
    return nodo;
}

void destruirNodoCola(NodoCola* nodoCola){
    nodoCola->elementoDeOperacion=NULL;
    nodoCola->siguiente=NULL;
    free(nodoCola);
}

Cola* crearCola(){
    Cola* cola =(Cola *)malloc(sizeof(Cola));
    cola->primer = cola->ultimo=NULL;//Aun no exisen valores
    return cola;
}

void destruirCola(Cola* cola){
    while(cola->primer){
        eliminarDeCola(cola);
    }
    free(cola);
}

void encolar(Cola* cola,ElementoDeOperacion* elementoDeOperacion){
    NodoCola* nodo = crearNodoCola(elementoDeOperacion);
    if(!cola->primer){//Cola esta vacia,primer ->NULL
        cola->primer=nodo;
        cola->ultimo=nodo;
    }else{
        cola->ultimo->siguiente=nodo;
        cola->ultimo=nodo;//Siguiente ya es nulo
    }
}

ElementoDeOperacion* consultarCola(Cola* cola){//Retorna elemento al Frente de la cola
    if(cola->primer){
        return cola->primer->elementoDeOperacion;
    }else{
        return NULL;
    }
}

ElementoDeOperacion* consultarFinalDeCola(Cola*  cola){
    if(cola->ultimo){
        return cola->ultimo->elementoDeOperacion;
    }else{
        NULL;
    }
}

void eliminarDeCola(Cola* cola){
    if(cola->primer){
        NodoCola* eliminado = cola->primer;
        cola->primer=cola->primer->siguiente;
        destruirNodoCola(eliminado);
        if(!cola->primer)
            cola->ultimo=NULL;
    }
}




