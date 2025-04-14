#include <stdio.h>  
#include <stdlib.h> 
void clear() { //9
    #ifdef _WIN32
        system("cls");  // windows
        commandline();
    #else
        system("clear"); // macOS do caiocollete
        commandline();
    #endif
}

void deletee(dUnidade *unidade) {
	char c;
    if (unidade == NULL) {
       	limparmsg();
		gotoxy(25,24);
		printf("Db isn't defined, Press [SPACE]");
    	do {
	    	gotoxy(1,21);
	        c = getch();  
    	}while(c != 32);
    }
    else{
        if (unidade->Status == NULL) {
            limparmsg();
			gotoxy(25,24);
			printf("Record status not found, Press [SPACE]");
	    	do {
		    	gotoxy(1,21);
		        c = getch();  
	    	}while(c != 32);
        }
        else{
            unidade->Status->Status = 'D';// esse 'D' mostre o registro foi deletado logicamente
            limparmsg();
			gotoxy(6,24);
			printf("Current drive record marked for deletion, Press [SPACE]");
	    	do{
		    	gotoxy(1,21);
		        c = getch();  
	    	}while(c != 32);
    	}
    }
    
}

void delete_all(dUnidade *unidade) {
	char c;
    if (unidade == NULL) {
        limparmsg();
		gotoxy(25,24);
		printf("Db isn't defined, Press [SPACE]");
    	do {
	    	gotoxy(1,21);
	        c = getch();  
    	}while(c != 32);
    }
    else{
        if (unidade->Campos == NULL) {
            limparmsg();
			gotoxy(25,24);
			printf("Record status not found, Press [SPACE]");
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
                    if (unidade->Status != NULL) {
                        unidade->Status->Status = 'D'; //marcar excluido
                    }
                    dado = dado->prox;
                }
                campo = campo->prox;
            }
            limparmsg();
			gotoxy(6,24);
			printf("All records have been marked for deletion!, Press [SPACE]");
	    	do{
		    	gotoxy(1,21);
		        c = getch();  
	    	}while(c != 32);
        }
    }
}
