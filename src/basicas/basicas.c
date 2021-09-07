#include<stdio.h>
#include<stdlib.h>
#include "./basicas.h"


void flush_stdin(){
	int c;

	while ((c = getc(stdin)) != '\n' && c != EOF);

}


char get_char_and_flush_stdin(){
	char c, d;

	while ((c = fgetc(stdin)) == '\n' || c == EOF); // pegando todos os caracteres '\n' ou EOF antes de um caracter valido

	while ((d = getc(stdin)) != '\n' && d != EOF); // pegando todos os caracteres '\n' ou EOF depois de um caracter valido

	return c;

}


double ArrayToFloat(char *str, int *b){ //b contem 0 se for um numero entrado e 1 se não for
        int i, t = 1;
        double num=0, numf=0, cont=1, neg=1;

	if ((str[0]!='\0') && (str[0]=='-') && (str[1]!='\0')){
		neg = -1;
		i=1;
	} else if (str[0]!='\0'){
		i=0;
	} else {
		*b = 1;
		return 0;
	}

        for(; (str[i]!='\0') && (str[i]!=',') && (str[i]!='.');i++){ //parte inteira
                num *= 10;
                if(str[i]>47&&str[i]<58){
                        num += (str[i]-48);
			t = 0;
                } else {
			*b = 1;
                        return 0;
                }
        }
        if(str[i]=='\0'){ //verifica se so foi um inteiro entrado
		*b = 0;
                return (num * neg);
        }
        for(i+=1;str[i]!='\0';i++){ //parte fracionada / i+=1 salta a vírgula ou o ponto
                cont*=10;
                numf *= 10;
                if(str[i]>47&&str[i]<58){
                        numf += (str[i]-48);
			t = 0;
                } else {
			*b = 1;
                        return 0;
                }
        }
        numf /= cont;
        num += numf;
	if ( t == 0){
		*b = 0;
	} else {
		*b = 1;
	}
        return (num * neg);
}


int ArrayToInt(char *str, int *b){ //b contem 0 se for um numero entrado e 1 se não for
        int i, num=0,neg=1;

	if ((str[0]!='\0') && (str[0]=='-') && (str[1]!='\0')){
		neg = -1;
		i=1;
	} else if (str[0]!='\0'){
		i=0;
	} else {
		*b = 1;
		return 0;
	}

        for(; str[i]!='\0';i++){
                num *= 10;
                if(str[i]>47&&str[i]<58){
                        num += (str[i]-48);
                } else {
			*b = 1;
                        return 0;
                }
        }
	*b = 0;
        return (num * neg);
}


void copia(char *s1, char *s2){ // copia a string s2 para a string s1
    int count=0;
    while (s2[count]!='\0'){
        s1[count]=s2[count];
        count++;
    }
    s1[count]=s2[count];
}


void concatena(char *s1, char *s2){ //concatena a string s2 na string s1
        int i, e;
        for(i=0;(s1[i]!='\0');i++); //conta o tamanho da string s1
        for(e=0;(s2[e]!='\0');s1[i]=s2[e], i++, s1[i]='\0', e++); //(...) printf("antes: %d\n",i), i++, printf("depois: %d\n",i) (...)
}


int compara(char *c, char *c2){ // funcao para comparar se uma string c eh igual a string c2 / retorna 0 se for true e 1 se for false
    int e=0, k, j;
    while ((c[e]!='\0')&&(c2[e]!='\0')){
        k=j=0;
        if ((c[e]>64)&&(c[e]<91)){
            k=32;
        }
        if ((c2[e]>64)&&(c2[e]<91)){
            j=32;
        }
        if ((c[e]+k)!=(c2[e]+j)){
            return 1;
        }
        e++;
    }
    if (c[e]==c2[e]){
        return 0;
    }
    return 1;
}


int precedencia(char *c, char *c2){ // retorna se a string c vem antes da string c2 / retorna 0 se for true e 1 se for false, se forem iguais retorna 2
    int count=0,e,i;
    while((c[count]!='\0')&&(c2[count]!='\0')){
        i=e=0;
        if ((c[count]>64)&&(c[count]<91)){
            i=32;
        }
        if ((c2[count]>64)&&(c2[count]<91)){
            e=32;
        }
        if ((c[count]+i)<(c2[count]+e)){
            return 0;
        } else if ((c[count]+i)>(c2[count]+e)){
            return 1;
        }
        count++;
    }
    if ((c[count]=='\0')&&(c2[count]=='\0')){
            return 2;
    } else if (c[count]=='\0'){
            return 0;
    } else {
            return 1;
    }
}


