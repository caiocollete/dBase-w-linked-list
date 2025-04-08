void edit(dUnidade *unid){
	int x = 1;char c;
	if(unid!=NULL){
		Campos *aux = unid->Campos;
		while(aux!=NULL){
			
			gotoxy(1,x);
			printf("%s:  ", aux->FieldName);
			switch (aux->Type) {
	            case 'N': scanf("%f", &aux->Patual->Valor.N); break;
	            case 'D': scanf("%15s", &aux->Patual->Valor.D); break;
	            case 'L': scanf("%d", &aux->Patual->Valor.L); break;
	            case 'C': scanf("%49s", &aux->Patual->Valor.C); break;
	            case 'M': scanf("%49s", &aux->Patual->Valor.M); break;
	        }
	        aux=aux->prox;
	        x++;
		}	
	}else{
		limparmsg();
		gotoxy(11,24);
	    printf("Define a DB to use | You can define with 'USE name.dbf'\n");
    	do{
	    	gotoxy(1,21);
	        c = getch();  
    	}while(c != 32);
	
	}
	limparmsg();
	gotoxy(25,24);
	printf("Press [SPACE] to continue.");
	fflush(stdin);
    gotoxy(1,21);
	getch();
}
