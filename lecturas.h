//
//lecturas.h
//Jesfrin Gonzalez 05/02/19
//201630978 Estrucutura de datos
//

#ifndef lecturas_h
#define lecturas_h

char buscarSiCaracterEsUnEspacio(char caracter);
char buscarSiCaracterEsUnDigito(char caracter);
char buscarSiCaracterEsUnSimbolo(char caracter);
void liberarMemoria();
int calcularPrioridad(char operador);
void guardarPrimerCaracterDeNumero(char caracter);
void guardarEnesimoCaracterDeNumero(char caracter);
void convertirNumeroA_Decimal();
void crearPilaY_Cola();
ElementoDeOperacion* crearElemento(char operador,double operando);
void analizarExpresion(char caracter);
double evaluarEpos();
double calcularOperacion(double op1,double op2,char operacion);
void lecturaDeCaracteres();
void escribirPilaFinalEnError(char* mensaje,int numeroDeFila);
void escribirPilaFinal(char* mensaje,double resultado,int seDebeBorrar,double numeroMayor,double numeroMenor);
void escrituraDeCaracteres(char* nombreDeArchivo,char* mensaje,char caracterDeError,char* numeroDeError,int fila,int seDebeBorrar);
void realizarMinHeap(NodoLista* nodoAnalizado);
#endif // lecturas_h
