int calcularTamanho(dUnidade *unidade) {
    int total = 0;
    Campos *campo = unidade->Campos;
    while (campo) {
        total += campo->Width;
        campo = campo->prox;
    }
    return total;
}

void dir(dBase *db){
	limparescrita();
	int total=0;
	int x = 3, z = 0;
	if(db!=NULL){
		dUnidade *unidade = db->unidade;
		int size = calcularTamanho(unidade);
	    if(unidade!=NULL){
	    	
	    	gotoxy(1,1);
	    	printf(" DIR");
	    	gotoxy(1,2);
	    	printf("Database Files");
	    	gotoxy(25,2);
	    	printf("# Records");
	    	gotoxy(44,2);
	    	printf("Last Update");
	    	gotoxy(62,2);
	    	printf("Size");

	        while(unidade!=NULL){
	        	gotoxy(1,x);
	            printf("%s",unidade->NomeDBF);
	            gotoxy(33,x);
	            printf("%d",z);
	            gotoxy(44,x);
	            printf("%s",unidade->Data);
	            gotoxy(64,x);
	            printf("%d",size);
	            total+=size;
	            unidade = unidade->prox;
	            x++;
	            z++;
	            if(x == 17)
	            {
					
	            }
	        }
	        gotoxy(1,17);
	        printf("    %d bytes in	    %d files.",total,z);
	        limparmsg();
			gotoxy(28,24);
			printf("  To close, Press [BACKSPACE]");
			char c;
	    	do {
	    	gotoxy(1,21);
	        c = getch();  
	    	}while(c != 32);
	    }
	    else{
	    	limparmsg();
			gotoxy(25,24);
			printf("UNIT is NULL, Press [BACKSPACE]");
			char c;
	    	do {
	    	gotoxy(1,21);
	        c = getch();  
	    	}while(c != 32);
	    }
		
	}
	else{
		limparmsg();
		gotoxy(25,24);
		printf("Db isn't defined, Press [BACKSPACE]");
		char c;
    	do {
    	gotoxy(1,21);
        c = getch();  
    	}while(c != 32);
		
	}
	
}
