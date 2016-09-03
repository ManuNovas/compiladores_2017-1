#include<stdio.h>
#include<stdlib.h>
void main(int argc, char *argv[ ]){
	//Matriz que define al automata de la expresion regular
	int automata[11][14]={
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
}
