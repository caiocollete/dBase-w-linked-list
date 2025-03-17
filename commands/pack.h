#include <stdio.h>  
#include <stdlib.h>

void pack(dUnidade *unidade) {
    if (unidade == NULL || unidade->Campos == NULL) {
        printf("Nenhuma unidade esta em uso ou sem registros.\n");
        return;
    }
    printf("\nExecutando PACK na unidade '%s'\n", unidade->NomeDBF);
    Campos *campo = unidade->Campos;
    while (campo != NULL) {
        Pdados *atual = campo->Pdados;
        Pdados *anterior = NULL;

        while (atual != NULL) {
            if (atual->Status != NULL && atual->Status->Status == 'D') {  // apenas registros com status 'D'
                if (anterior == NULL) {
                    campo->Pdados = atual->prox;
                } else {
                    anterior->prox = atual->prox;
                }
                Pdados *temp = atual;
                atual = atual->prox;
                free(temp); //free 
            } else {
                anterior = atual;
                atual = atual->prox;
            }
        }
        campo = campo->prox;
    }

    printf("Registros marcados como 'D' foram removidos fisicamente!\n");
}
