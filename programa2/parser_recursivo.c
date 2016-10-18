/*
 *Authors:
 *  Martínez Rojas Jorge Antonio
 *  Novas Santamaría José Manuel
 */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

void error( );
void eat( );
void P( );
void D( );
void D_prima( );
void Y( );
void L( );
void L_prima( );
void G( );
void A( );
void C( );
void C_prima( );
void B( );
void B_prima( );
void S( );
void E( );
void E_prima( );
void T( );
void T_prima( );
void F( );
void H( );
void H_prima( );
void J( );
void J_prima( );

int token;
FILE *yyin;

int main(int argc, char **argv){
  if(argc<2){
    printf("Falta archivo de entrada :(\n");
    return 0;
  }
  yyin=fopen(argv[1], "r");
  if(yyin==NULL){
    printf("Error al abrir el archivo %s :(\n", argv[1]);
    fclose(yyin);
    return 0;
  }
  token=yylex( );
  P( );
  printf("Archivo sin errores :)\n");
  fclose(yyin);
  return 1;
}

void error( ){
  //Modo pánico
  printf("Error :(\n");
  fclose(yyin);
  exit(0);
}

void eat(int token_esperado){
  if(token_esperado==token)
    token=yylex( );
  else
    error( );
}

void P( ){
  printf("P( )\n");
  D( );
  G( );
}

void D( ){
  printf("D( )\n");
  Y( );
  L( );
  eat(PUNTO_COMA);
  D_prima( );
}

void D_prima( ){
  printf("D'( )\n");
  switch(token){
    case PALABRA_RESERVADA:
      Y( );
      L( );
      eat(PUNTO_COMA);
      D_prima( );
      break;
    case FUNCION:
      break;
    default:
      error( );
      break;
  }
}

void Y( ){
  printf("Y( )\n");
  eat(PALABRA_RESERVADA);
}

void L( ){
  printf("L( )\n");
  eat(ID);
  L_prima( );
}

void L_prima( ){
  printf("L'( )\n");
  switch(token){
    case COMA:
      eat(COMA);
      eat(ID);
      L_prima( );
      break;
    case PUNTO_COMA:
      break;
    default:
      error( );
      break;
  }
}

void G( ){
  printf("G( )\n");
  switch(token){
    case FUNCION:
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
      break;
    case 0:
      break;
    default:
      error( );
      break;
  }
}

void A( ){
  printf("A( )\n");
  switch(token){
    case PALABRA_RESERVADA:
      C( );
      break;
    case PARENTESIS_CIERRA:
      break;
    default:
      error( );
      break;
  }
}

void C( ){
  printf("C( )\n");
  Y( );
  eat(ID);
  C_prima( );
}

void C_prima( ){
  printf("C'( )\n");
  switch(token){
    case COMA:
      eat(COMA);
      Y( );
      eat(ID);
      C_prima( );
      break;
    case PARENTESIS_CIERRA:
      break;
    default:
      error( );
      break;
  }
}

void B( ){
  printf("B( )\n");
  S( );
  B_prima( );
}

void B_prima( ){
  printf("B'( )\n");
  if(token==SI || token==MIENTRAS || token==ID || token==RETORNA || token==LLAVE_ABRE){
    S( );
    B_prima( );
  }else if(token==LLAVE_CIERRA){
    //Retorno a funcion
  }else
    error( );
}

void S( ){
  printf("S( )\n");
  switch(token){
    case SI:
      eat(SI);
      eat(PARENTESIS_ABRE);
      H( );
      eat(PARENTESIS_CIERRA);
      S( );
      eat(SINO);
      S( );
      break;
    case MIENTRAS:
      eat(MIENTRAS);
      eat(PARENTESIS_ABRE);
      H( );
      eat(PARENTESIS_CIERRA);
      S( );
      break;
    case ID:
      eat(ID);
      eat(IGUAL);
      E( );
      eat(PUNTO_COMA);
      break;
    case RETORNA:
      eat(RETORNA);
      E( );
      eat(PUNTO_COMA);
      break;
    case LLAVE_ABRE:
      eat(LLAVE_ABRE);
      S( );
      eat(LLAVE_CIERRA);
      break;
    default:
      error( );
      break;
  }
}

void E( ){
  printf("E( )\n");
  T( );
  E_prima( );
}

void E_prima( ){
  printf("E'( )\n");
  if(token==MAS){
    eat(MAS);
    T( );
    E_prima( );
  }else if(token==MENOS){
    eat(MENOS);
    T( );
    E_prima( );
  }else if(token==PUNTO_COMA || token==PARENTESIS_CIERRA || token==DISTINTO || token ==IDENTICO || token==IGUAL || token==MENOR || token==MAYOR || token==MAYOR_IGUAL || token==MENOR_IGUAL){
    //Retorno a funcion
  }else
    error( );
}

void T( ){
  printf("T( )\n");
  F( );
  T_prima( );
}

void T_prima( ){
  printf("T'( )\n");
  if(token==POR){
    eat(POR);
    F( );
    T_prima( );
  }else if(token==ENTRE){
    eat(ENTRE);
    F( );
    T_prima( );
  }else if(token==MAS || token==MENOS ||token==PUNTO_COMA || token==PARENTESIS_CIERRA || token==DISTINTO || token ==IDENTICO || token==IGUAL || token==MENOR || token==MAYOR || token==MAYOR_IGUAL || token==MENOR_IGUAL){
    //Retorno a funcion
  }else
    error( );
}

void F( ){
  printf("F( )\n");
  switch(token){
    case ID:
      eat(ID);
      break;
    case NUMERO:
      eat(NUMERO);
      break;
    case PARENTESIS_ABRE:
      eat(PARENTESIS_ABRE);
      E( );
      eat(PARENTESIS_CIERRA);
      break;
    default:
      error( );
      break;
  }
}

void H( ){
  printf("H( )\n");
  J( );
  H_prima( );
}

void H_prima( ){
  printf("H'( )\n");
  switch(token){
    case MENOR:
      eat(MENOR);
      J( );
      H_prima( );
      break;
    case MAYOR:
      eat(MAYOR);
      J( );
      H_prima( );
      break;
    case MAYOR_IGUAL:
      eat(MAYOR_IGUAL);
      J( );
      H_prima( );
      break;
    case MENOR_IGUAL:
      eat(MENOR_IGUAL);
      J( );
      H_prima( );
      break;
    case PARENTESIS_CIERRA:
      break;
    default:
      error( );
      break;
  }
}

void J( ){
  printf("J( )\n");
  E( );
  J_prima( );
}

void J_prima( ){
  printf("J'( )\n");
  if(token==DISTINTO){
    eat(DISTINTO);
    E( );
    J_prima( );
  }else if(token==IDENTICO){
    eat(IDENTICO);
    E( );
    J_prima( );
  }else if(token==MAYOR || token==MENOR || token==PARENTESIS_CIERRA || token==MAYOR_IGUAL || token==MENOR_IGUAL){
    //Retorno a funcion
  }
  else
    error( );
}