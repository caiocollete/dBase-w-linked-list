void use(dBase *atual, dUnidade **unidade, char *target){
    if(atual!=NULL){
    	if(*unidade!=NULL){
    		dUnidade *aux = *unidade;
	        char nameDBF[MAXNAME];
	        strcpy(nameDBF, aux->NomeDBF);
	        to_upper_str(nameDBF);
	        if(strcmp(nameDBF, target)!=0){
	        	aux = aux->prox;
	        	while(aux!=NULL && strcmp(nameDBF, target)!=0){
	        		strcpy(nameDBF, aux->NomeDBF);
	        		to_upper_str(nameDBF);
	        		if(strcmp(nameDBF, target)!=0)
	        			aux = aux->prox;
	        	}
	        }
	        if(aux!=NULL){
	            *unidade=aux;
	            printf("[%s] was setted", target);
	        }
	        else
	            printf("[%s] was not found", target);
    	}
        else
        	printf("UNIT isn't DEFINED\n");
    }
    else
    	printf("DB isn't DEFINED\n");
}
