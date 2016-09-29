/*
 *Authors:
 *	Martínez Rojas Jorge Antonio
 *	Novas Santamaría José Manuel
 **/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct SYMBOL{
	char id[30];
	char clase[30];
};

//arreglo de 50 tokens ASIGNAR MEMORIA DINAMICA DESPUES
struct SYMBOL simbolos[50];
//Contador para el arreglo de tokens
int count=0, car=0, linea=1;

int convertidor(char c){
	if((c>='a' && c<='z') || (c>='A' && c<='Z')){ //letra
		return 0;
	}else if(c>='0' && c<='9'){ //digito
		return 1;
	}else if(c=='.'){ //punto
		return 2;
	}else if(c=='+'){ //suma
		return 3;
	}else if(c=='-'){ //resta
		return 4;
	}else if(c=='*'){ //multiplicacion
		return 5;
	}else if(c=='/'){ //division
		return 6;
	}else if(c=='='){ //igualdad
		return 7;
	}else if(c==' ' || c=='\n'){ //espacio
		return 8;
	}else if(c=='>'){ //mayor que
		return 9;
	}else if(c=='<'){ //menor que
		return 10;
	}else{ //default
		return 11;
	}
}

int agregaSimbolo(char *buffer, char *class){
	int i;
	for(i=0; i<count; i++){
		if(!strcmp(buffer, simbolos[i].id)){
			return 0;
		}
	} //For que elimina tokens repetidos
	strcpy(simbolos[count].id, buffer);
	strcpy(simbolos[count].clase, class);
	count++;
	return 1;
}

void suitch(int estado, char buffer[ ]){
	switch(estado){
		case 1:
			printf("<id , %s>\n",buffer);
			agregaSimbolo(buffer, "id");
			break;
		case 2:
			printf("<entero , %s>\n",buffer);
			agregaSimbolo(buffer, "entero");
			break;
		case 4:
			printf("<real , %s>\n",buffer);
			agregaSimbolo(buffer, "real");
			break;
		case 5:
			printf("<opRel , %s>\n",buffer);
			agregaSimbolo(buffer, "opRel");
			break;
		case 6:
			printf("<opRel , %s>\n",buffer);
			agregaSimbolo(buffer, "opRel");
			break;
		case 7:
			printf("<opArit , %s>\n",buffer);
			agregaSimbolo(buffer, "opArit");
			break;
		case 9:
			printf("<opArit , %s>\n",buffer);
			agregaSimbolo(buffer, "opArit");
			break;
		case 8:
			printf("<opAsig , %s>\n",buffer);
			agregaSimbolo(buffer, "opAsig");
			break;
		case 12:
			printf("<coment , %s>\n",buffer);
			agregaSimbolo(buffer, "coment");
			break;
		case 13: 
			//printf("Salto de linea\n");
			linea++;
			car=0;
			break;
		default:
			printf("--------\n");
			break;
	}
}
int main(int argc, char *argv[ ]){
	//Matriz que define al automata de la expresion regular
	int automata[14][11]={
		 1,  2, -1,  7,  7,  7,  9,  8, 13,  5,  5, // 0
		 1,  1, -1,  0,  0,  0,  0,  0,  0,  0,  0, // 1
		-1,  2,  3,  0,  0,  0,  0, -1,  0,  0,  0, // 2
		-1,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 3
		-1,  4, -1,  0,  0,  0,  0, -1,  0,  0,  0, // 4
		 0,  0, -1, -1, -1, -1, -1,  6,  0, -1, -1, // 5
		 0,  0, -1, -1, -1, -1, -1, -1,  0, -1, -1, // 6
		 0,  0, -1, -1, -1, -1, -1, -1,  0, -1, -1, // 7
		 0,  0, -1, -1, -1, -1, -1, -1,  0, -1, -1, // 8
		 0,  0, -1, -1, -1, 10, -1, -1,  0, -1, -1, // 9
		10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, // 10
		10, 10, 10, 10, 10, 10, 12, 10, 10, 10, 10, // 11
		 0,  0, -1, -1, -1, -1, -1, -1,  0, -1, -1, // 12
		 0,  0,  0,  0,  0,  0,  0,  0, 13,  0,  0};  //0-13
//   letra digito .  +   -   *   /   =  esp  >   <

	//Arreglo que contiene los estados de aceptacion
	int aceptacion[ ]= {0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,  0,  1,  1};
	//estado aceptacion[]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	
	//Variables para el desarrollo del programa
	char caracter;
	char buffer[20];
	char cadtemp[2];
	int selector, estado=0, estadoMatriz=0, j;
	FILE *entrada, *salida;

	//Verificando archivo de entrada
	if(argc!=2){
		printf("Falta archivo de entrada :(\n");
		exit(1);
	}
	entrada=fopen(argv[1], "r");
	if(entrada==NULL){
		printf("No se encuentra %s en el directorio actual :(\n", argv[1]);
		exit(1);
	}
	//iniciando con el proceso de análisis léxico
	buffer[0]='\0';
	//lee primer caracter
	caracter=fgetc(entrada);
	car++;
	do{
		selector=convertidor(caracter); // devuelve columna
		estado=estadoMatriz;
		estadoMatriz=automata[estadoMatriz][selector];
		//printf("Estoy en el estado de la matriz: %i\n", estadoMatriz);
		if(estadoMatriz == -1){
			printf("error :( en el caracter %i de la línea %i\n", car-1, linea);
			fclose(entrada);
			exit(1);
		}else if(estadoMatriz != 0){ //si no es estado de aceptación...
			cadtemp[0]=caracter;
			cadtemp[1]='\0';
			strcat(buffer,cadtemp);
			caracter=fgetc(entrada);//lee caracter
			car++;
			if(caracter==EOF){
				suitch(estado, buffer);
			}
		}else if(estadoMatriz == 0){
			suitch(estado,buffer);
			//añade el token al arreglo
			strcpy(buffer,"");
		}
	}while(caracter!=EOF);

	//Grabando tokens en archivo
	salida=fopen("simbolos.txt", "w");
	for(j=0; j<count; j++){
		char sm[50]="";
		strcat(sm, simbolos[j].clase);
		strcat(sm, ",");
		strcat(sm, simbolos[j].id);
		strcat(sm, "\n");
		fputs(sm, salida);
	}
	printf("\n\nArchivo %s aceptado, tabla de simbolos en el archivo 'simbolos.txt'\n", argv[1]);
	fclose(salida);
	fclose(entrada);
	return 0;
}