#ifndef _H_BASICAS
#define _H_BASICAS


void flush_stdin();


char get_char_and_flush_stdin();


double ArrayToFloat(char *str, int *b);


int ArrayToInt(char *str, int *b);


void copia(char *s1, char *s2);


void concatena(char *s1, char *s2);


int compara(char *c, char *c2);


int precedencia(char *c, char *c2);


#endif


