void use(dBase *atual, dUnidade **unidade, char *target){
    if(atual!=NULL){
        dUnidade *aux = *uniddade;
        while(aux!=NULL && strcmp(aux->NomeDBF, target)!=0)
            aux = aux->prox;
        if(aux!=NULL){
            *unidade=aux;
            printf("[%s] was setted", target);
        }
        else
            printf("[%s] was not found", target);
        sleep(3);
    }
}
