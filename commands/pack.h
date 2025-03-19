void pack(dUnidade *unidade) {
    if (unidade == NULL || unidade->Campos == NULL || unidade->Status == NULL) {
        printf("Nenhuma unidade esta em uso, sem registros ou sem status.\n");
    }
    else{
        printf("\nExecutando PACK na unidade '%s'\n", unidade->NomeDBF);
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

        printf("Foram removidos %d registros deletados.\n", registrosRemovidos);
    }
}
