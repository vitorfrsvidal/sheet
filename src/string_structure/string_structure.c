#include<stdio.h>
#include<stdlib.h>
#include "./string_structure.h"


/*
        Ponteiros ou apontadores, são variáveis que armazenam o endereço de memória de outras variáveis.

        Dizemos que um ponteiro "aponta" para uma varíável quando contém o endereço da mesma.
*/


void initialize(string *s){	// a função "initialize" recebe como parâmetro um apontador de apontador do tipo "string" (ou seja, recebe como parâmetro o endereço de memória de um apontador do tipo "string")

	*s = NULL;	// vai onde "s" aponta (vai no endereço armazenado em "s") e seta como NULL (sem endereço de memória, aponta para um endereço nulo)

}	// OBS.: Só é possível alterar o valor de uma variável (permanentemente) passada por parâmetro para uma função em C usando ponteiros, pois a alteração é feita em endereço de memória!


int insert_stdin_input(string *s){
	string new_node, valid_node;	// "new_node" e "valid_node" são apontadores para struct "node_of_character" do tipo "words"
	char c;

	valid_node = *s;

	if (valid_node != NULL){

		for (; (*valid_node).next != NULL; valid_node = (*valid_node).next);

	}

	while ((c = getc(stdin)) && (c != '\n') && (c != EOF)){	// enquanto a letra entrada não é uma quebra de linha

		if ((new_node = (string)malloc(sizeof(words))) && (new_node != NULL)){	// se foi possível alocar espaço na memória para uma struct do tipo "words" e "new_node" pôde receber o endereço de memória dessa struct (truncando como tipo string: (string)malloc...)

			(*new_node).character = c;

			if (*s == NULL){	// se *s acabou de ser inicializada

				(*new_node).prior = (*new_node).next = NULL;
				*s = valid_node = new_node;	// atualiza o valor de valid_node caso seja a primeira inserção

			} else {	// se *s já contém algum nó

				(*new_node).next = NULL;
				(*new_node).prior = valid_node;
				(*valid_node).next = new_node;
				valid_node = new_node;

			}

		} else {

			fprintf(stderr,"We're running out of RAM memory...\n");
			return 1;

		}

	}

	return 0;

}


int insert_array_input(string *s, char *str){
        string new_node, valid_node;    // "new_node" e "valid_node" são apontadores para struct "node_of_character" do tipo "words"
	int i = 0;

	valid_node = *s;

	if (valid_node != NULL){

		for (; (*valid_node).next != NULL; valid_node = (*valid_node).next);

	}

        while (str[i] != '\0'){       // enquanto a letra entrada não chegou até o fim

                if ((new_node = (string)malloc(sizeof(words))) && (new_node != NULL)){  // se foi possível alocar espaço na memória para uma struct do tipo "words" e "new_node" pôde receber o endereço de memória dessa struct (truncando como tipo string: (string)malloc...)

                        (*new_node).character = str[i];

                        if (*s == NULL){        // se *s acabou de ser inicializada

                                (*new_node).prior = (*new_node).next = NULL;
                                *s = valid_node = new_node;

                        } else {        // se *s já contém algum nó

                                (*new_node).next = NULL;
                                (*new_node).prior = valid_node;
                                (*valid_node).next = new_node;
				valid_node = new_node;

                        }

                } else {

                        fprintf(stderr,"We're running out of RAM memory...\n");
                        return 1;

                }

		i++;

        }

	return 0;

}


int insert_string_input(string *s, string *str){
	string new_node, valid_node, aux_node;

	valid_node = *s;

	if (valid_node != NULL){

		for (; (*valid_node).next != NULL; valid_node = (*valid_node).next);

	}

	aux_node = *str;

	while (aux_node != NULL){

		if ((new_node = (string)malloc(sizeof(words))) && (new_node != NULL)){

			(*new_node).character = (*aux_node).character;

			if (*s == NULL){

				(*new_node).prior = (*new_node).next = NULL;
				*s = valid_node = new_node;

			} else {

				(*new_node).next = NULL;
				(*new_node).prior = valid_node;
				(*valid_node).next = new_node;
				valid_node = new_node;

			}

		} else {

			fprintf(stderr,"We're running out of RAM memory...\n");
			return 1;

		}

		aux_node = (*aux_node).next;

	}

	return 0;

}


void reinitialize(string *s){
	string node;

	while (*s != NULL){

		node = *s;
		*s = (*(*s)).next; // (*(*s)).next => Vá no campo "next" (que é do tipo "string") do apontador apontado pelo apontador "s" (que é um apontador para o tipo "string")
		free(node);

	}

}


int print_output(string *s){
	string node;

	if (*s != NULL){

		for (node = *s; (node != NULL); printf ("%c",(*node).character), node = (*node).next);
		return 0;

	}

	return 1;

}


int print_output_inverted(string *s){
        string node;

	if (*s != NULL){

	        for (node = *s; ((*node).next != NULL); node = (*node).next);

		while (node != NULL){

			printf ("%c",(*node).character);
			node = (*node).prior;

		}

		return 0;

	}

	return 1;

}


