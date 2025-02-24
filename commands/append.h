void append(dUnidade **unidade){
    Campos *aux;
    Pdados *novo, *auxDados;
    if(*unidade!=NULL){
    	printf("Define an DB to use\n You can define with 'USE name.dbf'\n");
    }
    else{
    	float N;
    	char D[MAXDATA];
		int L;
    	char C[MAXBYTES];
    	char M[MAXBYTES];
    	
    	aux = (*unidade)->Campos;
    	auxDados = aux->Pdados;
    	while(aux!=NULL){
    		novo = (Pdados*)malloc(sizeof(Pdados));
    	
			printf("%s: ", aux->FieldName);
    		switch(aux->Type){
	    		case 'N': scanf("&f", N); novo->Valor.N = N; break;
	    		case 'D': printf("(00/00/0000) "); fgets(D, sizeof(D), stdin); strcpy(novo->Valor.D, D); break;
	    		case 'L': printf("(0/1) "); scanf("&d", L); novo->Valor.L = L; break;
	    		case 'C': fgets(C, sizeof(C), stdin); strcpy(novo->Valor.C, C); break;
	    		case 'M': fgets(M, sizeof(M), stdin); strcpy(novo->Valor.M, M); break;
    		}
			printf("\n");
			
			while(auxDados->prox!=NULL){
				auxDados=auxDados->prox;
			}
			
			auxDados->prox = novo;
			
			aux = aux->prox;
			auxDados = aux->Pdados;
    	}
    }
}
