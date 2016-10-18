%{
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
int errorL [20];
int errorC[20];
int lineas=1;
int totalErrores=0;
int cuentaCar=1;
int i;
%}
letra [a-zA-Z_]
caracter [a-zA-Z_0-9]
digito [0-9]

%%

return {cuentaCar+=yyleng;return RETORNA;}
func {cuentaCar+=yyleng;return FUNCION;}
if {cuentaCar+=yyleng;return SI;}
else {cuentaCar+=yyleng;return SINO;}
while {cuentaCar+=yyleng;return MIENTRAS;}
(int|float|char|void) {cuentaCar+=yyleng;return PALABRA_RESERVADA;}
{letra}{caracter}* {cuentaCar+=yyleng;return ID;}
";" {cuentaCar+=yyleng;return PUNTO_COMA;}
"(" {cuentaCar+=yyleng;return PARENTESIS_ABRE;}
")" {cuentaCar+=yyleng;return PARENTESIS_CIERRA;}
"{" {cuentaCar+=yyleng;return LLAVE_ABRE;}
"}" {cuentaCar+=yyleng;return LLAVE_CIERRA;}
"," {cuentaCar+=yyleng;return COMA;}
"+" {cuentaCar+=yyleng;return MAS;}
"-" {cuentaCar+=yyleng;return MENOS;}
"*" {cuentaCar+=yyleng;return POR;}
"/" {cuentaCar+=yyleng;return ENTRE;}
{digito}+ {if(atoi(yytext)<=1000){return NUMERO;}else{errorL[totalErrores]=lineas;errorC[totalErrores]=cuentaCar;cuentaCar+=yyleng;totalErrores+=1;}}
">=" {cuentaCar+=yyleng;return MAYOR_IGUAL;}
"<=" {cuentaCar+=yyleng;return MENOR_IGUAL;}
"<" {cuentaCar+=yyleng;return MENOR;}
">" {cuentaCar+=yyleng;return MAYOR;}
"!=" {cuentaCar+=yyleng;return DISTINTO;}
"==" {cuentaCar+=yyleng;return IDENTICO;}
"=" {cuentaCar+=yyleng;return IGUAL;}
[\n] {lineas++;cuentaCar=1;}
[\t] {cuentaCar+=4;}
[ ] {cuentaCar+=1;}
. {printf("\ncaracter inesperado. ");cuentaCar+=yyleng;}
<<EOF>> {if(totalErrores!=0){printf("\n\nERRORES LEXICOS:\n\n");
		for(i=0;i<totalErrores;i++)
			printf("Error en la linea: %d en el caracter: %d\n",errorL[i],errorC[i]);
		printf("\n");}else
		return 0;}

%%

int yywrap(void){return 1;}