double StringToFloat(string *s, int *b){ //b contem 0 se for um numero entrado e 1 se não for
	string node;
        double num=0, numf=0, cont=1, neg=1;
	int t = 1;

	if ((*s != NULL) && ((*(*s)).character == '-') && ((*(*s)).next != NULL)){
		neg = -1;
		node = (*(*s)).next;
	} else if (*s != NULL){
		node = *s;
	} else {
		*b = 1;
		return 0;
	}

        for(; (node != NULL) && ((*node).character != ',') && ((*node).character != '.'); node = (*node).next){ //parte inteira
                num *= 10;
                if((*node).character > 47 && (*node).character < 58){
                        num += ((*node).character - 48);
			t = 0;
                } else {
			*b = 1;
                        return 0;
                }
        }
        if(node == NULL){ //verifica se so foi um inteiro entrado
		*b = 0;
                return (num * neg);
        }
        for(node = (*node).next; (node != NULL); node = (*node).next){ //parte fracionada / node = (*node).next salta a vírgula ou o ponto
                cont*=10;
                numf *= 10;
                if((*node).character > 47 && (*node).character < 58){
                        numf += ((*node).character - 48);
			t = 0;
                } else {
			*b = 1;
                        return 0;
                }
        }
        numf /= cont;
       	num += numf;
	if (t == 0){
		*b = 0;
	} else {
		*b = 1;
	}
       	return (num * neg);
}


int StringToInt(string *s, int *b){ //b contem 0 se for um numero entrado e 1 se não for
	string node;
	int num=0, neg=1;

	if ((*s != NULL) && ((*(*s)).character == '-') && ((*(*s)).next != NULL)){
		neg = -1;
		node = (*(*s)).next;
	} else if (*s != NULL){
		node = *s;
	} else {
		*b = 1;
		return 0;
	}

	for(; (node != NULL); node = (*node).next){
                num *= 10;
                if((*node).character > 47 && (*node).character < 58){
                        num += ((*node).character - 48);
                } else {
			*b = 1;
                        return 0;
                }
        }
	*b = 0;
        return (num * neg);
}


int compare(string *s, string *str){ // funcao para comparar se uma string s eh igual a string str / retorna 0 se for true e 1 se for false (independente se estao com letras maiusculas ou menusculas)
	string aux_node_s = *s, aux_node_str = *str;
	int k, j;
	
	while ((aux_node_s != NULL) && (aux_node_str != NULL)){

		k = j = 0;

		if (((*aux_node_s).character > 64) && ((*aux_node_s).character < 91)){

			k = 32;

		}

		if (((*aux_node_str).character > 64) && ((*aux_node_str).character < 91)){

			j = 32;

		}

		if (((*aux_node_s).character + k) != ((*aux_node_str).character + j)){

			return 1;

		}

        	aux_node_s = (*aux_node_s).next;
		aux_node_str = (*aux_node_str).next;

	}

	if ((aux_node_s == NULL) && (aux_node_str == NULL)){

		return 0;

	}

	return 1;

}


int precedence(string *s, string *str){ // retorna 0 se s antecede str, 1 se nao e 2 se são iguais
	string aux_node_s = *s, aux_node_str = *str;
	int e, i;

	while ((aux_node_s != NULL) && (aux_node_str != NULL)){

		i = e = 0;

		if (((*aux_node_s).character > 64) && ((*aux_node_s).character < 91)){

			i = 32;

		}

		if (((*aux_node_str).character > 64) && ((*aux_node_str).character < 91)){

			e = 32;

		}

		if (((*aux_node_s).character + i) < ((*aux_node_str).character + e)){

			return 0;

		} else if (((*aux_node_s).character + i) > ((*aux_node_str).character + e)){

			return 1;

		}

		aux_node_s = (*aux_node_s).next;
		aux_node_str = (*aux_node_str).next;

	}

	if ((aux_node_s == NULL) && (aux_node_str == NULL)){ // sao iguais

		return 2;

	} else if (aux_node_s == NULL){

		return 0;

	} else {

		return 1;

	}

}


int is_it_a_number(string *s){ // 0 se é um número, 1 se não
	string node;
	int t = 1;

	if ((*s != NULL) && ((*(*s)).character == '-') && ((*(*s)).next != NULL)){
		node = (*(*s)).next;
	} else if (*s != NULL){
		node = *s;
	} else {
		return 1;
	}

        for(; (node != NULL) && ((*node).character != ',') && ((*node).character != '.'); node = (*node).next){ //parte inteira
                if((*node).character < 48 || (*node).character > 57){
			return 1;
                } else {
			t = 0;
		}
        }
        if(node == NULL){ //verifica se so foi um inteiro entrado
                return 0;
        }
        for(node = (*node).next; (node != NULL); node = (*node).next){ //parte fracionada / node = (*node).next salta a vírgula ou o ponto
                if((*node).character < 48 || (*node).character > 57){
			return 1;
                } else {
			t = 0;
		}
        }

	return t; // se em algum momento pegou um numero, antes ou depois da virgula ou ponto
}


