void dir(dBase db){
    dUnidade *unidade = db->unidade;
    if(unidade!=NULL){
        while(unidade!=NULL){
            printf("%s", unidade->NameDBF);
            unidade = unidade->prox;
        }
    }
}
