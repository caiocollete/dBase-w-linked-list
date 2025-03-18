// locate for <fieldName> = <parameter>

void locate(char *parm, dUnidade *unidAt) {
    Campos *campos;
    char filterField[MAXNAME], filter[MAXNAME];
    int i = 0, j = 0, count=0;
    
    // Encontrar o '=' na string
    while (parm[i] != '=' && parm[i] != '\0') {
        i++;
    }
    
    if (parm[i] == '=') {
        // Copiar o nome do campo (removendo espacos extras)
        while (j < i && parm[j] == ' ') {
            j++;
        }
        strncpy(filterField, parm + j, i - j);
        filterField[i - j] = '\0';
        
        // Copiar o valor do filtro (removendo espacos extras)
        i++;
        while (parm[i] == ' ') {
            i++;
        }
        strcpy(filter, parm + i);
        
        campos = unidAt->Campos;
        
        if (findField(filterField, &campos)) {
            int aux;
            float value;
                      
			// posicionando patual no inicio  
            auxCampos = unidAt->Campos;
            while (auxCampos != NULL) {
                auxCampos->Patual = auxCampos->Pdados;
                auxCampos = auxCampos->prox;
            }
            
            while (campos != NULL) {
                aux = 0;
                char fieldAux[MAXNAME];
                if (campos->Patual != NULL) {
                    switch (campos->Type) {
                        case 'N':
                            value = atof(filter);
                            aux = (campos->Patual->Valor.N == value);
                            break;
                        case 'D':
                        	strcpy(fieldAux,campos->Patual->Valor.D);
                        	to_upper_str(fieldAux);
                            aux = (strcmp(fieldAux, filter) == 0);
                            break;
                        case 'L':
                            aux = (campos->Patual->Valor.L == atoi(filter));
                            break;
                        case 'C':
                        	strcpy(fieldAux,campos->Patual->Valor.C);
                        	to_upper_str(fieldAux);
                            aux = (strcmp(fieldAux, filter) == 0);
                            break;
                        case 'M':
                        	strcpy(fieldAux,campos->Patual->Valor.M);
                        	to_upper_str(fieldAux);
                            aux = (strcmp(fieldAux, filter) == 0);
                            break;
                    }
                }
                
                if (aux) {
                    count++;
                }
                
                if (campos->Patual != NULL) {
                    campos->Patual = campos->Patual->prox;
                }
                campos = campos->prox;
                findField(filterField, &campos);
            }
            
            printf("Record - %d", count);
            
            // Resetar ponteiros para o inicio da lista
            campos = unidAt->Campos;
            while (campos != NULL) {
                campos->Patual = campos->Pdados;
                campos = campos->prox;
            }
        } 
		else {
            printf("Field not found\n");
        }
    } else {
        printf("Has missing parameters\n");
    }
}
