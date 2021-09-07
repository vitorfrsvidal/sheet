#include<stdio.h>
#include<stdlib.h>
#include "../basicas/basicas.h"
#include "../string_structure/string_structure.h"
#include "../transaction/transaction.h"
#include "../balance/balance.h"

// indentation = 3 spaces

int main(int argc, char **argv){

   string buffer, month_string, buffer1, buffer2, buffer3;
   char i = 'z', t = 'z', month_array[3], f;
   balance_sheet sheet, node, node_aux;
   int month_int, correct, alterado = 0;
   transactions tr, tr_aux;
   double expenses, income, savings, receipt, savings_aux, receipt_aux, income_aux, expenses_aux;

   if (argc != 2){

      fprintf(stdout, "\nEntre com o ano a ser carregado ou criado como parametro!\n\n");
      return 1;

   }

   initialize_balance_sheet(&sheet);

   system("clear");

   if (read_balance_sheet(&sheet, argv[1]) == 0){

      fprintf(stdout, "\nArquivo \"%s\" carregado com sucesso!\n", argv[1]);

   }

   initialize(&buffer);
   initialize(&month_string);
   initialize(&buffer1);
   initialize(&buffer2);
   initialize(&buffer3);

   while (i != 'w'){

      fprintf(stdout, "\n>>> Menu principal\n\nEntre com a opcao desejada:\n\nm = menu mes\ns = salvar alteracoes\nw = finalizar programa (a qualquer momento)\nv = informacoes sobre autor e versao\n\n");
      while ((i = fgetc(stdin)) == '\n' || i == EOF){

         system("clear");
         fprintf(stdout, "\n>>> Menu principal\n\nEntre com a opcao desejada:\n\nm = menu mes\ns = salvar alteracoes\nw = finalizar programa (a qualquer momento)\nv = informacoes sobre autor e versao\n\n");

      }
      while ((f = fgetc(stdin)) != '\n' && f != EOF){

         i = 'z';

      }
      system("clear");

      switch (i){

         case 'm':

            while (i == 'm'){

               correct = 1;

               while ((correct == 1) && (i != 'v') && (i != 'w')){

                  fprintf(stdout,"\n>>> Menu mes\n\nEntre com a opcao desejada:\n\n");
                  print_balance_sheet_modified_month_name(&sheet);
                  fprintf(stdout,"\nv = voltar para o menu principal\n\n");
                  insert_stdin_input(&month_string);
                  system("clear");

                  if (month_string != NULL){

                     month_int = StringToInt(&month_string, &correct);
                     i = (*month_string).character;

                     if ((correct == 0) && (month_int > 0) && (month_int < 13)){ // se for um numero de mes corretamente entrado

                        sprintf(month_array, "%02i", month_int);

                     } else {

                        if (((i != 'v') && (i != 'w')) || ((*month_string).next != NULL)){

                           fprintf(stderr, "\nEntrada invalida!\n");
			   i = 'm';

                        }

                        correct = 1;

                     }

                     reinitialize(&month_string);

                  }

               }

               if ((i != 'v') && (i != 'w')){ // i é igual a '0', '1', 'v' ou 'w'

                  insert_array_input(&buffer, argv[1]); // inserindo o ano entrado como parametro
                  insert_array_input(&buffer, month_array); // inserindo o mes entrado no loop anterior

                  if ((node = search_balance_sheet(&sheet, &buffer)) == NULL){ // se nao encontrou o mes

                     while ((i != 's') && (i != 'n') && (i != 'w') && (i != 'v')){

                        fprintf(stdout, "\n>>> Menu mes\n\nMes (%s/%s) nao encontrado, deseja cria-lo?\n\ns = sim\nn = nao\n\n", month_array, argv[1]);
                        while ((i = fgetc(stdin)) == '\n' || i == EOF){

                           system("clear");
                           fprintf(stdout, "\n>>> Menu mes\n\nMes (%s/%s) nao encontrado, deseja cria-lo?\n\ns = sim\nn = nao\n\n", month_array, argv[1]);

                        }
                        while ((f = fgetc(stdin)) != '\n' && f != EOF){

                           i = 'z';

		        }
                        system("clear");

                        if (i == 's'){

                           node = new_balance_sheet_node(&sheet, &buffer);
                           alterado = 1;

                        } else if ((i != 'n') && (i != 'w') && (i != 'v')){

                           fprintf(stderr, "\nEntrada invalida!\n");

                        }

                     }

                     if ((i == 'n') || (i == 'v')){

                        i = 'm';

                     }

                  }

                  while ((i != 'm') && (i != 'w')){ // 'm' para voltar ao menu mes

                     fprintf(stdout, "\n>>> Menu transacoes (%s/%s)\n\nEntre com a opcao desejada:\n\ni = inserir transacao\nr = remover transacao\nu = atualizar valor da transacao\np = atualizar valor quitado da transacao\nt = atualizar tipo da transacao\nl = menu listagem\nx = apagar todas as transacoes e este mes\nv = voltar para o menu mes\n\n", month_array, argv[1]);
                     while ((i = fgetc(stdin)) == '\n' || i == EOF){

                        system("clear");
                        fprintf(stdout, "\n>>> Menu transacoes (%s/%s)\n\nEntre com a opcao desejada:\n\ni = inserir transacao\nr = remover transacao\nu = atualizar valor da transacao\np = atualizar valor quitado da transacao\nt = atualizar tipo da transacao\nl = menu listagem\nx = apagar todas as transacoes e este mes\nv = voltar para o menu mes\n\n", month_array, argv[1]);

                     }
                     while ((f = fgetc(stdin)) != '\n' && f != EOF){

                        i = 'z';

                     }
                     system("clear");

                     switch (i){

                        case 'i':

                           do {

                              fprintf(stdout, "\nEntre com o nome da transacao a ser inserida:\n\n");
                              insert_stdin_input(&buffer1);
                              system("clear");

                           } while (buffer1 == NULL);

			   if ((((*buffer1).character != 'w') && ((*buffer1).character != 'v')) || ((*buffer1).next != NULL)){ // se foi entrado somente w ou v nao entra nessa condicao, qualquer valor diferente de w e v entra

                              do {

                                 fprintf(stdout, "\nEntre com o valor da transacao:\n\n");
                                 insert_stdin_input(&buffer2);
                                 system("clear");

                                 if (buffer2 != NULL){

				    if ((((*buffer2).character != 'w') && ((*buffer2).character != 'v')) || ((*buffer2).next != NULL)){

				       if (is_it_a_number(&buffer2) != 0){

                                          fprintf(stderr, "\nEntre com um numero valido!\n");
                                          reinitialize(&buffer2);

                                       }

				    }

                                 }

                              } while (buffer2 == NULL);

			      if ((((*buffer2).character != 'w') && ((*buffer2).character != 'v')) || ((*buffer2).next != NULL)){

                                 do {

                                    fprintf(stdout, "\nEntre com o tipo da transacao:\n\ne = debitos\na = debito incluido no valor de outra transacao (desconsiderado)\ni = creditos\no = credito incluido no valor de outra transacao (desconsiderado)\ns = reservas\n\n");
                                    while ((t = fgetc(stdin)) == '\n' || t == EOF){

                                       system("clear");
                                       fprintf(stdout, "\nEntre com o tipo da transacao:\n\ne = debitos\na = debito incluido no valor de outra transacao (desconsiderado)\ni = creditos\no = credito incluido no valor de outra transacao (desconsiderado)\ns = reservas\n\n");

                                    }
                                    while ((f = fgetc(stdin)) != '\n' && f != EOF){

				       t = 'z';

				    }
                                    system("clear");

                                    if ((t != 'e') && (t != 'a') && (t != 'i') && (t != 'o') && (t != 's') && (t != 'w') && (t != 'v')){

                                       fprintf(stderr, "\nEntre com um tipo valido!\n");

                                    }

                                 } while ((t != 'e') && (t != 'a') && (t != 'i') && (t != 'o') && (t != 's') && (t != 'w') && (t != 'v'));

				 if ((t != 'w') && (t != 'v')){

                                    do {

                                       fprintf(stdout, "\nEntre com o valor ja quitado para a transacao:\n\n");
                                       insert_stdin_input(&buffer3);
                                       system("clear");

                                       if (buffer3 != NULL){

				          if ((((*buffer3).character != 'w') && ((*buffer3).character != 'v')) || ((*buffer3).next != NULL)){

					     if (is_it_a_number(&buffer3) != 0){

                                                fprintf(stderr, "\nEntre com um numero valido!\n");
                                                reinitialize(&buffer3);

                                             } else {

                                                system("clear");

                                                fprintf(stdout, "\n"); // para pular uma linha caso de erro e a mensagem sair formatada

                                                if (new_transaction(&(*node).balance, &buffer1, &buffer2, &buffer3, t) == 0){

                                                   fprintf(stdout, "Transacao inserida!\n");
                                                   alterado = 1;

                                                }

					     }

					  } else if ((*buffer3).character == 'w'){

				             i = 'w';

					  }

                                       }

                                    } while (buffer3 == NULL);

                                    reinitialize(&buffer3);

				 } else if (t == 'w'){

                                    i = 'w';

			         }

			      } else if ((*buffer2).character == 'w'){

                                 i = 'w';

		              }

                              reinitialize(&buffer2);

		           } else if ((*buffer1).character == 'w'){ // se entrou w em buffer1

		              i = 'w';

		           }

                           reinitialize(&buffer1);

                        break;

                        case 'r':

                           do {

                              fprintf(stdout, "\nEntre com o nome da transacao a ser removida:\n\n");
                              insert_stdin_input(&buffer1);
                              system("clear");

                           } while (buffer1 == NULL);

			   if ((((*buffer1).character != 'w') && ((*buffer1).character != 'v')) || ((*buffer1).next != NULL)){

                              if (remove_transaction(&(*node).balance, &buffer1) == 0){

                                 fprintf(stdout, "\nTransacao removida!\n");
                                 alterado = 1;

                              } else {

                                 fprintf(stderr, "\nTransacao inexistente!\n");

                              }

			   } else if ((*buffer1).character == 'w'){

                              i = 'w';

			   }
                           
                           reinitialize(&buffer1);

                        break;

                        case 'u':

                           do {

                              fprintf(stdout, "\nEntre com o nome da transacao a ser atualizada:\n\n");
                              insert_stdin_input(&buffer1);
                              system("clear");

                           } while (buffer1 == NULL);

			   if ((((*buffer1).character != 'w') && ((*buffer1).character != 'v')) || ((*buffer1).next != NULL)){

                              if ((tr = search_transaction(&(*node).balance, &buffer1)) != NULL){

                                 fprintf(stdout, "\nTransacao encontrada!\n");

                                 do {

                                    fprintf(stdout, "\nEntre com o novo valor da transacao:\n\n");
                                    insert_stdin_input(&buffer2);
                                    system("clear");

                                    if (buffer2 != NULL){

                                       if ((((*buffer2).character != 'w') && ((*buffer2).character != 'v')) || ((*buffer2).next != NULL)){

                                          if (is_it_a_number(&buffer2) != 0){

                                             fprintf(stderr, "\nEntre com um numero valido!\n");
					     reinitialize(&buffer2);

                                          } else {

                                             reinitialize(&(*tr).value);
                                             insert_string_input(&(*tr).value, &buffer2);
                                             system("clear");
                                             fprintf(stdout, "\nValor atualizado!\n");
                                             alterado = 1;

				          }

				       } else if ((*buffer2).character == 'w'){

                                          i = 'w';

                                       }

                                    }

                                 } while (buffer2 == NULL);

				 reinitialize(&buffer2);

                              } else {

                                 fprintf(stdout, "\nTransacao inexistente!\n");

                              }

			   } else if ((*buffer1).character == 'w'){

                              i = 'w';

			   }

                           reinitialize(&buffer1);

                        break;

                        case 'p':

                           do {

                              fprintf(stdout, "\nEntre com o nome da transacao a ser atualizada:\n\n");
                              insert_stdin_input(&buffer1);
                              system("clear");

                           } while (buffer1 == NULL);

			   if ((((*buffer1).character != 'w') && ((*buffer1).character != 'v')) || ((*buffer1).next != NULL)){

                              if ((tr = search_transaction(&(*node).balance, &buffer1)) != NULL){

                                 fprintf(stdout, "\nTransacao encontrada!\n");

                                 do {

                                    fprintf(stdout, "\nEntre com o novo valor quitado da transacao:\n\n");
                                    insert_stdin_input(&buffer2);
                                    system("clear");

                                    if (buffer2 != NULL){

                                       if ((((*buffer2).character != 'w') && ((*buffer2).character != 'v')) || ((*buffer2).next != NULL)){

                                          if (is_it_a_number(&buffer2) != 0){

                                             fprintf(stderr, "\nEntre com um numero valido!\n");
					     reinitialize(&buffer2);

                                          } else {

                                             reinitialize(&(*tr).receipted);
                                             insert_string_input(&(*tr).receipted, &buffer2);
                                             system("clear");
                                             fprintf(stdout, "\nValor atualizado!\n");
                                             alterado = 1;

				          }

				       } else if ((*buffer2).character == 'w'){

                                          i = 'w';

                                       }

                                    }

                                 } while (buffer2 == NULL);

				 reinitialize(&buffer2);

                              } else {

                                 fprintf(stdout, "\nTransacao inexistente!\n");

                              }

			   } else if ((*buffer1).character == 'w'){

                              i = 'w';

			   }

                           reinitialize(&buffer1);

                        break;

                        case 't':

                           do {

                              fprintf(stdout, "\nEntre com o nome da transacao a ser atualizada:\n\n");
                              insert_stdin_input(&buffer1);
                              system("clear");

                           } while (buffer1 == NULL);

			   if ((((*buffer1).character != 'w') && ((*buffer1).character != 'v')) || ((*buffer1).next != NULL)){

                              if ((tr = search_transaction(&(*node).balance, &buffer1)) != NULL){

                                 fprintf(stdout, "\nTransacao encontrada!\n");

                                 do {

                                    fprintf(stdout, "\nEntre com o novo tipo da transacao:\n\ne = debitos\na = debito incluido no valor de outra transacao (desconsiderado)\ni = creditos\no = credito incluido no valor de outra transacao (desconsiderado)\ns = reservas\n\n");
                                    while ((t = fgetc(stdin)) == '\n' || t == EOF){

                                       system("clear");
                                       fprintf(stdout, "\nEntre com o novo tipo da transacao:\n\ne = debitos\na = debito incluido no valor de outra transacao (desconsiderado)\ni = creditos\no = credito incluido no valor de outra transacao (desconsiderado)\ns = reservas\n\n");

                                    }
                                    while ((f = fgetc(stdin)) != '\n' && f != EOF){

                                       t = 'z';

                                    }
                                    system("clear");

                                    if ((t != 'e') && (t != 'a') && (t != 'i') && (t != 'o') && (t != 's') && (t != 'w') && (t != 'v')){

                                       fprintf(stderr, "\nEntre com um tipo valido!\n");

                                    }

                                 } while ((t != 'e') && (t != 'a') && (t != 'i') && (t != 'o') && (t != 's') && (t != 'w') && (t != 'v'));

                                 if ((t != 'w') && (t != 'v')){

				    (*tr).type = t;
                                    system("clear");
                                    fprintf(stdout, "\nValor atualizado!\n");
                                    alterado = 1;

				 } else if (t == 'w'){

                                    i = 'w';

                                 }

                              } else {

                                 fprintf(stdout, "\nTransacao inexistente!\n");

                              }

			   } else if ((*buffer1).character == 'w'){

                              i = 'w';

			   }

                           reinitialize(&buffer1);

                        break;

                        case 'l':

                           while ((i != 'v') && (i != 'w')){

                              fprintf(stdout, "\n>>> Menu listagem (%s/%s)\n\nEntre com a opcao desejada:\n\ne = listar debitos\ni = listar creditos\ns = listar reservas\nt = mostrar saldo total\nv = voltar para o menu transacoes\n\n", month_array, argv[1]);
                              while ((i = fgetc(stdin)) == '\n' || i == EOF){

                                 system("clear");
                                 fprintf(stdout, "\n>>> Menu listagem (%s/%s)\n\nEntre com a opcao desejada:\n\ne = listar debitos\ni = listar creditos\ns = listar reservas\nt = mostrar saldo total\nv = voltar para o menu transacoes\n\n", month_array, argv[1]);

                              }
                              while ((f = fgetc(stdin)) != '\n' && f != EOF){

			         i = 'z';

			      }
                              system("clear");

                              if ((i != 'v') && (i != 'w')){

                                 switch (i){

                                    case 'i': // listar transacoes de entrada (credito)

                                       if ((*node).balance != NULL){

                                          income = receipt = 0;
                                          t = '1';

                                          for (tr = (*node).balance; (tr != NULL);  tr = (*tr).next){

                                             if (((*tr).type == 'i') || ((*tr).type == 'o')){ //type 'o' sao transacoes de credito que nao sao contabilizadas nos calculos totais, pois o valor esta incluido em outras transacoes de credito

                                                fprintf(stdout, "\n");
						fprintf(stdout, "\033[0;36m> ");
                                                print_output(&(*tr).name);
						if ((*tr).type == 'o'){

						   fprintf(stdout, " (CREDITO INCLUIDO NO VALOR DE OUTRA TRANSACAO)");

						}
                                                fprintf(stdout, ":\033[0m\n");
						if ((*tr).type == 'i'){

                                                   income += StringToFloat(&(*tr).value, &correct);
                                                   receipt += StringToFloat(&(*tr).receipted, &correct);
                                                   t = '0';

						}
                                                fprintf(stdout, "\033[0;33m%-9s\033[0m", "  Valor:");
                                                fprintf(stdout, "\033[0;33m%-28.2f\033[0m", StringToFloat(&(*tr).value, &correct));
                                                fprintf(stdout, "\033[0;32m%-10s\033[0m", "Recebido:");
                                                fprintf(stdout, "\033[0;32m%-17.2f\033[0m", StringToFloat(&(*tr).receipted, &correct));
                                                fprintf(stdout, "\033[0;31m%-10s\033[0m", "Restante:");
                                                fprintf(stdout, "\033[0;31m%-17.2f\033[0m", StringToFloat(&(*tr).value, &correct) - StringToFloat(&(*tr).receipted, &correct));
						if ((StringToFloat(&(*tr).value, &correct) - StringToFloat(&(*tr).receipted, &correct)) <= 0.0){

                                                   fprintf(stdout, "\033[0;32m%-6s\033[0m\n","[ OK ]");

						} else {

						   fprintf(stdout, "\033[0;31m%-6s\033[0m\n", "[ .. ]");

						}

                                             }

                                          }

                                          if (t == '0'){

                                             fprintf(stdout, "\033[0;36m\n=================================================================================================\033[0m\n");
                                             fprintf(stdout, "\033[0;33m%-20s\033[0m", "# Total de credito:");
                                             fprintf(stdout, "\033[0;33m%-17.2f\033[0m", income);
                                             fprintf(stdout, "\033[0;32m%-10s\033[0m", "Recebido:");
                                             fprintf(stdout, "\033[0;32m%-17.2f\033[0m", receipt);
                                             fprintf(stdout, "\033[0;31m%-10s\033[0m", "Restante:");
                                             fprintf(stdout, "\033[0;31m%-17.2f\033[0m", (income - receipt));

					     if ((income - receipt) <= 0.0){

                                                fprintf(stdout, "\033[0;32m%-6s\033[0m\n","[ OK ]");

					     } else {

					        fprintf(stdout, "\033[0;31m%-6s\033[0m\n", "[ .. ]");

					     }

                                             fprintf(stdout, "\033[0;36m=================================================================================================\033[0m\n");

                                          } else {

                                             fprintf(stdout, "\nSem transacoes de credito!\n");

                                          }

                                       } else {

                                          fprintf(stdout, "\nSem transacoes de credito!\n");

                                       }

                                    break;

                                    case 'e': // listar transacoes de saida (debito)

                                       if ((*node).balance != NULL){

                                          expenses = receipt = 0;
                                          t = '1';

                                          for (tr = (*node).balance; (tr != NULL);  tr = (*tr).next){

                                             if (((*tr).type == 'e') || ((*tr).type == 'a')){ // type 'a' sao transacoes de debito que nao sao contabilizadas nos calculos totais, pois o valor esta incluido em outras transacoes de debito

                                                fprintf(stdout, "\n");
						fprintf(stdout, "\033[0;36m> ");
                                                print_output(&(*tr).name);
						if ((*tr).type == 'a'){

						   fprintf(stdout, " (DEBITO INCLUIDO NO VALOR DE OUTRA TRANSACAO)");

						}
                                                fprintf(stdout, ":\033[0m\n");
						if ((*tr).type == 'e'){
							
                                                   expenses += StringToFloat(&(*tr).value, &correct);
                                                   receipt += StringToFloat(&(*tr).receipted, &correct);
						   t = '0';

						}
                                                fprintf(stdout, "\033[0;33m%-9s\033[0m", "  Valor:");
                                                fprintf(stdout, "\033[0;33m%-28.2f\033[0m", StringToFloat(&(*tr).value, &correct));
                                                fprintf(stdout, "\033[0;32m%-9s\033[0m", "Quitado:");
                                                fprintf(stdout, "\033[0;32m%-18.2f\033[0m", StringToFloat(&(*tr).receipted, &correct));
                                                fprintf(stdout, "\033[0;31m%-10s\033[0m", "Restante:");
                                                fprintf(stdout, "\033[0;31m%-17.2f\033[0m", StringToFloat(&(*tr).value, &correct) - StringToFloat(&(*tr).receipted, &correct));

						if ((StringToFloat(&(*tr).value, &correct) - StringToFloat(&(*tr).receipted, &correct)) <= 0.0){

                                                   fprintf(stdout, "\033[0;32m%-6s\033[0m\n","[ OK ]");

						} else {

						   fprintf(stdout, "\033[0;31m%-6s\033[0m\n", "[ .. ]");

						}

                                             }

                                          }

                                          if (t == '0'){

                                             fprintf(stdout, "\033[0;36m\n=================================================================================================\033[0m\n");
                                             fprintf(stdout, "\033[0;33m%-19s\033[0m", "# Total de debito:");
                                             fprintf(stdout, "\033[0;33m%-18.2f\033[0m", expenses);
                                             fprintf(stdout, "\033[0;32m%-9s\033[0m", "Quitado:");
                                             fprintf(stdout, "\033[0;32m%-18.2f\033[0m", receipt);
                                             fprintf(stdout, "\033[0;31m%-10s\033[0m", "Restante:");
                                             fprintf(stdout, "\033[0;31m%-17.2f\033[0m", (expenses - receipt));

					     if ((expenses - receipt) <= 0.0){

                                                fprintf(stdout, "\033[0;32m%-6s\033[0m\n","[ OK ]");

					     } else {

					        fprintf(stdout, "\033[0;31m%-6s\033[0m\n", "[ .. ]");

					     }

                                             fprintf(stdout, "\033[0;36m=================================================================================================\033[0m\n");

                                          } else {

                                             fprintf(stdout, "\nSem transacoes de debito!\n");

                                          }

                                       } else {

                                          fprintf(stdout, "\nSem transacoes de debito!\n");

                                       }

                                    break;

                                    case 's': // listar transacoes de reserva

                                       if ((*node).balance != NULL){

                                          savings = receipt = 0;
                                          t = '1';

                                          for (tr = (*node).balance; (tr != NULL);  tr = (*tr).next){

                                             if ((*tr).type == 's'){

                                                savings_aux = receipt_aux = 0;

                                                for (node_aux = sheet; (node_aux != node); node_aux = (*node_aux).next){

                                                   if (((tr_aux = search_transaction(&(*node_aux).balance, &(*tr).name)) != NULL) && ((*tr_aux).type == 's')){

                                                      savings_aux += StringToFloat(&(*tr_aux).value, &correct);
                                                      receipt_aux += StringToFloat(&(*tr_aux).receipted, &correct);

                                                   }

                                                }

                                                fprintf(stdout, "\n");
						fprintf(stdout, "\033[0;36m> ");
                                                print_output(&(*tr).name);
                                                fprintf(stdout, ":\033[0m\n");
                                                savings += StringToFloat(&(*tr).value, &correct);
                                                receipt += StringToFloat(&(*tr).receipted, &correct);
                                                fprintf(stdout, "\033[0;33m%-9s\033[0m", "  Valor:");
                                                fprintf(stdout, "\033[0;33m%-28.2f\033[0m", StringToFloat(&(*tr).value, &correct));
                                                fprintf(stdout, "\033[0;32m%-11s\033[0m", "Reservado:");
                                                fprintf(stdout, "\033[0;32m%-16.2f\033[0m", StringToFloat(&(*tr).receipted, &correct));
                                                fprintf(stdout, "\033[0;31m%-10s\033[0m", "Restante:");
                                                fprintf(stdout, "\033[0;31m%-17.2f\033[0m", StringToFloat(&(*tr).value, &correct) - StringToFloat(&(*tr).receipted, &correct));
						if ((StringToFloat(&(*tr).value, &correct) - StringToFloat(&(*tr).receipted, &correct)) <= 0.0){

                                                   fprintf(stdout, "\033[0;32m%-6s\033[0m\n","[ OK ]");

						} else {

						   fprintf(stdout, "\033[0;31m%-6s\033[0m\n", "[ .. ]");

						}

						t = '0';

                                                if (savings_aux != 0){ // reservas de meses anteriores

                                                   fprintf(stdout, "\033[0;35m%-43s\033[0m", "* Planejado do inicio do ano ate este mes:");
                                                   fprintf(stdout, "\033[0;33m%-17.2f\033[0m\n", (StringToFloat(&(*tr).value, &correct) + savings_aux));
                                                   fprintf(stdout, "\033[0;35m%-43s\033[0m", "* Reservado do inicio do ano ate este mes:");
                                                   fprintf(stdout, "\033[0;32m%-17.2f\033[0m\n", (StringToFloat(&(*tr).receipted, &correct) + receipt_aux));

                                                }

                                             }

                                          }

                                          if (t == '0'){

                                             fprintf(stdout, "\033[0;36m\n=================================================================================================\033[0m\n");
                                             fprintf(stdout, "\033[0;33m%-21s\033[0m", "# Total de reservas:");
                                             fprintf(stdout, "\033[0;33m%-16.2f\033[0m", savings);
                                             fprintf(stdout, "\033[0;32m%-11s\033[0m", "Reservado:");
                                             fprintf(stdout, "\033[0;32m%-16.2f\033[0m", receipt);
                                             fprintf(stdout, "\033[0;31m%-10s\033[0m", "Restante:");
                                             fprintf(stdout, "\033[0;31m%-17.2f\033[0m", (savings - receipt));

					     if ((savings - receipt) <= 0.0){

                                                fprintf(stdout, "\033[0;32m%-6s\033[0m\n","[ OK ]");

					     } else {

					        fprintf(stdout, "\033[0;31m%-6s\033[0m\n", "[ .. ]");

					     }

                                             fprintf(stdout, "\033[0;36m=================================================================================================\033[0m\n");

                                          } else {

                                             fprintf(stdout, "\nSem transacoes de reserva!\n");

                                          }

                                       } else {

                                          fprintf(stdout, "\nSem transacoes de reserva!\n");

                                       }

                                    break;

                                    case 't': // mostrar saldo final total

                                       expenses = income = savings = income_aux = expenses_aux = savings_aux = 0;

                                       for (tr = (*node).balance; (tr != NULL); tr = (*tr).next){

                                          if ((*tr).type == 'i'){

                                             income += StringToFloat(&(*tr).value, &correct);
                                             income -= StringToFloat(&(*tr).receipted, &correct);
                                             income_aux += StringToFloat(&(*tr).value, &correct); // total a receber no mes

                                          } else if ((*tr).type == 'e'){

                                             expenses += StringToFloat(&(*tr).value, &correct);
                                             expenses -= StringToFloat(&(*tr).receipted, &correct);
                                             expenses_aux += StringToFloat(&(*tr).value, &correct);

                                          } else if ((*tr).type == 's'){

                                             savings += StringToFloat(&(*tr).value, &correct);
                                             savings -= StringToFloat(&(*tr).receipted, &correct);
                                             savings_aux += StringToFloat(&(*tr).value, &correct);

                                          }

                                       }

                                       fprintf(stdout, "\n\033[0;36m%-16s\033[0m", "Falta Receber:");
                                       fprintf(stdout, "\033[0;36m%-17.2f\033[0m\n", income);
                                       fprintf(stdout, "\033[0;31m%-16s\033[0m", "Falta pagar:");
                                       fprintf(stdout, "\033[0;31m%-17.2f\033[0m\n", expenses);
                                       fprintf(stdout, "\033[0;35m%-16s\033[0m", "Falta reservar:");
                                       fprintf(stdout, "\033[0;35m%-17.2f\033[0m\n", savings);
                                       fprintf(stdout, "\033[0;32m%-16s\033[0m", "Posso gastar:");
                                       fprintf(stdout, "\033[0;32m%-17.2f\033[0m\n", (income_aux - (expenses_aux + savings_aux)));

                                    break;

                                    default:

                                       fprintf(stderr, "\nEntrada invalida!\n");

                                 }

                              }

                           }

                        break;

                        case 'x':

                           while ((i != 's') && (i != 'n') && (i != 'v') && (i != 'w')){

                              fprintf(stdout, "\nTem certeza que deseja remover o mes (%s/%s)?\n\ns = sim\nn = nao\n\n", month_array, argv[1]);
                              while ((i = fgetc(stdin)) == '\n' || i == EOF){

                                 system("clear");
                                 fprintf(stdout, "\nTem certeza que deseja remover o mes (%s/%s)?\n\ns = sim\nn = nao\n\n", month_array, argv[1]);

                              }
                              while ((f = fgetc(stdin)) != '\n' && f != EOF){

			         i = 'z';

			      }
                              system("clear");

                              if (i == 's'){

                                 remove_balance_sheet_node(&sheet, &buffer);
                                 fprintf(stdout, "\nMes removido!\n");
                                 alterado = 1;

                              } else if ((i != 'n') && (i != 'v') && (i != 'w')){

                                 fprintf(stderr, "\nEntrada invalida!\n");

                              }

                           }

                           if (i == 's'){

                              i = 'm';

                           }

                        break;

                        case 'v':

                           i = 'm';

                        break;

                        default:

			   if (i != 'w'){

                              fprintf(stderr, "\nEntrada invalida!\n");

			   }

                     }

                  }

                  reinitialize(&buffer);

               }

            }

         break;

         case 's':

            write_balance_sheet(&sheet, argv[1]);
            fprintf(stdout, "\nPrograma Salvo!\n");
            alterado = 0;

         break;

         case 'v':

            fprintf(stdout, "\nVersao 1.3\nFinalizado em: 19 de Abril de 2021 as 16h46\nAutor: Vitor Vidal\n");

         break;

	 default:

	    if (i != 'w'){

               fprintf(stderr, "\nEntrada invalida!\n");
	    }

      }

   }

   if (alterado == 1){

      do {

         fprintf(stdout, "\nAlteracoes detectadas, deseja salva-las?\n\ns = sim\nn = nao\n\n");
         while ((i = fgetc(stdin)) == '\n' || i == EOF){

            system("clear");
            fprintf(stdout, "\nAlteracoes detectadas, deseja salva-las?\n\ns = sim\nn = nao\n\n");

         }

         while ((f = fgetc(stdin)) != '\n' && f != EOF){

	    i = 'z';

	 }

         system("clear");

         if ((i != 's') && (i != 'n')){

            fprintf(stderr, "\nEntrada invalida!\n");

         }

      } while ((i != 's') && (i != 'n'));

      if (i == 's'){

         write_balance_sheet(&sheet, argv[1]);
         fprintf(stdout, "\nPrograma salvo!\n");

      }

   }

   reinitialize_balance_sheet(&sheet);
   fprintf(stdout, "\nPrograma finalizado!\n\n");

   return 0;

}


