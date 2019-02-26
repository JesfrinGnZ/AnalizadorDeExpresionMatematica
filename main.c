#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "lecturas.h"

int main()
{
    printf("Hello world!\n");
    ElementoDeOperacion nuevoElemento={10,'@'};
    if(nuevoElemento.operador=='@'){
        printf("Pues solo se toma el numero\n");
    }
    printf("Valor numericoDeNuevoElemento:%d, caracter %c\n",nuevoElemento.operando,nuevoElemento.operador);
    lecturaDeCaracteres();
    return 0;
}
