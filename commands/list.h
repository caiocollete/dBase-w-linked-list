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



void list(dUnidade *unid){
    Campos *auxCampos = unid->Campos;
    Pdados *auxPdados = auxCampos->Pdados;
    int counter = 0; // conta as linhas
    int i; // ira interar ate o valor de counter
    
    while(auxCampos!=NULL){
        printf("%s\t", auxCampos->FieldName);
    }
    printf("\n");
    
    auxCampos= unid->Campos;
    while(auxPdados!=NULL){
        if(auxCampos!=NULL){
            for(i = 0; i < counter; i++){
                auxPdados->prox;
            }
            if(auxPdados!=NULL){
                switch(auxCampos->Type){
                    case 'N': printf("%f\t", auxPdados->dados.F);  break;
                    case 'D': printf("%s\t", auxPdados->dados.D); break;
                    case 'L': printf("%d\t", auxPdados->dados.L); break;
                    case 'C': printf("%s\t", auxPdados->dados.C); break;
                    case 'M': printf("%s\t", auxPdados->dados.M); break;
                }
                auxCampos=auxCampos->prox;
                counter++;
            }
        }
        else{
            auxCampos = unid->Campos;
        }
    }
    
}
