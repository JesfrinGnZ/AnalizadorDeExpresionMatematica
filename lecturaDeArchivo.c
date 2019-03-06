//
//lecturaDeArchivo.c
//Jesfrin Gonzalez 05/02/19
//201630978 Estrucutura de datos
//


#include "cola.h"
#include "pila.h"
#include "lista.h"
#include "lecturas.h"
#include <stdio.h>
#include <stdlib.h>


char seDebeSeguirAnalizando='1';
char *numeroActual,*copiaDeNumero;
int tamanoDeNumero=0;
int hayNumeroPorGuardar=0;
int cantidadDePuntosDecimales=0;
int cantidadDeNumeros=0;
char caracteresDeEspacio[] ={'\n','\t','\r',' '};
char digitos[]= {'0','1','2','3','4','5','6','7','8','9','.'};
char simbolos[]={'+','-','*','/','(',')'};
Cola* cola;
Pila* pila;
Pila* pilaEpos;
Pila* pilaFinal;
Lista* listaDeNumeros;
Lista* listaDeNumerosMin;
int numeroDeFila=1;

char buscarSiCaracterEsUnEspacio(char caracter){
    for(int i=0;i<4;i++){
        if(caracter==caracteresDeEspacio[i]){
            return '1';
        }
    }
    return '0';
}

char buscarSiCaracterEsUnDigito(char caracter){
    for(int i=0;i<11;i++){
        if(caracter==digitos[i]){
            return '1';
        }
    }
    return '0';
}

char buscarSiCaracterEsUnSimbolo(char caracter){
    for(int i=0;i<6;i++){
        if(caracter==simbolos[i]){
            return '1';
        }
    }
    return '0';
}

int calcularPrioridad(char operador){
    if(operador=='('){
        return -1;
    }else if(operador=='*' || operador=='/'){
        return 1;
    }
    return 0;
}


void liberarMemoria(){
    free(numeroActual);//Se libera el espacio de memoria que se tenia usado actualmente
    free(copiaDeNumero);
}

void guardarPrimerCaracterDeNumero(char caracter){
    hayNumeroPorGuardar=1;
    tamanoDeNumero++;
    numeroActual = malloc(tamanoDeNumero*sizeof(char));//Se crea el espacio para solo un caracter
    numeroActual[0]=caracter;
}

void guardarEnesimoCaracterDeNumero(char caracter){
    tamanoDeNumero++;
    copiaDeNumero = realloc(numeroActual, sizeof(char)*tamanoDeNumero);//Se redimenciona el tamano para el enesimo caracter
    numeroActual = copiaDeNumero;
    numeroActual[tamanoDeNumero-1] =caracter;
}

void convertirNumeroA_Decimal(){
    if(cantidadDePuntosDecimales>1){
        //Terminar proceso del programa, el numero es erroneo el cual seria numero actual
        printf("ERROR: El numero leido:%s tiene un formato incorrecto.\n",numeroActual);
        escrituraDeCaracteres("Error.txt","Formato de numero incorrecto:",'@',numeroActual,numeroDeFila,0);
        seDebeSeguirAnalizando='0';
    }else{
        double numeroConvertido = atof(numeroActual);
        encolar(cola,crearElemento('@',numeroConvertido));
        //Max heap
        anadirALista(listaDeNumeros,numeroConvertido,cantidadDeNumeros);
        //Min heap
        anadirALista(listaDeNumerosMin,numeroConvertido,cantidadDeNumeros);

        NodoLista* nodo= buscarNodoEnPosicion(listaDeNumeros,cantidadDeNumeros);
        NodoLista* min = buscarNodoEnPosicion(listaDeNumerosMin,cantidadDeNumeros);
        realizarMaxHeap(nodo);
        realizarMinHeap(min);
        cantidadDeNumeros++;
        //printf("Se ha transformado el numero------->%f\n",numeroConvertido);
        //printf("Final de la cola actual:::::::::::::::::::::::::::::::::%f\n",consultarFinalDeCola(cola)->operando);
    }

    //liberarMemoria();
    tamanoDeNumero=0;
    hayNumeroPorGuardar=0;
    cantidadDePuntosDecimales=0;
}

