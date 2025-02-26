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
    else {
        Campos *auxCampos = unid->Campos;

        // Imprime os nomes das colunas (cabeçalho)
        while (auxCampos != NULL) {
            printf("%s\t", auxCampos->FieldName);
            auxCampos = auxCampos->prox;
        }
        printf("\n");

        int temDados = 1; // Flag para indicar se há mais registros para imprimir
        while (temDados) {
            temDados = 0; // Assume que não há mais dados a menos que encontre algum
            
            auxCampos = unid->Campos;
            while (auxCampos != NULL) {
                if (auxCampos->Pdados != NULL) {
                    temDados = 1; // Ainda há dados para imprimir

                    switch (auxCampos->Type) {
                        case 'N': printf("%f\t", auxCampos->Pdados->Valor.N); break;
                        case 'D': printf("%s\t", auxCampos->Pdados->Valor.D); break;
                        case 'L': printf("%d\t", auxCampos->Pdados->Valor.L); break;
                        case 'C': printf("%s\t", auxCampos->Pdados->Valor.C); break;
                        case 'M': printf("%s\t", auxCampos->Pdados->Valor.M); break;
                        default: printf("?\t"); break;
                    }

                    // Avança para o próximo dado no campo
                    auxCampos->Pdados = auxCampos->Pdados->prox;
                }
                auxCampos = auxCampos->prox;
            }
            printf("\n");
        }
    }
}
