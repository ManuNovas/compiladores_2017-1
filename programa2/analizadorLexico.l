%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

int errorL [20];
int errorC[20];
int lineas=1;
int totalErrores=0;
int cuentaCar=1;
int i;
typedef size_t yy_size_t;
		
%}

%option yylineno

letra [a-zA-Z_]
caracter [a-zA-Z_0-9]
digito [0-9]
op [+\-*/%]
carEsp [(){};,]

%%

; {cuentaCar+=yyleng;return PUNTO_COMA;}

return {cuentaCar+=yyleng;return RETORNA;}

(int|float|char|void) {cuentaCar+=yyleng;return PALABRA_RESERVADA;}

{letra}{caracter}* {cuentaCar+=yyleng;return ID;}

func {cuentaCar+=yyleng; return FUNCION;}

\( {cuentaCar+=yyleng; return PARENTESIS_ABRE;}

\) {cuentaCar+=yyleng; return PARENTESIS_CIERRA;}

\{ {cuentaCar+=yyleng; return LLAVE_ABRE;}

\} {cuentaCar+=yyleng; return LLAVE_CIERRA;}

\, {cuentaCar+=yyleng; return COMA;}

if {cuentaCar+=yyleng; return SI;}

else {cuentaCar+=yyleng; return SINO;}

while {cuentaCar+=yyleng; return MIENTRAS;}

= {cuentaCar+=yyleng; return IGUAL;}

\+ {cuentaCar+=yyleng; return MAS;}

\- {cuentaCar+=yyleng; return MENOS;}

\* {cuentaCar+=yyleng; return POR;}

\/ {cuentaCar+=yyleng; return ENTRE;}

{digito}{letra}{caracter}* {errorL[totalErrores]=lineas;errorC[totalErrores]=cuentaCar;cuentaCar+=yyleng;
	totalErrores+=1;}

{digito}+ {if(atoi(yytext) <= 1000){return CE;}
	else{errorL[totalErrores]=lineas;errorC[totalErrores]=cuentaCar;cuentaCar+=yyleng;totalErrores+=1;}}

\< {cuentaCar+=yyleng; return MENOR;}

\> {cuentaCar+=yyleng; return MAYOR;}

">=" {cuentaCar+=yyleng; return MAYOR_IGUAL;}

"<=" cuentaCar+=yyleng; return MENOR_IGUAL;}

"!=" {cuentaCar+=yyleng; return DISTINTO;}

"==" {cuentaCar+=yyleng; return IDENTICO;}

[\n] {lineas++;cuentaCar=1;}

[\t] {cuentaCar+=4;}

[ ] {cuentaCar+=1;}

. {printf("\ncaracter inesperado. ");cuentaCar+=yyleng;}

<<EOF>> {printf("\n\nERRORES:\n\n");
for(i=0;i<totalErrores;i++)
printf("Error en la linea: %d en el caracter: %d\n",errorL[i],errorC[i]);
printf("\n");
return 0;}

%%

int yywrap( ){
	return 1;
}
