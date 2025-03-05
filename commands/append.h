void append(dUnidade **unidade) {
    if (*unidade == NULL) {
        printf("Define a DB to use\nYou can define with 'USE name.dbf'\n");
    }
    else {
        Campos *aux = (*unidade)->Campos;
        
        while (aux != NULL) {
            Pdados *novo = (Pdados *)malloc(sizeof(Pdados));
            if (novo == NULL) {
                printf("Error about memory!\n");
            }
            else {
                novo->prox = NULL;
                int exit = 0; // Variavel para controle de erro
                
                printf("%s: ", aux->FieldName);
                
                switch (aux->Type) {
                    case 'N':
                        if (scanf("%f", &novo->Valor.N) != 1) {
                            printf("Error: Entrada invalida para numero!\n");
                            free(novo);
                            exit = 1;
                        }
                        break;
                    case 'D':
                        printf("(00/00/0000) ");
                        fgets(novo->Valor.D, sizeof(novo->Valor.D), stdin);
                        novo->Valor.D[strcspn(novo->Valor.D, "\n")] = '\0'; // Remove '\n'
                        break;
                    case 'L':
                        if (scanf("%d", &novo->Valor.L) != 1) {
                            printf("Error: Entrada invalida para logico!\n");
                            free(novo);
                            exit = 1;
                        }
                        break;
                    case 'C':
                        while (getchar() != '\n'); // Limpa buffer antes de fgets
                        fgets(novo->Valor.C, sizeof(novo->Valor.C), stdin);
                        novo->Valor.C[strcspn(novo->Valor.C, "\n")] = '\0'; // Remove '\n'
                        break;
                    case 'M':
                        while (getchar() != '\n'); // Limpa buffer antes de fgets
                        fgets(novo->Valor.M, sizeof(novo->Valor.M), stdin);
                        novo->Valor.M[strcspn(novo->Valor.M, "\n")] = '\0'; // Remove '\n'
                        break;
                    default:
                        printf("Tipo desconhecido!\n");
                        free(novo);
                        exit = 1;
                }

                if (!exit) { // Apenas adiciona se não houver erro
                    if (aux->Pdados == NULL) {
                        aux->Pdados = novo;
                        aux->Patual = novo;
                    } 
					else {
                        Pdados *auxDados = aux->Pdados;
                        while (auxDados->prox != NULL) {
                            auxDados = auxDados->prox;
                        }
                        auxDados->prox = novo;
                    }
                }
            }
            aux = aux->prox; // Avança para o próximo campo
        }
    }
}
