int use(dBase *atual, dUnidade **unidade, char *target){
	char c;
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
	            limparmsg();
				gotoxy(15,24);
				printf("[%s] was setted, Press [BACKSPACE]",target);
				do {
				gotoxy(1,21);
			    c = getch();  
				}while(c != 32);
	    	   	return 1;
	        }
	        else{
	        	
		            limparmsg();
					gotoxy(15,24);
					printf("[%s] was not found, Press [BACKSPACE]",target);
					do {
					gotoxy(1,21);
				    c = getch();  
					}while(c != 32);
		    	   	return 0;
			}
    	}
        else{
        	
    		limparmsg();
			gotoxy(25,24);
			printf("UNIT isn't DEFINED, Press [BACKSPACE]");
			do {
			gotoxy(1,21);
		    c = getch();  
			}while(c != 32);
    	   	return 0;
        	
        }
        	
    }
    else
    	{
    		limparmsg();
			gotoxy(25,24);
			printf("Db isn't defined, Press [BACKSPACE]");
			do {
			gotoxy(1,21);
		    c = getch();  
			}while(c != 32);
    	   	return 0;

    	}
}
