#include<stdio.h>
#include<stdlib.h>
#include "../string_structure/string_structure.h"	//precisa incluir a biblioteca de string porque vou usar o tipo "string"
#include "./transaction.h"	//o tipo string é chamado na struct transactions no header transaction.h


void initialize_transaction(transactions *t){

	*t = NULL;

}


int new_transaction(transactions *t, string *name_data, string *value_data, string *receipted_data, char type_data){
	transactions new_node, current_node;
	int r;

	if ((new_node = (transactions)malloc(sizeof(operation))) && (new_node != NULL)){

		if (*t == NULL){

			(*new_node).prior = (*new_node).next = NULL;
			*t = new_node;

		} else {

			for (current_node = *t; ((r = precedence(name_data, &(*current_node).name)) != 0) && ((*current_node).next != NULL); current_node = (*current_node).next);

			if (r == 2){ // se o novo nó a ser inserido já existe na lista de transacoes

				fprintf(stderr,"Transaction already exists, aborting...\n");
				free(new_node);
				return 1;

			} else if (r == 0){ // se o novo nó a ser inserido vem antes do nó current_node (que é sempre um nó válido)

				(*new_node).prior = (*current_node).prior;
				(*current_node).prior = new_node;
				(*new_node).next = current_node;

				if((*new_node).prior != NULL){ // se existe algum nó válido antes do nó que está sendo inserido, ele precisa apontar para o novo nó

					(*(*new_node).prior).next = new_node;

				} else { // quando (*new_node).prior é igual a NULL, *t é igual a current_node, será o primeiro nó

					*t = new_node;

				}

			} else { // se chegar até o fim da lista, ou seja (*current_node).next == NULL, adicionar após current_node

				(*new_node).prior = current_node;
				(*new_node).next = NULL; // ou (*new_node).next = (*current_node).next (pois (*current_node).next é igual a NULL)
				(*current_node).next = new_node;

			}

		}

		initialize(&(*new_node).name);
		insert_string_input(&(*new_node).name, name_data);

		initialize(&(*new_node).value);
		insert_string_input(&(*new_node).value, value_data);

		initialize(&(*new_node).receipted);
		insert_string_input(&(*new_node).receipted, receipted_data);

		(*new_node).type = type_data;

	} else {

		fprintf(stderr,"We're running out of RAM memory...\n");
		return 1;

	}

	return 0;

}


int print_transactions(transactions *t){
	transactions node;

	if (*t != NULL){

		for (node = *t; (node != NULL); print_output(&(*node).name), print_output(&(*node).value), print_output(&(*node).receipted), printf("%c\n", (*node).type), node = (*node).next);
		return 0;

	}

	return 1;

}


int print_transactions_inverted(transactions *t){
	transactions node;

	if (*t != NULL){

		for (node = *t; (*node).next != NULL; node = (*node).next);

		while (node != NULL){

			print_output(&(*node).name);
			print_output(&(*node).value);
			print_output(&(*node).receipted);
			printf("%c\n", (*node).type);
			node = (*node).prior;

		}

		return 0;

	}

	return 1;

}


void reinitialize_transactions(transactions *t){
	transactions node;

	while (*t != NULL){

		node = *t;
		*t = (*(*t)).next;
		reinitialize(&(*node).name);
		reinitialize(&(*node).value);
		reinitialize(&(*node).receipted);
		free(node);

	}

}


transactions search_transaction(transactions *t, string *s){ // retorna a transação ou NULL
	transactions node;
	int r;

	for (node = *t; (node != NULL) && (r = precedence(s, &(*node).name) != 2); node = (*node).next){

		if (r == 0){ // se a string que eu to procurando precede a do nó atual

			return NULL;

		}

	}

	return node;

}


int remove_transaction(transactions *t, string *s){ // 0 == removeu, 1 == nao encontrou
	transactions node;
	int r;

	for (node = *t; (node != NULL) && (r = precedence(s, &(*node).name) != 2); node = (*node).next){

		if (r == 0){ // se a string que eu to procurando precede a do nó atual

			return 1;

		}

	}

	if (node != NULL){

		if (*t == node){

			*t = (*node).next;

		}

		if ((*node).prior != NULL){

			(*(*node).prior).next = (*node).next;

		}

		if ((*node).next != NULL){

			(*(*node).next).prior = (*node).prior;

		}

		reinitialize(&(*node).name);
		reinitialize(&(*node).value);
		reinitialize(&(*node).receipted);
		free(node);
		return 0;

	} else {

		return 1;

	}

}


