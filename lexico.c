#include<stdio.h>
#include<stdlib.h>

int convertidor(char c){
	if((c>='a' && c<='z') || (c>='A' && c<='Z')){
		return 0;
	}else if(c>='0' && c<='9'){
		return 1;
	}else if(c=='.'){
		return 2;
	}else if(c=='+'){
		return 3;
	}else if(c=='-'){
		return 4;
	}else if(c=='*'){
		return 5;
	}else if(c=='/'){
		return 6;
	}else if(c=='='){
		return 7;
	}else if(c==' '){
		return 8;
	}else if(c=='>'){
		return 9;
	}else if(c=='<'){
		return 10;
	}else{
		//default
		return 11;
	}
}

void main(int argc, char *argv[ ]){
	//Matriz que define al automata de la expresion regular
	int automata[14][11]={
		 1,  2, -1,  7,  7,  7,  9,  8, 13,  5,  5,
		 1,  1, -1,  0,  0,  0,  0,  0,  0,  0,  0,
		-1,  2,  3,  0,  0,  0,  0, -1,  0,  0,  0,
		-1,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1,  4, -1,  0,  0,  0,  0, -1,  0,  0,  0,
		 0,  0, -1, -1, -1, -1, -1,  6,  0, -1, -1,
		 0,  0, -1, -1, -1, -1, -1, -1,  0, -1, -1,
		 0,  0, -1, -1, -1, -1, -1, -1,  0, -1, -1,
		 0,  0, -1, -1, -1, -1, -1, -1,  0, -1, -1,
		 0,  0, -1, -1, -1, 10, -1, -1,  0, -1, -1,
		10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 12, 10, 10, 10, 10,
		 0,  0, -1, -1, -1, -1, -1, -1,  0, -1, -1,
		 0,  0,  0,  0,  0,  0,  0,  0, 13,  0,  0};

	//Arreglo que contiene los estados de aceptacion
	int aceptacion[14]={0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1};
	
	//Variables para el desarrollo del programa
	char caracter;
	int selector, estado=0;
	FILE *entrada;

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
	do{
		//obteniendo siguiente caracter
		caracter=fgetc(entrada);
		if(caracter!='\n' && caracter!=EOF){
			selector=convertidor(caracter);
			estado=automata[estado][selector];
			printf("Estoy en el estado: %i\n", estado);
			if(estado==-1){
				printf("error :(");
				exit(1);
			}
		}
	}while(caracter!=EOF);
	if(aceptacion[estado]){
		printf("Cadena aceptada\n");
	}
}
