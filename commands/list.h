char findField(char *field, Campos **campos);

void liststructure(dBase *dbAtual, dUnidade *unid);
void list(dUnidade *unid);
void listforname(char *parm, dUnidade *unidAt);

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

void list(dUnidade *unid) {
    if (unid == NULL || unid->Campos == NULL) {
        printf("Nenhuma unidade ou campos dispon?veis.\n");
    }
    else{
    	
	    Campos *auxCampos = unid->Campos;
	
	    // Imprime os nomes das colunas (cabe?alho)
	    while (auxCampos != NULL) {
	        printf("%s\t", auxCampos->FieldName);
	        auxCampos = auxCampos->prox;
	    }
	    printf("\n");
	
	    // Reinicializa auxCampos para percorrer novamente
	    auxCampos = unid->Campos;
	
	    // Verifica se ha dados
	    if (auxCampos->Pdados == NULL) {
	        printf("Nenhum dado dispon?vel.\n");
	    }
	    else{
	    	// Percorrer os registros (considerando que cada campo tem sua lista de dados)
		    int continuar = 1;
		    while (continuar) {
		        continuar = 0; // Assume que nao ha mais registros
		
		        Campos *campoAtual = unid->Campos;
                
                while (campoAtual != NULL) {
                    campoAtual->Patual = campoAtual->Pdados;
                    campoAtual = campoAtual->prox;
                }
                
                campoAtual = unid->Campos;
		        while (campoAtual != NULL) {
		            if (campoAtual->Patual != NULL) {
		                continuar = 1; // Ainda ha registros para imprimir
		
		                switch (campoAtual->Type) {
		                    case 'N': printf("%.2f\t", campoAtual->Patual->Valor.N); break;
		                    case 'D': printf("%s\t", campoAtual->Patual->Valor.D); break;
		                    case 'L': printf("%d\t", campoAtual->Patual->Valor.L); break;
		                    case 'C': printf("%s\t", campoAtual->Patual->Valor.C); break;
		                    case 'M': printf("%s\t", campoAtual->Patual->Valor.M); break;
		                    default: printf("?\t"); break;
		                }
		
		                // Avan?a para o pr?ximo dado na lista do campo
		                campoAtual->Patual = campoAtual->Patual->prox;
		            } else {
		                printf("\t"); // Preenchendo espa?os para colunas vazias
		            }
		            campoAtual = campoAtual->prox;
		        }
		        printf("\n");
		    }
		
		    // Resetando os ponteiros Patual para o in?cio da lista de cada campo
		    auxCampos = unid->Campos;
		    while (auxCampos != NULL) {
		        auxCampos->Patual = auxCampos->Pdados;
		        auxCampos = auxCampos->prox;
		    }	
	    }
    }
}

void listfor(char *parm, dUnidade *unidAt) {
    Campos *campos;
    char filterField[MAXNAME], filter[MAXNAME];
    int i = 0, j = 0;
    
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
            
            // Imprimir cabecalhos das colunas
            Campos *auxCampos = unidAt->Campos;
            while (auxCampos != NULL) {
                printf("%s\t", auxCampos->FieldName);
                auxCampos = auxCampos->prox;
            }
            printf("\n");
            
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
                    auxCampos = unidAt->Campos;
                    while (auxCampos != NULL) {
                        if (auxCampos->Patual != NULL) {
                            switch (auxCampos->Type) {
                                case 'N': printf("%.2f\t", auxCampos->Patual->Valor.N); break;
                                case 'D': printf("%s\t", auxCampos->Patual->Valor.D); break;
                                case 'L': printf("%d\t", auxCampos->Patual->Valor.L); break;
                                case 'C': printf("%s\t", auxCampos->Patual->Valor.C); break;
                                case 'M': printf("%s\t", auxCampos->Patual->Valor.M); break;
                                default: printf("?\t"); break;
                            }
                        }
                        auxCampos = auxCampos->prox;
                    }
                    printf("\n");
                }
                
                if (campos->Patual != NULL) {
                    campos->Patual = campos->Patual->prox;
                }
                campos = campos->prox;
                findField(filterField, &campos);
            }
            
            // Resetar ponteiro para o in?cio da lista
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

