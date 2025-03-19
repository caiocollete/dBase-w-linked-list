void append(dUnidade **unidade) {
    if (*unidade == NULL) {
        printf("Define a DB to use\nYou can define with 'USE name.dbf'\n");
    } else {
        Campos *auxCampos = (*unidade)->Campos;
        int exit = 0;
        Status *novoStatus = NULL;
        Pdados *dadosTemp[MAXFIELDNAME];
        int count = 0,i;

        novoStatus = (Status*)malloc(sizeof(Status));
        if (novoStatus == NULL) {
            printf("Erro de memoria!\n");
            exit = 1;
        } 
		else {
            novoStatus->Status = 'A';
            novoStatus->prox = NULL;
            
            while (auxCampos != NULL && !exit) {
                Pdados *novoDado = (Pdados*)malloc(sizeof(Pdados));
                if (novoDado == NULL) {
                    printf("Erro de memoria!\n");
                    exit = 1;
                } 
				else {
                    novoDado->prox = NULL;
                    printf("%s: ", auxCampos->FieldName);
                    
                    switch (auxCampos->Type) {
                        case 'N':
                            if (scanf("%f", &novoDado->Valor.N) != 1) {
                                printf("Valor invalido!\n");
                                free(novoDado);
                                exit = 1;
                            }
                            break;
                        case 'D':
                            printf("(DD/MM/YYYY) ");
                            fflush(stdin);
                            fgets(novoDado->Valor.D, MAXDATA, stdin);
                            novoDado->Valor.D[strcspn(novoDado->Valor.D, "\n")] = '\0';
                            break;
                        case 'L':
                            if (scanf("%d", &novoDado->Valor.L) != 1) {
                                printf("Valor invalido!\n");
                                free(novoDado);
                                exit = 1;
                            }
                            break;
                        case 'C':
                            fflush(stdin);
                            fgets(novoDado->Valor.C, MAXBYTES, stdin);
                            novoDado->Valor.C[strcspn(novoDado->Valor.C, "\n")] = '\0';
                            break;
                        case 'M':
                            fflush(stdin);
                            fgets(novoDado->Valor.M, MAXBYTES, stdin);
                            novoDado->Valor.M[strcspn(novoDado->Valor.M, "\n")] = '\0';
                            break;
                        default:
                            printf("Tipo desconhecido!\n");
                            free(novoDado);
                            exit = 1;
                    }

                    if (!exit) {
                        dadosTemp[count++] = novoDado;
                        auxCampos = auxCampos->prox;
                    } 
					else {
                        free(novoDado);
                    }
                }
            }

            if (!exit) {
                if ((*unidade)->Status == NULL) {
                    (*unidade)->Status = novoStatus;
                } 
				else {
                    Status *ultimoStatus = (*unidade)->Status;
                    while (ultimoStatus->prox != NULL) {
                        ultimoStatus = ultimoStatus->prox;
                    }
                    ultimoStatus->prox = novoStatus;
                }

                Campos *campoAtual = (*unidade)->Campos;
                for (i = 0; i < count; i++) {
                    if (campoAtual->Pdados == NULL) {
                        campoAtual->Pdados = dadosTemp[i];
                        campoAtual->Patual = dadosTemp[i];
                    } else {
                        Pdados *ultimoDado = campoAtual->Pdados;
                        while (ultimoDado->prox != NULL) {
                            ultimoDado = ultimoDado->prox;
                        }
                        ultimoDado->prox = dadosTemp[i];
                    }
                    campoAtual = campoAtual->prox;
                }
            } 
			else {
                free(novoStatus);
                for (i = 0; i < count; i++) {
                    free(dadosTemp[i]);
                }
            }
        }
    }
}
