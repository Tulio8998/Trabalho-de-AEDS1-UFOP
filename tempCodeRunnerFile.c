printf("\nDigite o NOME do EVENTO: ");
                                            fgets(nome, sizeof(nome), stdin);
                                            nome[strcspn(nome, "\n")] = '\0';
                                            TEvento* evento = Pesquisar_evento_nome(&pesquisa->item, nome);
                                            if (evento != NULL) {
                                                printf("Foi encontrado o EVENTO [%s] na CIDADE [%s]\n", evento->nome_evento, pesquisa->item.nome_cidade);
                                            } else {
                                                printf("O EVENTO [%s] não foi encontrado na CIDADE [%s]\n", nome, pesquisa->item.nome_cidade);
                                            }