/*
 *Authors:
 *	Martínez Rojas Jorge Antonio
 *	Novas Santamaría José Manuel
 **/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
  int clase;
  char id[20];
  struct SIMBOLO *siguiente;
}SIMBOLO;

SIMBOLO *simbolos, *h=NULL, *t=NULL;
int l=1, c=0;

int convertidor(char c){
  if(c=='i')
    return 0;
  else if(c=='f')
    return 1;
  else if(c=='n')
    return 2;
  else if(c=='t')
    return 3;
  else if(c=='e')
    return 4;
  else if(c=='l')
    return 5;
  else if(c=='s')
    return 6;
  else if(c=='o')
    return 7;
  else if(c=='a')
    return 8;
  else if((c>='b' && c<='d') || c=='g' || c=='h' || c=='j' || c=='k' || c=='m' || (c>='p' && c<='r') || (c>='u' && c<='z') || c=='_')
    return 9;
  else if(c>='0' && c<='9')
    return 10;
  else if(c=='*')
    return 11;
  else if(c=='/')
    return 12;
  else if(c=='+' || c=='-' || c=='%')
    return 13;
  else if(c=='=')
    return 14;
  else if(c=='>' || c=='<')
    return 15;
  else if(c=='!')
    return 16;
  else if(c=='(' || c==')' || c=='{' || c=='}' || c==';' || c==',')
    return 17;
  else if(c=='.')
    return 18;
  else if(c==' ' || c=='\n' || c=='\t'){
    l++;
    c=0;
    return 19;
  }
}

/*int agregaSimbolo(int c, char *b){
  if(h==NULL){
    h=t=(SIMBOLO *) malloc(sizeof(SIMBOLO));
    h->clase=c;
    h->id[0]='\0';
    strcpy(h->id, b);
    h->siguiente=NULL;
  }else{
    SIMBOLO *q;
    q=h;
    while(q!=NULL){
      if(((q->clase)==c) && !strcmp(b, q->id))
        return 0;
      else
        q=q->siguiente;
    }
    t->siguiente=(SIMBOLO *)malloc(sizeof(SIMBOLO));
    t->clase=c;
    t->id[0]='\0';
    strcpy(t->id, b);
    t=t->siguiente=NULL;
  }
  return 1;
}*/

void token(int e, char *b){
  if((e>=1 && e<=4) || (e>=13 && e<=15) || e==20 || e==21 ||  e==22){
    printf("<1, %s>\n", b);
    //agregaSimbolo(1, b);
  }else if(e==5 || e==6)
    printf("<4, %s>\n", b);
  else if(e==7 || e==16)
    printf("<3, %s>\n", b);
  else if(e==8 || e==18)
    printf("<5, %s>\n", b);
  else if(e==10)
    printf("<2, %s>\n", b);
  else if(e==11)
    printf("<6, %s>\n", b);
  else if(e==12){
    printf("<0, %s>\n", b);
    //agregaSimbolo(0, b);
  }else if(e==19)
    printf("<7, %s>\n", b);
  else if(e==24)
    printf("<9, >\n");
  else if(e==25)
    printf("<8,  >\n");
}

void main(int argc, char **argv){
  int automata[26][21]={
  // i   f   n   t   e   l   s   o   a le_  dig  *   / ope   = rel   ! pun   . esp acp
     1,  3,  4,  4,  2,  4,  4,  4,  4,  4, 11,  5,  6,  5,  7,  8,  9, 10, -1, 25,  0,
     4, 12, 13,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
     4,  4,  4,  4,  4, 14,  4,  4,  4,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
     4,  4,  4,  4,  4, 15,  4,  4,  4,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
     4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, 16, -1, -1, -1, -1,  0,  1, //OA
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 17, -1, -1, -1, -1, -1, -1, -1,  0,  1, //OA
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, 18, -1, -1, -1, -1,  0,  1, //ASI
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, 18, -1, -1, -1, -1,  0,  1, //OR
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, -1, -1, -1,  0, -1,  0,  1, //SP
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11,  0,  0,  0, -1,  0, -1,  0, 19,  0,  1, //ENT
     4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0, -1, -1, -1, -1, -1,  0, -1,  0,  1, //PR
     4,  4,  4, 12,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
     4,  4,  4,  4,  4,  4, 20,  4,  4,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
     4,  4,  4,  4,  4,  4,  4, 21,  4,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, -1, -1, -1, -1, -1,  0,  1, //ASI
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 22, 17, 17, 17, 17, 17, 17, 17, 17,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1, -1, -1, -1, -1, -1, -1,  0,  1, //OR
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19,  0,  0,  0, -1,  0, -1,  0, -1,  0,  1, //FLO
     4,  4,  4,  4, 12,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
     4,  4,  4,  4,  4,  4,  4,  4, 23,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 24, 17, 17, 17, 17, 17, 17, 17,  0,
     4,  4,  4, 12,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0,  0, -1,  0, -1,  0,  1, //ID
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, //COM
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 25,  1  //ESP
  };
  FILE *entrada;
  char temporal[2], buffer[20], caracter;
  int selector, actual, siguiente=0;

  if(argc!=2){
    printf("Falta archivo de entrada :(\n");
    exit(1);
  }
  entrada=fopen(argv[1], "r");
  if(entrada==NULL){
    printf("No se encuentra %s en el directorio actual :(\n", argv[1]);
    exit(1);
  }
  buffer[0]='\0';
  caracter=fgetc(entrada);
  c++;
  do{
    selector=convertidor(caracter);
    actual=siguiente;
    siguiente=automata[actual][selector];
    if(siguiente==-1){
      printf("Error en el caracter %i de la linea %i\n", c, l);
      caracter=fgetc(entrada);
      siguiente=0;
    }else if(siguiente!=0){
      temporal[0]=caracter;
      temporal[1]='\0';
      strcat(buffer, temporal);
      caracter=fgetc(entrada);
      c++;
    }else if(siguiente==0){
      token(actual, buffer);
      buffer[0]='\0';
    }
  }while(caracter!=EOF);

  fclose(entrada);
}