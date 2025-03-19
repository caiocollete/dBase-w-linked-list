char findField(char *field, Campos **campos);

void liststructure(dBase *dbAtual, dUnidade *unid);
void list(dUnidade *unid, char viewDelete);
void listfor(char *parm, dUnidade *unidAt, char viewDelete);

void liststructure(dBase *dbAtual, dUnidade *unid){
    int dataRecords=0, widthsum=0;
    Campos *aux = unid->Campos;
    Pdados *auxp;
    
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    
    printf(". List Structure\n");
    printf("Structure for database: %s%s\n",dbAtual->disco, unid->NomeDBF);
    
    while (aux != NULL) {
        aux->Patual = aux->Pdados;
        aux = aux->prox;
    }
    
    aux = unid->Campos;
    while(aux!=NULL){
        auxp=aux->Pdados;
        while(auxp!=NULL){
            dataRecords++;
            auxp=auxp->prox;
        }
        aux=aux->prox;
    }
    printf("Number of data records: %d\n", dataRecords);
    printf("Date of last update: %s\n", unid->Data);
    printf("Field\tFieldName\tType\tWidth\tDec\n");
    aux=unid->Campos; dataRecords=1;
    while(aux!=NULL){
        printf("%d\t%s\t", dataRecords, aux->FieldName);
        switch(aux->Type){
        	case 'N': printf("Numeric\t");  break;
        	case 'D': printf("Date\t"); break;
        	case 'L': printf("Logical\t"); break;
        	case 'C': printf("Character\t"); break;
        	case 'M': printf("Memo\t"); break;
        }
        printf("%d\t%d\n", aux->Width, aux->Dec);
        
        widthsum+=aux->Width;
        dataRecords++;
        aux=aux->prox;
    }
    printf("** TOTAL **\t\t\t%d", widthsum);
}

void list(dUnidade *unid, char viewDelete) {
    if (unid == NULL || unid->Campos == NULL) {
        printf("Nenhuma unidade ou campos disponíveis.\n");
    }
    else {
        Campos *auxCampos = unid->Campos;

        // Imprime os nomes das colunas (cabeçalho)
        while (auxCampos != NULL) {
            printf("%s\t", auxCampos->FieldName);
            auxCampos = auxCampos->prox;
        }
        printf("\n");

        // Reinicializa auxCampos para percorrer novamente
        auxCampos = unid->Campos;

        // Verifica se há dados
        if (auxCampos->Pdados == NULL) {
            printf("Nenhum dado disponível.\n");
        }
        else {
            
            Status *statusAtual = unid->Status;
            Campos *campoAtual = unid->Campos;
            // Inicializar ponteiros para o início dos dados de cada campo
            while (campoAtual != NULL) {
                campoAtual->Patual = campoAtual->Pdados;
                campoAtual = campoAtual->prox;
            }

            // Percorre e imprime os registros
            int continuar = 1;
            while (continuar) {
                continuar = 0; // Assume que nao ha mais registros

                campoAtual = unid->Campos;
                while (campoAtual != NULL) {
                    if (campoAtual->Patual != NULL && (viewDelete || statusAtual->Status=='A')) {
                        continuar = 1; // Ainda ha registros para imprimir

                        switch (campoAtual->Type) {
                            case 'N': printf("%.2f\t", campoAtual->Patual->Valor.N); break;
                            case 'D': printf("%s\t", campoAtual->Patual->Valor.D); break;
                            case 'L': printf("%d\t", campoAtual->Patual->Valor.L); break;
                            case 'C': printf("%s\t", campoAtual->Patual->Valor.C); break;
                            case 'M': printf("%s\t", campoAtual->Patual->Valor.M); break;
                            default: printf("?\t"); break;
                        }

                        // Avanca para o proximo dado na lista do campo
                        campoAtual->Patual = campoAtual->Patual->prox;
                        statusAtual=statusAtual->prox;
                    }
                    else {
                        printf("\t"); // Preenchendo espacos para colunas vazias
                    }
                    campoAtual = campoAtual->prox;
                }
                printf("\n");
            }

            // Resetando os ponteiros Patual para o inicio da lista de cada campo
            auxCampos = unid->Campos;
            while (auxCampos != NULL) {
                auxCampos->Patual = auxCampos->Pdados;
                auxCampos = auxCampos->prox;
            }
        }
    }
}

