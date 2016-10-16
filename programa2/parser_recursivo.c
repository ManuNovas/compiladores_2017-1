#include <stdio.h>
#include "tokens.h"

int token;

void error( ){
  printf("Error :(");
  exit(0);
}

void eat(int tok){
  if(tok==token)
    token=yylex( );
  else
    error( );
}

void D( ){
  while(token==PALABRA_RESERVADA){
    Y( );
    L( );
    eat(PUNTO_COMA);
    D_prima( );
  }
}

void G( ){
  while(token==FUNCION || token==EPSILON){
    if(token==FUNCION){
      eat(FUNCION);
      Y( );
      eat(ID);
      eat(PARENTESIS_ABRE);
      A( );
      eat(PARENTESIS_CIERRA);
      eat(LLAVE_ABRE);
      B( );
      eat(LLAVE_CIERRA);
      G( );
    }else{
      eat(EPSILON);
    }
  }
}

void P( ){
  while(token==PALABRA_RESERVADA){
    D( );
    G( );
  }
}

int main(int argc, char **argv){
  if(argc<=2){
    printf("Falta archivo de entrada :(");
    return 0;
  }
  yyin=fopen(argv[1], "r")
  if(yyin==NULL){
    printf("Error al abrir el archivo %s :(", argv[1]);
    fclose(yyin);
    return 0;
  }
  token=yylex;
  P( );
  return 1;
}