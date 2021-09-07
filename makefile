SHELL	= /bin/bash


PROG	= sheet

PATH_P	= ./bin/

PROJECT	:= $(PATH_P)$(PROG)

C_SRC	= $(wildcard ./src/*/*.c)

H_SRC	= $(wildcard ./src/*/*.h)

OBJ	= $(C_SRC:.c=.o)

COMP	= gcc

C_FLAGS	= -c -W -Wall -pedantic


# $@ expande para o nome do target, $< expande para o nome do primeiro pré-requisito do target e $^ expande para a lista contendo todos os nomes dos pré-requisitos do target

# Compilacao do projeto

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(COMP) -o $@ $^


# Compilacao da estrutura do projeto (headers)

./src/main/main.o: ./src/main/main.c $(C_SRC) $(H_SRC)
	$(COMP) -o $@ $< $(C_FLAGS)

# transaction necessita de uma atencao especial, pois ele utiliza funcoes declaradas em string_structure, logo qualquer alteracao no codigo de string_structure faz necessario recompilar o codigo de transaction

./src/transaction/transaction.o: ./src/transaction/transaction.c ./src/transaction/transaction.h ./src/string_structure/string_structure.c ./src/string_structure/string_structure.h
	$(COMP) -o $@ $< $(C_FLAGS)

# balance necessita de uma atencao especial, pois ele utiliza funcoes declaradas em string_structure e transaction, logo qualquer alteracao nos codigos de string_structure e de transaction faz necessario recompilar o codigo de balance

./src/balance/balance.o: ./src/balance/balance.c ./src/balance/balance.h ./src/transaction/transaction.c ./src/transaction/transaction.h ./src/string_structure/string_structure.c ./src/string_structure/string_structure.h ./src/basicas/basicas.c ./src/basicas/basicas.h
	$(COMP) -o $@ $< $(C_FLAGS)

# para os demais que nao utilizam funcoes declaradas em outros headers

%.o: %.c %.h
	$(COMP) -o $@ $< $(C_FLAGS)


# Limpeza

clean: clear

clear:
	rm -f $(OBJ) $(PROJECT)


.PHONY: all clean clear


