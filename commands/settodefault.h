void setDefault(dBase **dbase, char *disco, dBase **dbAtual){
    dBase *novo, *aux;
    novo= (dBase*)malloc(sizeof(dBase));
    novo->ant = NULL;
    novo->prox = NULL;
    strcpy(novo->disco, disco);
    novo->unidade=NULL;
    if(*dbase==NULL){
        *dbase=novo;
    }
    else{
        aux = *dbase;
        while(strcmp(aux->disco, disco)!=0 && aux->prox!=NULL){
            aux=aux->prox;
        }
        if(strcmp(aux->disco, disco)==0){ // ACHOU O DISCO, OU SEJA, ELE JA ESTA ADICIONADO
            *dbAtual = aux;
        }
        else{ // NAO ACHOU O DISCO
            *dbase = novo;
            *dbAtual = *dbase;
        }
    }
}
