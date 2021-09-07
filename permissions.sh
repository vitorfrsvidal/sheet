#!/bin/bash

# Este script so podera ser executado dentro do diretorio raiz

find . -type d -exec chmod 750 {} \; && find . -type f -exec chmod 640 {} \; && chmod 750 permissions.sh ./bin/update.sh . && make clean && make && echo "Sucess!" && exit 0

echo "Failed!"
exit 1

