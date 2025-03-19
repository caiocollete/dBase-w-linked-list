// locate for <fieldName> = <parameter>

void locate(char *parm, dUnidade *unidAt, char viewDelete) {
    Campos *campos;
    Status *statusAtual;
    char filterField[MAXNAME], filter[MAXNAME];
    int i = 0, j = 0, count = 0;
    
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
        
        statusAtual = unidAt->Status;
        // Localizar o campo filtrado
        campos = unidAt->Campos;
        if (findField(filterField, &campos)) {
            float value;
            
            // Resetar ponteiros para o início da lista de cada campo
            Campos *auxCampos = unidAt->Campos;
            while (auxCampos != NULL) {
                auxCampos->Patual = auxCampos->Pdados;
                auxCampos = auxCampos->prox;
            }
            
            // Percorrer todos os registros
            int encontrou = 0;
            while (campos->Patual != NULL) {
                int aux = 0;
                char fieldAux[MAXNAME];
                
                switch (campos->Type) {
                    case 'N':
                        value = atof(filter);
                        aux = (campos->Patual->Valor.N == value);
                        break;
                    case 'D':
                        strcpy(fieldAux, campos->Patual->Valor.D);
                        to_upper_str(fieldAux);
                        aux = (strcmp(fieldAux, filter) == 0);
                        break;
                    case 'L':
                        aux = (campos->Patual->Valor.L == atoi(filter));
                        break;
                    case 'C':
                        strcpy(fieldAux, campos->Patual->Valor.C);
                        to_upper_str(fieldAux);
                        aux = (strcmp(fieldAux, filter) == 0);
                        break;
                    case 'M':
                        strcpy(fieldAux, campos->Patual->Valor.M);
                        to_upper_str(fieldAux);
                        aux = (strcmp(fieldAux, filter) == 0);
                        break;
                }
                
                if (aux && (viewDelete || statusAtual->Status=='A')) {
                    count++;
                    encontrou = 1;
                }
                
                // Avançar para o próximo registro
                Campos *campoAvancar = unidAt->Campos;
                while (campoAvancar != NULL) {
                    if (campoAvancar->Patual != NULL) {
                        campoAvancar->Patual = campoAvancar->Patual->prox;
                    }
                    campoAvancar = campoAvancar->prox;
                }
                statusAtual=statusAtual->prox;
            }
            
            if (!encontrou) {
                printf("Nenhum registro encontrado.\n");
            } else {
                printf("Total de registros encontrados: %d\n", count);
            }
            
            // Resetar ponteiros para o início da lista
            auxCampos = unidAt->Campos;
            while (auxCampos != NULL) {
                auxCampos->Patual = auxCampos->Pdados;
                auxCampos = auxCampos->prox;
            }
        } else {
            printf("Field not found\n");
        }
    } else {
        printf("Has missing parameters\n");
    }
}

