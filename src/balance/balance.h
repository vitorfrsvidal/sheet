#ifndef _H_BALANCE
#define _H_BALANCE


typedef struct node_of_monthly_accounting_record{
        string year_month;
	transactions balance;
        struct node_of_monthly_accounting_record *prior, *next;
} monthly_accounting_record, *balance_sheet;


void initialize_balance_sheet(balance_sheet *b);


balance_sheet new_balance_sheet_node(balance_sheet *b, string *year_month_data);


balance_sheet search_balance_sheet(balance_sheet *b, string *year_month_data);


int remove_balance_sheet_node(balance_sheet *b, string *year_month_data);


void reinitialize_balance_sheet(balance_sheet *b);


void print_balance_sheet_month_name(balance_sheet *b);


void print_balance_sheet_modified_month_name(balance_sheet *b);


void write_balance_sheet(balance_sheet *b, char *output_file_name);


int read_balance_sheet(balance_sheet *b, char *input_file_name);


#endif


