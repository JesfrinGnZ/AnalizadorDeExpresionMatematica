#include<stdio.h>
#include<stdlib.h>

char *numeroActual,*copiaDeNumero;
int tamanoDeNumero=0;
char hayNumeroPorGuardar=0;
char *caracteresDeEspacio ={'\n','\t','\r',' '};
char *digitos= {'0','1','2','3','4','5','6','7','8','9','.'};
char *simbolos={'+','-','*','/'};


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
    for(int i=0;i<4;i++){
        if(caracter==simbolos[i]){
            return '1';
        }
    }
    return '0';
}


void liberarMemoria(){
    free(numeroActual);//Se libera el espacio de memoria que se tenia usado actualmente
    free(copiaDeNumero);
}

void guardarPrimerCaracterDeNumero(char caracter){
    tamanoDeNumero++;
    free(numeroActual);//Se libera el espacio de memoria que se tenia usado actualmente
    free(copiaDeNumero);
    numeroActual = malloc(tamanoDeNumero*sizeof(char));//Se crea el espacio para solo un caracter
    numeroActual[0]=caracter;
}

void guardarEnesimoCaracterDeNumero(char caracter){
    tamanoDeNumero++;
    copiaDeNumero = realloc(numeroActual, sizeof(char)*tamanoDeNumero);//Se redimenciona el tamano para el enesimo caracter
    numeroActual = copiaDeNumero;
    numeroActual[tamanoDeNumero-1] =caracter;
    printf("Concatenacion:");
    for(int i=0;i<tamanoDeNumero;i++){
        printf("%c",numeroActual[i]);
    }
    printf("\n");
}

void convertirNumeroA_Decimal(){
    printf("Se ha transformado el numero------->%f\n",atof(numeroActual));
}

void lecturaDeCaracteres(){
    //valor=2;
	FILE *archivo;
	char caracter;
	char caracterAnterior;

	archivo = fopen("prueba.txt","r");

	if (archivo == NULL)
        {
            printf("\nError de apertura del archivo. \n\n");
        }
        else
        {
            printf("\nEl contenido del archivo de prueba es \n\n");
            while((caracter = fgetc(archivo)) != EOF)
	    {
		//printf("%c",caracter);
		if(caracter!=' ' && caracter!='\t'&& caracter!='\n'&& caracter!='\r'){
            caracterAnterior=caracter;
		}
		printf("Caracter ANTERIOR::::::::::%c\n",caracterAnterior);
		if(caracter!= '+' && caracter!= '-' && caracter!= '*' && caracter!= '/' && caracter!= '(' && caracter!= ')'){
                if(tamanoDeNumero==0){
                    hayNumeroPorGuardar=1;
                    guardarPrimerCaracterDeNumero(caracter);
                }else{
                    guardarEnesimoCaracterDeNumero(caracter);
                }

		}else{
		    if(hayNumeroPorGuardar==1){
                convertirNumeroA_Decimal();
                tamanoDeNumero=0;
                hayNumeroPorGuardar=0;
		    }//Si o si se concatena el signo

		}
	    }
        }
        if(caracterAnterior== '0' || caracterAnterior== '1' || caracterAnterior== '2' || caracterAnterior== '3' || caracterAnterior== '4' || caracterAnterior== '5'||
           caracterAnterior== '6' || caracterAnterior== '7' || caracterAnterior== '8' || caracterAnterior== '9'){
           convertirNumeroA_Decimal();
        }
        liberarMemoria();
        fclose(archivo);

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



