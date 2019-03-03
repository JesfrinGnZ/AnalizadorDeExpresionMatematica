#ifndef lecturas_h
#define lecturas_h

char buscarSiCaracterEsUnEspacio(char caracter);
char buscarSiCaracterEsUnDigito(char caracter);
char buscarSiCaracterEsUnSimbolo(char caracter);
void liberarMemoria();
void guardarPrimerCaracterDeNumero(char caracter);
void guardarEnesimoCaracterDeNumero(char caracter);
void convertirNumeroA_Decimal();
void crearPilaY_Cola();
ElementoDeOperacion* crearElemento(char operador,double operando);
void lecturaDeCaracteres();
void analizarExpresion(char caracter);
#endif // lecturas_h
