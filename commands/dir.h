void dir(dBase *db){
	if(db!=NULL){
		dUnidade *unidade = db->unidade;
	    if(unidade!=NULL){
	        while(unidade!=NULL){
	            printf("> %s\n", unidade->NomeDBF);
	            unidade = unidade->prox;
	        }
	    }
	    else
			printf("UNIT is NULL");
	}
	else
		printf("DB isn't defined");
}
