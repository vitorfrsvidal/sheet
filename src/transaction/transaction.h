#ifndef _H_TRANSACTION
#define _H_TRANSACTION


typedef struct node_of_transaction{
        string name;
	string value;
	string receipted;
	char type;
        struct node_of_transaction *prior, *next;
} operation, *transactions;


void initialize_transaction(transactions *t);


int new_transaction(transactions *t, string *name_data, string *value_data, string *receipted_data, char type_data);


int print_transactions(transactions *t);


int print_transactions_inverted(transactions *t);


void reinitialize_transactions(transactions *t);


transactions search_transaction(transactions *t, string *s);


int remove_transaction(transactions *t, string *s);


#endif


