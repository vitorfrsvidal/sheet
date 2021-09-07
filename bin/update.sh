#!/bin/bash

# Este script so podera ser executado dentro do diretorio executable

cd .. && make clean && make && cd bin/ && echo "Sucess!" && exit 0

echo "Failed!"
exit 1

