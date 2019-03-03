#ifndef cola_h
#define cola_h

#include <stdio.h>
#include "elementoDeOperacion.h"

typedef struct NodoCola{
    ElementoDeOperacion *elementoDeOperacion;
    struct NodoCola* siguiente;

}NodoCola;

typedef struct Cola{
    NodoCola* primer;//Frente
    NodoCola* ultimo;//Final
}Cola;

NodoCola* crearNodoCola(ElementoDeOperacion* elementoDeOperacion);
void destruirNodoCola(NodoCola* nodoCola);
Cola* crearCola();
void destruirCola(Cola* cola);
void encolar(Cola* cola,ElementoDeOperacion* elementoDeOperacion);
ElementoDeOperacion* consultarCola(Cola* cola);
ElementoDeOperacion* consultarFinalDeCola(Cola*  cola);
void eliminarDeCola(Cola* cola);



#endif // cola_h