void crearPilaY_Cola(){
    pila = crearPila();
    cola = crearCola();
    listaDeNumeros = crearLista();
    listaDeNumerosMin= crearLista();
}


ElementoDeOperacion* crearElemento(char operador,double operando){
    ElementoDeOperacion * elementoDeOperacion = (ElementoDeOperacion*)malloc(sizeof(ElementoDeOperacion));
    elementoDeOperacion->operador=operador;
    elementoDeOperacion->operando=operando;
    elementoDeOperacion->numeroDeFila=numeroDeFila;
    return elementoDeOperacion;
}

void analizarExpresion(char caracter){
     if(buscarSiCaracterEsUnEspacio(caracter)=='0'){//Caracter no es un espacio
                if(buscarSiCaracterEsUnSimbolo(caracter)=='1'){//Caracter es un simbolo
                    if(hayNumeroPorGuardar==1){//Convertir el numero, colocarlo en la pila, volver valores a su estado inicial
                        convertirNumeroA_Decimal();
                    }
                    if(seDebeSeguirAnalizando=='1'){
                        if(caracter==')'){
                        int contador=0;
                        while(cimaDePila(pila)!=NULL && cimaDePila(pila)->operador!='('){
                            encolar(cola,cimaDePila(pila));
                            desapilar(pila);
                            contador++;
                        }
                        if(cimaDePila(pila)==NULL){
                            printf("Error en parentesis:\n");
                            escrituraDeCaracteres("Error.txt","No se ha abierto el parentesis:",')',0,numeroDeFila,0);
                            escribirPilaFinal("",0,1,0,0);
                            seDebeSeguirAnalizando='0';
                        }else{
                             if(cimaDePila(pila)->operador=='('){
                            desapilar(pila);
                            }else{
                                printf("Error en parentesis:\n");
                                escrituraDeCaracteres("Error.txt","No se ha abierto el parentesis:",')',0,numeroDeFila,0);
                                escribirPilaFinal("",0,1,0,0);
                                seDebeSeguirAnalizando='0';
                            }
                        }
                    }else if(caracter=='('){
                        apilar(pila,crearElemento(caracter,0));
                    }else{
                        while(cimaDePila(pila)!=NULL && calcularPrioridad(caracter)!=-1 &&(calcularPrioridad(caracter)<=calcularPrioridad(pila->cima->elementoDeOperacion->operador))){
                            //ElementoDeOperacion* cima = cimaDePila(pila);
                            encolar(cola,cimaDePila(pila));
                            desapilar(pila);
                        }
                        apilar(pila,crearElemento(caracter,0));
                    }
                    }
                    //printf("Tope de pila::::::::::::::::::::::%c\n",cimaDePila(pila)->operador);
                    //printf("Es un simbolo:%c\n",caracter);//Guardar el simbolo
                }else{//Caracter es un digito o un punto
                    if(caracter=='.'){//Para posterior analisis si el numero tiene solo un punto
                        cantidadDePuntosDecimales++;
                    }
                    if(tamanoDeNumero==0){
                        guardarPrimerCaracterDeNumero(caracter);
                    }else{
                        guardarEnesimoCaracterDeNumero(caracter);
                    }
                }
            }else{//Caracter es un espacio
                if(caracter=='\n'){
                    numeroDeFila++;
                }
                if(hayNumeroPorGuardar==1){//Convertir el numero, colocarlo en la pila, volver valores a su estado inicial
                    convertirNumeroA_Decimal();
                }
            }
}

