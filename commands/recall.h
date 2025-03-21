#include <stdio.h>
#include <stdlib.h>  // (malloc, free)


void recall(dUnidade *unidade) {
	char c;
    if (unidade == NULL) {
        limparmsg();
		gotoxy(25,24);
		printf("Db isn't defined, Press [BACKSPACE]");
    	do {
	    	gotoxy(1,21);
	        c = getch();  
    	}while(c != 32);
    }
    else{
        if (unidade->Status == NULL) {
            limparmsg();
			gotoxy(25,24);
			printf("The unit has no records, Press [BACKSPACE]");
	    	do {
		    	gotoxy(1,21);
		        c = getch();  
	    	}while(c != 32);
        }
        else{
            if (unidade->Status->Status == 'D') {
                unidade->Status->Status = 'A'; // o 'A' para indicar q foi ativado o registro que estava 'D'
                limparmsg();
				gotoxy(6,24);
				printf("Current record for drive has been restored, Press [BACKSPACE]");
		    	do {
			    	gotoxy(1,21);
			        c = getch();  
		    	}while(c != 32);
            }
            else {
                limparmsg();
				gotoxy(11,24);
				printf("Current record marked as not deleted, Press [BACKSPACE]");
		    	do {
			    	gotoxy(1,21);
			        c = getch();  
		    	}while(c != 32);
            }
        }
    }
}
void recall_all(dUnidade *unidade) {
	char c;
    if (unidade == NULL) {
        limparmsg();
		gotoxy(25,24);
		printf("Db isn't defined, Press [BACKSPACE]");
    	do {
	    	gotoxy(1,21);
	        c = getch();  
    	}while(c != 32);
    }
    else{
        if (unidade->Campos == NULL) {
        	limparmsg();
			gotoxy(25,24);
			printf("The unit has no records, Press [BACKSPACE]");
	    	do {
		    	gotoxy(1,21);
		        c = getch();  
	    	}while(c != 32);
        }
        else{
            
            Campos *campo = unidade->Campos;
            while (campo != NULL) {
                Pdados *dado = campo->Pdados;
                while (dado != NULL) {
                    if (unidade->Status != NULL && unidade->Status->Status == 'D') {
                        unidade->Status->Status = 'A';
                    }
                    dado = dado->prox;
                }
                campo = campo->prox;
            }
			limparmsg();
			gotoxy(21,24);
			printf("All records have been restored, Press [BACKSPACE]");
	    	do {
		    	gotoxy(1,21);
		        c = getch();  
	    	}while(c != 32);
        }
    }
}
