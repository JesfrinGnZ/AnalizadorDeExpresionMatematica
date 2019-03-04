#include "cola.h"
#include "pila.h"
#include "lecturas.h"
#include <stdio.h>
#include <stdlib.h>


char seDebeSeguirAnalizando='1';
char *numeroActual,*copiaDeNumero;
int tamanoDeNumero=0;
int hayNumeroPorGuardar=0;
int cantidadDePuntosDecimales=0;
char caracteresDeEspacio[] ={'\n','\t','\r',' '};
char digitos[]= {'0','1','2','3','4','5','6','7','8','9','.'};
char simbolos[]={'+','-','*','/','(',')'};
Cola* cola;
Pila* pila;
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
        escrituraDeCaracteres("Error.txt","Formato de numero incorrecto:\n",'@',numeroActual,numeroDeFila);
        seDebeSeguirAnalizando='0';
    }else{
        double numeroConvertido = atof(numeroActual);
        encolar(cola,crearElemento('@',numeroConvertido));
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
}


void lecturaDeCaracteres(){
    //valor=2;
	FILE *archivo;
	char caracter;
	char caracterAnterior;
	archivo = fopen("prueba.txt","r");

	if (archivo == NULL){
            printf("\nError de apertura del archivo. \n\n");
    }else{
        printf("\nEl contenido del archivo de prueba es \n\n");
        crearPilaY_Cola();
        while((caracter = fgetc(archivo)) != EOF && seDebeSeguirAnalizando=='1'){
		//printf("%c",caracter);
            analizarExpresion(caracter);
            printf("SeDebeSeguirAnalizando:%c\n",seDebeSeguirAnalizando);
        }
    }
        while(cimaDePila(pila)!=NULL && seDebeSeguirAnalizando=='1'){//Pasandp elementos de la pila a EPOS
            if(cimaDePila(pila)->operador=='('){
                printf("Error no se ha cerrado el parentesis\n");
            }
            encolar(cola,cimaDePila(pila));
            desapilar(pila);
        }

        printf("Elementos en cola:");
        while(consultarCola(cola)!=NULL){
            if(consultarCola(cola)->operador=='@'){
                printf("%f ",consultarCola(cola)->operando);
            }else{
                printf("%c ",consultarCola(cola)->operador);
            }
            eliminarDeCola(cola);
        }
        printf("\n");
        //liberarMemoria();
        fclose(archivo);

}

void escrituraDeCaracteres(char* nombreDeArchivo,char* mensaje,char caracterDeError,char* numeroDeError,int fila){
    FILE* flujo = fopen(nombreDeArchivo,"w");
    if(flujo==NULL){
        perror("Error en la creacion de archivo\n\n");
    }else{
        fprintf(flujo,"%s",mensaje);
        if(caracterDeError=='@'){
            fprintf(flujo,"%s Fila:%d\n\n",numeroDeError,fila);
        }else{
            fprintf(flujo,"%c Fila %d\n\n",caracterDeError,fila);
        }
        while(consultarCola(cola)!=NULL){
            if(consultarCola(cola)->operador=='@'){
                fprintf(flujo,"%f\n",consultarCola(cola)->operando);
            }else{
                fprintf(flujo,"%c\n",consultarCola(cola)->operador);
            }
            eliminarDeCola(cola);
        }
        fflush(flujo);
        fclose(flujo);
    }
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
                        }else{
                            if(contador==0){
                                printf("Error en parentesis:\n");
                                seDebeSeguirAnalizando='0';
                            }else if(cimaDePila(pila)->operador=='('){
                            desapilar(pila);
                            }else{
                                printf("Error en parentesis:\n");
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




/*
void lecturaDeCaracteres(){
    float *arrayFl1, *mem;
    int elementos, q;

    elementos = 6;
    arrayFl1 = malloc(elementos*sizeof(float));
    arrayFl1[0] = 0.172;
    arrayFl1[1] = -0.0717;
    arrayFl1[2] = 0.2285;
    arrayFl1[3] = 0.176;
    arrayFl1[4] = -0.068;
    arrayFl1[5] = 0.228;
    for(int i=0;i<elementos;i++){
        printf("%f\n",arrayFl1[i]);
    }

    elementos++;
    mem = realloc(arrayFl1, sizeof(float)*elementos);
    arrayFl1 = mem;
    arrayFl1[elementos-1] = 1.2345;

    printf("Segunda vuelta\n");
    for(int i=0;i<elementos;i++){
        printf("%f\n",arrayFl1[i]);
    }
    free(arrayFl1);
    free(mem);
    printf("Tercera vuelta, cambian valores???----> se ha liverado la memoria\n");
    for(int i=0;i<elementos;i++){
        printf("%f\n",arrayFl1[i]);
    }
}
*/