double evaluarEpos(){
    pilaEpos=crearPila();
    pilaFinal=crearPila();
    while(consultarCola(cola)!=NULL){
        if(consultarCola(cola)->operador=='@'){
            apilar(pilaEpos,consultarCola(cola));//Se apilan los numeros
            apilar(pilaFinal,consultarCola(cola));//Apilara en pila final
            eliminarDeCola(cola);
        }else{
        ElementoDeOperacion* opearadorEnCola = consultarCola(cola);
        eliminarDeCola(cola);
        ElementoDeOperacion* op2 = cimaDePila(pilaEpos);
        desapilar(pilaEpos);
        ElementoDeOperacion* op1 = cimaDePila(pilaEpos);
        desapilar(pilaEpos);
        if(opearadorEnCola==NULL){//operador->operador=='@'
            printf("Error falta de signo en fila %d\n",cimaDePila(pilaFinal)->numeroDeFila);
            escribirPilaFinalEnError("Error falta de operandos",cimaDePila(pilaFinal)->numeroDeFila);
            seDebeSeguirAnalizando=='0';
            return 0;
        }else if(op2==NULL || op1==NULL){
            printf("Error falta de operandos en fila %d\n",opearadorEnCola->numeroDeFila);            escrituraDeCaracteres("Error.txt","Error falta de signo",'.',0,cimaDePila(pilaFinal)->numeroDeFila,0);
            escribirPilaFinalEnError("Error falta de operandos",cimaDePila(pilaFinal)->numeroDeFila);
            //escrituraDeCaracteres("Error.txt","Error falta de operandos",'.','0',numeroDeFila,0);
            seDebeSeguirAnalizando='0';
            return 0;
        }else{
            apilar(pilaFinal,opearadorEnCola);//Apilar signo en pila final
            double resultado=calcularOperacion(op1->operando,op2->operando,opearadorEnCola->operador);
            //printf("El resultado es:%f\n",resultado);
            if(consultarCola(cola)==NULL){
                //printf("El resultado es:%f\n",resultado);
                return resultado;
            }else{
                apilar(pilaEpos,crearElemento('@',resultado));
            }
        }
        }
    }
    return 0;
    }


double calcularOperacion(double op1,double op2,char operacion){
    switch(operacion){
    case '*':
        return op1*op2;
        break;
    case '/':
        return op1/op2;
        break;
    case '+':
        return op1+op2;
        break;
    case '-':
        return op1-op2;
        break;
    }
    return 0;
}


void escribirPilaFinalEnError(char* mensaje,int numeroDeFila){
    FILE* flujo = fopen("Error.txt","w");
    if(flujo == NULL){
        perror("Error en la creacion de archivo\n\n");
    }else{
        fprintf(flujo,mensaje);
        fprintf(flujo,"en fila %d \n PILA...\n",numeroDeFila);
        while(cimaDePila(pilaFinal)!=NULL){
            if(cimaDePila(pilaFinal)->operador=='@'){
                fprintf(flujo,"%.3f\n",cimaDePila(pilaFinal)->operando);
            }else{
                fprintf(flujo,"%c\n",cimaDePila(pilaFinal)->operador);
            }
            desapilar(pilaFinal);
        }
    }

}

void escribirPilaFinal(char* mensaje,double resultado,int seDebeBorrar,double numeroMayor,double numeroMenor){
    FILE* flujo = fopen("Resultado.txt","w");
    if(flujo==NULL){
        perror("Error en la creacion de archivo\n\n");
    }else if(seDebeBorrar==1){
        fprintf(flujo,"Ha existido un error, revise el archivo Error.txt para mas informacion");
    }else{
        fprintf(flujo,"Numero mayor:%.3f, Numero menor:%.3f\n",numeroMayor,numeroMenor);
        fprintf(flujo,"Resultado %.3f\n\nPILA...\n\n",resultado);

        while(cimaDePila(pilaFinal)!=NULL){
            if(cimaDePila(pilaFinal)->operador=='@'){
                fprintf(flujo,"%.3f\n",cimaDePila(pilaFinal)->operando);
            }else{
                fprintf(flujo,"%c\n",cimaDePila(pilaFinal)->operador);
            }
            desapilar(pilaFinal);
        }
    }
}

void escrituraDeCaracteres(char* nombreDeArchivo,char* mensaje,char caracterDeError,char* numeroDeError,int fila,int seDebeBorrar){
    FILE* flujo = fopen(nombreDeArchivo,"w");
    if(flujo==NULL){
        perror("Error en la creacion de archivo\n\n");
    }else if(seDebeBorrar==1){
        fprintf(flujo,"Operacion realizada con exito revisa el archivo Resultado.txt\n");
    }else{
        fprintf(flujo,"%s",mensaje);
        if(caracterDeError=='@'){
            fprintf(flujo,"%s Fila:%d\n\n",numeroDeError,fila);
        }else{
            fprintf(flujo,"%c Fila %d\n\n",caracterDeError,fila);
        }
        while(consultarCola(cola)!=NULL){
            if(consultarCola(cola)->operador=='@'){
                fprintf(flujo,"%.3f\n",consultarCola(cola)->operando);
            }else{
                fprintf(flujo,"%c\n",consultarCola(cola)->operador);
            }
            eliminarDeCola(cola);
        }
        fflush(flujo);
        fclose(flujo);
    }
}

