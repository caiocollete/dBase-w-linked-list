#include <stdio.h>  
#include <stdlib.h>
void zap(dUnidade *unidade) {
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
			gotoxy(8,24);
			printf("The unit is already completely empty, Press [BACKSPACE]");
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
                    Pdados *temp = dado;
                    dado = dado->prox;
                    free(temp);
                }
                // libera o campo para remover os dados...
                Campos *tempCampo = campo;
                campo = campo->prox;
                free(tempCampo);
            }

            // define a lista como vazia
            unidade->Campos = NULL;

            limparmsg();
			gotoxy(7,24);
			printf("All records have been physically removed!, Press [BACKSPACE]");
	    	do {
	    	gotoxy(1,21);
	        c = getch();  
	    	}while(c != 32);
        }
    }
}
