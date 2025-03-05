void liststructure(dBase *dbAtual, dUnidade *unid);

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
        printf("Nenhuma unidade ou campos disponíveis.\n");
    }
    else{
    	
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
	    else{
	    	// Percorrer os registros (considerando que cada campo tem sua lista de dados)
		    int continuar = 1;
		    while (continuar) {
		        continuar = 0; // Assume que não há mais registros
		
		        Campos *campoAtual = unid->Campos;
		        while (campoAtual != NULL) {
		            if (campoAtual->Patual != NULL) {
		                continuar = 1; // Ainda há registros para imprimir
		
		                switch (campoAtual->Type) {
		                    case 'N': printf("%.2f\t", campoAtual->Patual->Valor.N); break;
		                    case 'D': printf("%s\t", campoAtual->Patual->Valor.D); break;
		                    case 'L': printf("%d\t", campoAtual->Patual->Valor.L); break;
		                    case 'C': printf("%s\t", campoAtual->Patual->Valor.C); break;
		                    case 'M': printf("%s\t", campoAtual->Patual->Valor.M); break;
		                    default: printf("?\t"); break;
		                }
		
		                // Avança para o próximo dado na lista do campo
		                campoAtual->Patual = campoAtual->Patual->prox;
		            } else {
		                printf("\t"); // Preenchendo espaços para colunas vazias
		            }
		            campoAtual = campoAtual->prox;
		        }
		        printf("\n");
		    }
		
		    // Resetando os ponteiros Patual para o início da lista de cada campo
		    auxCampos = unid->Campos;
		    while (auxCampos != NULL) {
		        auxCampos->Patual = auxCampos->Pdados;
		        auxCampos = auxCampos->prox;
		    }	
	    }
    }
}