void lecturaDeCaracteres(){
    //valor=2;
	FILE *archivo;
	char caracter;
	archivo = fopen("prueba.txt","r");

	if (archivo == NULL){
            printf("\nError de apertura del archivo. \n\n");
    }else{
        crearPilaY_Cola();
        while((caracter = fgetc(archivo)) != EOF && seDebeSeguirAnalizando=='1'){
		//printf("%c",caracter);
            analizarExpresion(caracter);
        }
    }
        while(cimaDePila(pila)!=NULL && seDebeSeguirAnalizando=='1'){//Pasandp elementos de la pila a EPOS
            if(cimaDePila(pila)->operador=='('){
                printf("Error no se ha cerrado el parentesis\n");
                escrituraDeCaracteres("Error.txt","No se ha cerrado el parentesis:",'(',0,numeroDeFila,0);
                escribirPilaFinal("",0,1,0,0);
                seDebeSeguirAnalizando='0';
            }
            encolar(cola,cimaDePila(pila));
            desapilar(pila);
        }


        if(seDebeSeguirAnalizando=='1'){
            printf("EPOS FINALIZADO CON EXITO\n");
            printf("Evaluando...EPOS\n");
            double resultado=evaluarEpos();
            if(seDebeSeguirAnalizando!='0'){
                if(cimaDePila(pilaEpos)!=NULL){//Error ya que la pila no se ha quedado vacia
                    int numDeFila =cimaDePila(pilaEpos)->numeroDeFila-1;
                    printf("EXISTIO UN ERROR...numeros sin operacion en fila:%d\n",numDeFila);
                    escribirPilaFinal("",0,1,0,0);
                    escribirPilaFinalEnError("Error numeros sin opearacion ",numDeFila);
                }else{
                    printf("Analisis concluido con exito.El resultado es:%.2f",resultado);
                    escrituraDeCaracteres("Error.txt","hh",'@',"ff",numeroDeFila,1);
                    escribirPilaFinal("El resultado es:",resultado,0,listaDeNumeros->cabeza->numero,listaDeNumerosMin->cabeza->numero);
                    printf("\nMayor:%.3f\n",listaDeNumeros->cabeza->numero);
                    printf("Menor:%.3f\n",listaDeNumerosMin->cabeza->numero);
                }
            }
        }
        fclose(archivo);

}


void realizarMaxHeap(NodoLista* nodoAnalizado){
    int posicionDePadre = cantidadDeNumeros-1;
    while(nodoAnalizado->posicion!=0 && nodoAnalizado->numero>buscarNodoEnPosicion(listaDeNumeros,posicionDePadre)->numero){
        double numeroNodoPadre=buscarNodoEnPosicion(listaDeNumeros,posicionDePadre)->numero;
        double numeroNodoHijo=nodoAnalizado->numero;
        nodoAnalizado->numero=numeroNodoPadre;
        buscarNodoEnPosicion(listaDeNumeros,posicionDePadre)->numero=numeroNodoHijo;
        nodoAnalizado=buscarNodoEnPosicion(listaDeNumeros,posicionDePadre);
        posicionDePadre--;
    }
}

void realizarMinHeap(NodoLista* nodoAnalizado){
    int posicionDePadre = cantidadDeNumeros-1;
    while(nodoAnalizado->posicion!=0 && nodoAnalizado->numero<buscarNodoEnPosicion(listaDeNumerosMin,posicionDePadre)->numero){
        double numeroNodoPadre=buscarNodoEnPosicion(listaDeNumerosMin,posicionDePadre)->numero;
        double numeroNodoHijo=nodoAnalizado->numero;
        nodoAnalizado->numero=numeroNodoPadre;
        buscarNodoEnPosicion(listaDeNumerosMin,posicionDePadre)->numero=numeroNodoHijo;
        nodoAnalizado=buscarNodoEnPosicion(listaDeNumerosMin,posicionDePadre);
        posicionDePadre--;
    }
}


