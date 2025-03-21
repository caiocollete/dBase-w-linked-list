void pack(dUnidade *unidade) {
	char c;
    if (unidade == NULL || unidade->Campos == NULL || unidade->Status == NULL) {
    	limparmsg();
		gotoxy(25,24);
		printf("Db isn't defined, Press [BACKSPACE]");
    	do {
    	gotoxy(1,21);
        c = getch();  
    	}while(c != 32);
    }
    else{
        Campos *campo = unidade->Campos;
        int registrosRemovidos = 0;

        while (campo != NULL) {
            Pdados *atual = campo->Pdados;
            Pdados *anterior = NULL;
            Status *statusAtual = unidade->Status;
            Status *statusAnterior = NULL;

            while (atual != NULL && statusAtual != NULL) {
                if (statusAtual->Status == 'D') {  // Verifica se o registro esta marcado para remocao
                    if (anterior == NULL) {
                        campo->Pdados = atual->prox;
                    }
                    else {
                        anterior->prox = atual->prox;
                    }
                    if (statusAnterior == NULL) {
                        unidade->Status = statusAtual->prox;
                    }
                    else {
                        statusAnterior->prox = statusAtual->prox;
                    }
                    
                    Pdados *temp = atual;
                    Status *tempStatus = statusAtual;
                    atual = atual->prox;
                    statusAtual = statusAtual->prox;

                    free(temp);  // Libera o registro
                    free(tempStatus);  // Libera o status associado
                    registrosRemovidos++;
                }
                else {
                    anterior = atual;
                    statusAnterior = statusAtual;
                    atual = atual->prox;
                    statusAtual = statusAtual->prox;
                }
            }
            campo = campo->prox;
        }
        limparmsg();
		gotoxy(7,24);
		printf("All deleted records were removed!, Press [BACKSPACE]");
    	do {
    	gotoxy(1,21);
        c = getch();  
    	}while(c != 32);
    }
}