void listfor(char *parm, dUnidade *unidAt, char viewDelete) {
    Campos *campos;
    Status *statusAtual;
    char filterField[MAXNAME], filter[MAXNAME];
    int i = 0, j = 0;
    
    // Encontrar o '=' na string
    while (parm[i] != '=' && parm[i] != '\0') {
        i++;
    }
    
    if (parm[i] == '=') {
        // Copiar o nome do campo (removendo espaços extras)
        while (j < i && parm[j] == ' ') {
            j++;
        }
        strncpy(filterField, parm + j, i - j);
        filterField[i - j] = '\0';
        
        // Copiar o valor do filtro (removendo espaços extras)
        i++;
        while (parm[i] == ' ') {
            i++;
        }
        strcpy(filter, parm + i);
        
        campos = unidAt->Campos;
        statusAtual = unidAt->Status;
        
        if (findField(filterField, &campos)) {
            float value;
            
            // Imprimir cabeçalhos das colunas
            Campos *auxCampos = unidAt->Campos;
            while (auxCampos != NULL) {
                printf("%s\t", auxCampos->FieldName);
                auxCampos = auxCampos->prox;
            }
            printf("\n");

            // Resetar ponteiros para o inicio da lista de cada campo
            auxCampos = unidAt->Campos;
            while (auxCampos != NULL) {
                auxCampos->Patual = auxCampos->Pdados;
                auxCampos = auxCampos->prox;
            }

            // Percorrer todos os registros
            int continuar = 1;
            while (continuar) {
                continuar = 0;  // Assume que nao ha mais registros
                
                Campos *campoAtual = unidAt->Campos;
                int encontrado = 0;

                // Verifica se algum campo ainda tem registros
                while (campoAtual != NULL) {
                    if (campoAtual->Patual != NULL) {
                        continuar = 1;
                    }
                    campoAtual = campoAtual->prox;
                }

                // Se nao ha mais registros, sair do loop
                if !continuar) {
                    // Verificar se o registro atual do campo filtrado atende a condicao
                    if (campos->Patual != NULL) {
                        switch (campos->Type) {
                            case 'N':
                                value = atof(filter);
                                encontrado = (campos->Patual->Valor.N == value);
                                break;
                            case 'D': {
                                char fieldAux[MAXNAME];
                                strcpy(fieldAux, campos->Patual->Valor.D);
                                to_upper_str(fieldAux);
                                encontrado = (strcmp(fieldAux, filter) == 0);
                                break;
                            }
                            case 'L':
                                encontrado = (campos->Patual->Valor.L == atoi(filter));
                                break;
                            case 'C': {
                                char fieldAux[MAXNAME];
                                strcpy(fieldAux, campos->Patual->Valor.C);
                                to_upper_str(fieldAux);
                                encontrado = (strcmp(fieldAux, filter) == 0);
                                break;
                            }
                            case 'M': {
                                char fieldAux[MAXNAME];
                                strcpy(fieldAux, campos->Patual->Valor.M);
                                to_upper_str(fieldAux);
                                encontrado = (strcmp(fieldAux, filter) == 0);
                                break;
                            }
                        }
                    }

                    // Se o registro corresponde ao filtro, imprimir todos os campos da linha
                    if (encontrado && (viewDelete || statusAtual->Status=='A')) {
                        campoAtual = unidAt->Campos;
                        while (campoAtual != NULL) {
                            if (campoAtual->Patual != NULL) {
                                switch (campoAtual->Type) {
                                    case 'N': printf("%.2f\t", campoAtual->Patual->Valor.N); break;
                                    case 'D': printf("%s\t", campoAtual->Patual->Valor.D); break;
                                    case 'L': printf("%d\t", campoAtual->Patual->Valor.L); break;
                                    case 'C': printf("%s\t", campoAtual->Patual->Valor.C); break;
                                    case 'M': printf("%s\t", campoAtual->Patual->Valor.M); break;
                                    default: printf("?\t"); break;
                                }
                            } else {
                                printf("\t");
                            }
                            campoAtual = campoAtual->prox;
                        }
                        printf("\n");
                    }

                    // Avancar para o proximo registro em cada campo
                    campoAtual = unidAt->Campos;
                    while (campoAtual != NULL) {
                        if (campoAtual->Patual != NULL) {
                            campoAtual->Patual = campoAtual->Patual->prox;
                        }
                        campoAtual = campoAtual->prox;
                    }
                    statusAtual=statusAtual->prox;
                }
            }

            // Resetar ponteiros para o início da lista de cada campo
            auxCampos = unidAt->Campos;
            while (auxCampos != NULL) {
                auxCampos->Patual = auxCampos->Pdados;
                auxCampos = auxCampos->prox;
            }
        }
        else {
            printf("Field not found\n");
        }
    }
    else {
        printf("Has missing parameters\n");
    }
}


char findField(char *field, Campos **campos) {
    Campos *auxCampos = *campos;
    char fieldName[MAXNAME];

    while (auxCampos != NULL) {
        strcpy(fieldName, auxCampos->FieldName);
        to_upper_str(fieldName); // Normaliza para maiusculas
        
        if (strcmp(fieldName, field) == 0) {
            *campos = auxCampos;
            return 1; // Campo encontrado
        }
        
        auxCampos = auxCampos->prox;
    }
    
    return 0; // Campo nao encontrado
}

