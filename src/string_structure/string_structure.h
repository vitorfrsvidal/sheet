#ifndef _H_STRING_STRUCTURE
#define _H_STRING_STRUCTURE


typedef struct node_of_character{
        char character;
        struct node_of_character *prior, *next;
} words, *string;       // "string" é definido como um apontador (armazena o endereço de memória) para a struct "node_of_character" definida como tipo "words"


void initialize(string *s);


int insert_stdin_input(string *s);


int insert_array_input(string *s, char *str);


int insert_string_input(string *s, string *str);


void reinitialize(string *s);


int print_output(string *s);


int print_output_inverted(string *s);


double StringToFloat(string *s, int *b);


int StringToInt(string *s, int *b);


int compare(string *s, string *str);


int precedence(string *s, string *str);


int is_it_a_number(string *s);


#endif


