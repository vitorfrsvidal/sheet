#include<stdio.h>
#include<stdlib.h>
#include "../basicas/basicas.h"
#include "../string_structure/string_structure.h"
#include "../transaction/transaction.h"
#include "./balance.h"


void initialize_balance_sheet(balance_sheet *b){

	*b = NULL;

}


balance_sheet new_balance_sheet_node(balance_sheet *b, string *year_month_data){
	balance_sheet new_node, current_node;
	int r;

	if ((new_node = (balance_sheet)malloc(sizeof(monthly_accounting_record))) && (new_node != NULL)){

		if (*b == NULL){

			(*new_node).prior = (*new_node).next = NULL;
			*b = new_node;

		} else {

			for (current_node = *b; ((r = precedence(year_month_data, &(*current_node).year_month)) != 0) && ((*current_node).next != NULL); current_node = (*current_node).next);

			if (r == 2){

				fprintf(stderr, "Monthly accounting record already exists, aborting...\n");
				free(new_node);
				return NULL;

			} else if (r == 0){

				(*new_node).prior = (*current_node).prior;
				(*current_node).prior = new_node;
				(*new_node).next = current_node;

				if((*new_node).prior != NULL){

					(*(*new_node).prior).next = new_node;

				} else {

					*b = new_node;

				}

			} else {

				(*new_node).prior = current_node;
				(*new_node).next = NULL;
				(*current_node).next = new_node;

			}

		}

		initialize(&(*new_node).year_month);
		insert_string_input(&(*new_node).year_month, year_month_data);

		initialize_transaction(&(*new_node).balance);

	} else {

		fprintf(stderr,"We're running out of RAM memory...\n");
		return NULL;

	}

	return new_node;

}


balance_sheet search_balance_sheet(balance_sheet *b, string *year_month_data){
	balance_sheet node;
	int r;

	for (node = *b; (node != NULL) && (r = precedence(year_month_data, &(*node).year_month) != 2); node = (*node).next){

		if (r == 0){

			return NULL;

		}

	}

	return node;

}


int remove_balance_sheet_node(balance_sheet *b, string *year_month_data){
	balance_sheet node;
	int r;

	for (node = *b; (node != NULL) && (r = precedence(year_month_data, &(*node).year_month) != 2); node = (*node).next){

		if (r == 0){

			return 1;

		}

	}

	if (node != NULL){

		if (*b == node){

			*b = (*node).next;

		}

		if ((*node).prior != NULL){

			(*(*node).prior).next = (*node).next;

		}

		if ((*node).next != NULL){

			(*(*node).next).prior = (*node).prior;

		}

		reinitialize(&(*node).year_month);
		reinitialize_transactions(&(*node).balance);
		free(node);
		return 0;

	} else {

		return 1;

	}

}


void reinitialize_balance_sheet(balance_sheet *b){
	balance_sheet node;

	while (*b != NULL){

		node = *b;
		*b = (*(*b)).next;
		reinitialize(&(*node).year_month);
		reinitialize_transactions(&(*node).balance);
		free(node);

	}

}


void print_balance_sheet_month_name(balance_sheet *b){
	balance_sheet node;

	for (node = *b; (node != NULL); print_output(&(*node).year_month), fprintf(stdout, "\n"), node = (*node).next);

}


void print_balance_sheet_modified_month_name(balance_sheet *b){
	balance_sheet node;
	string lastchar; // -1
	char month[3];
	int c, result;

	if (*b != NULL){

		for (node = *b; (node != NULL); node = (*node).next){

			if ((*node).year_month != NULL){

				for (lastchar = (*node).year_month; ((*lastchar).next != NULL); lastchar = (*lastchar).next);

				month[0] = '0';
				month[1] = '0';
				month[2] = '\0';

				if ((*lastchar).prior != NULL){

					//fprintf(stdout, "%c", (*(*lastchar).prior).character);
					month[0] = (*(*lastchar).prior).character;

				}

				//fprintf(stdout, "%c\n", (*lastchar).character);
				month[1] = (*lastchar).character;

				result = ArrayToInt(month, &c);

				switch (result){

					case 1:

						fprintf(stdout, "[ 01 ] - Janeiro\n");

					break;

					case 2:

						fprintf(stdout, "[ 02 ] - Fevereiro\n");

					break;

					case 3:

						fprintf(stdout, "[ 03 ] - Marco\n");

					break;

					case 4:

						fprintf(stdout, "[ 04 ] - Abril\n");

					break;

					case 5:

						fprintf(stdout, "[ 05 ] - Maio\n");

					break;

					case 6:

						fprintf(stdout, "[ 06 ] - Junho\n");

					break;

					case 7:

						fprintf(stdout, "[ 07 ] - Julho\n");

					break;

					case 8:

						fprintf(stdout, "[ 08 ] - Agosto\n");

					break;

					case 9:

						fprintf(stdout, "[ 09 ] - Setembro\n");

					break;

					case 10:

						fprintf(stdout, "[ 10 ] - Outubro\n");

					break;

					case 11:

						fprintf(stdout, "[ 11 ] - Novembro\n");

					break;

					case 12:

						fprintf(stdout, "[ 12 ] - Dezembro\n");

					break;

					default:

						fprintf(stderr, "Dado invalido!\n");

				}

			}

		}

	} else {

		fprintf(stdout, "[ Vazio! ]\n");

	}

}


