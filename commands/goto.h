void gotoo(dUnidade *unidade, char target[MAXCOMMAND]){
    // vai causar bug em outros finds list e listfor
    if(unidade!=NULL){
        Campos *campos = unidade->Campos;
        int i = atoi(target);
        int j;

        // posicionar Patual no comeco
        while (campos != NULL) {
            campos->Patual = campos->Pdados;
            campos = campos->prox;
        }
        
        // posicionar Patual no target
        campos = unidade->Campos;
        while(campos!=NULL){
            for(j=1; j<i; j++){
                campos->Patual = campos->Patual->prox;
            }
            campos=campos->prox;
        }
        
        printf("\n%d\n", i);
    }
}
