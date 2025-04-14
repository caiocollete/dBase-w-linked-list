void display(dUnidade *unid){
	if(unid!=NULL){
		Campos *aux = unid->Campos;
		gotoxy(1,1);
		while(aux!=NULL){
			printf("%s\t", aux->FieldName);
			aux=aux->prox;
		}
		aux = unid->Campos;
		gotoxy(1,2);
		while(aux!=NULL){
			switch (aux->Type) {
	            case 'N': printf("%.2f\t", aux->Patual->Valor.N); break;
	            case 'D': printf("%s\t", aux->Patual->Valor.D); break;
	            case 'L': printf("%d\t", aux->Patual->Valor.L); break;
	            case 'C': printf("%s\t", aux->Patual->Valor.C); break;
	            case 'M': printf("%s\t", aux->Patual->Valor.M); break;
	            default: printf("?\t"); break;
	        }
	        aux=aux->prox;
		}	
	}
	getch();
	clear();
}