void write_balance_sheet(balance_sheet *b, char *output_file_name){
	balance_sheet node;
	transactions t;
	string s;
	FILE *balance_year_record;

	balance_year_record = fopen(output_file_name,"w");

	for (node = *b; (node != NULL); node = (*node).next){

		for (s = (*node).year_month; (s != NULL); fputc((*s).character, balance_year_record), s = (*s).next);
		fputc('\n', balance_year_record);

		for (t = (*node).balance; (t != NULL); t = (*t).next){

			for (s = (*t).name; (s != NULL); fputc((*s).character, balance_year_record), s = (*s).next);
			fputc('\n', balance_year_record);

			for (s = (*t).value; (s != NULL); fputc((*s).character, balance_year_record), s = (*s).next);
			fputc('\n', balance_year_record);

			for (s = (*t).receipted; (s != NULL); fputc((*s).character, balance_year_record), s = (*s).next);
			fputc('\n', balance_year_record);

			fputc((*t).type, balance_year_record);
			fputc('\n', balance_year_record);

		}

		fputc('\n', balance_year_record);

	}

	fclose(balance_year_record);

}


int read_balance_sheet(balance_sheet *b, char *input_file_name){
	FILE *balance_year_record;
	balance_sheet node;
	string buffer1, buffer2, buffer3;
	char c[2], t;
	int line_data = 1;

	if ((balance_year_record = fopen(input_file_name, "r")) == NULL){

		fprintf(stderr, "\nFile \"%s\" not found. Creating new file called \"%s\"...\n", input_file_name, input_file_name);
		balance_year_record = fopen(input_file_name, "a+");
		fclose(balance_year_record);
		return 1;

	}

	initialize(&buffer1);
	initialize(&buffer2);
	initialize(&buffer3);
	c[1] = '\0'; // necessario para inserir um unico char como array

	rewind(balance_year_record);

	while ((c[0] = fgetc(balance_year_record)) != EOF){

		if (c[0] == '\n'){ // if para controle do case abaixo atraves do char '\n'

			if ((c[0] = fgetc(balance_year_record)) == '\n'){

				if (line_data == 5){ // se existem transacoes para o mes atual

					new_transaction(&(*node).balance, &buffer1, &buffer2, &buffer3, t);
					reinitialize(&buffer1);
					reinitialize(&buffer2);
					reinitialize(&buffer3);

				} else { // line_data será sempre igual a 1 se entrar aqui

					new_balance_sheet_node(b, &buffer1);
					reinitialize(&buffer1);

				}

				if ((c[0] = fgetc(balance_year_record)) == EOF){

					fclose(balance_year_record);
					return 0;

				}

				line_data = 1; // significa que acabaram as transacoes do mes atual e vai passar para um novo mes, ou seja, um novo balance sheet node

			} else if (line_data == 1){

				node = new_balance_sheet_node(b, &buffer1);
				reinitialize(&buffer1);
				line_data = 2;

			} else if (line_data == 2){

				line_data = 3;

			} else if (line_data == 3){

				line_data = 4;

			} else if (line_data == 4) {

				line_data = 5;

			} else if (line_data == 5){ // se leu todas as linhas 

				new_transaction(&(*node).balance, &buffer1, &buffer2, &buffer3, t);
				reinitialize(&buffer1);
				reinitialize(&buffer2);
				reinitialize(&buffer3);
				line_data = 2;

			}

		}

		if ((line_data == 1) || (line_data == 2)){

			insert_array_input(&buffer1, c);

		} else if (line_data == 3){

			insert_array_input(&buffer2, c);

		} else if (line_data == 4){

			insert_array_input(&buffer3, c);

		} else if (line_data == 5){

				t = c[0];

		}

	}

	fclose(balance_year_record);
	return 0;

}


