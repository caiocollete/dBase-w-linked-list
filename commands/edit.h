void edit(dUnidade *unid){
	if(unid!=NULL){
		Campos *aux = unid->Campos;
		while(aux!=NULL){
			
			printf("%s:\t", aux->FieldName);
			
			switch (aux->Type) {
	            case 'N': scanf("%f", &aux->Patual->Valor.N); break;
	            case 'D': scanf("%15s", &aux->Patual->Valor.D); break;
	            case 'L': scanf("%d", &aux->Patual->Valor.L); break;
	            case 'C': scanf("%49s", &aux->Patual->Valor.C); break;
	            case 'M': scanf("%49s", &aux->Patual->Valor.M); break;
	        }
	        printf("\n");
	        aux=aux->prox;
		}	
	}
}
