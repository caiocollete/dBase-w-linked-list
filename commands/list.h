void liststructure(dBase *dbAtual, dUnidade *unid, char *value);

void liststructure(dBase *dbAtual, dUnidade *unid, char *value){
    int dataRecords=0;
    Campos *aux = unid->Campos;
    Pdados *auxp;
    
    printf("-List Structure\n");
    printf("Structure for database: %s%s",dbAtual->disco, unid->NomeDBF);
    
    while(aux!=NULL){
        auxp=aux->Pdados;
        while(auxp!=NULL){
            dataRecords++;
            auxp=auxp->prox;
        }
    }
    printf("Number of data records: %d\n", dataRecords);
    printf("Date of last update: %s\n", unid->Data);
    printf("Field\tFieldName\tType\tWidth\tDec\n");
    aux=unid->Campos; dataRecords=1;
    while(aux!=NULL){
        printf("%d\t%s\t%c\t%d\t%d\n", dataRecords, unid->FieldName, unid->Type, unid->Width, unid->Dec);
        dataRecords++;
    }
}
