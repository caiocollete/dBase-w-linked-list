#include <stdio.h>  
#include <stdlib.h>  

/*void zap(dUnidade *unidade) {
    if (unidade == NULL) {
        printf("Nenhuma unidade esta em uso.\n");
        return;
    }
    if (unidade->Campos == NULL) {
        printf("A unidade '%s' já está completamente vazia\n", unidade->NomeDBF);
        return;
    }
    printf("\nExecutando ZAP na unidade '%s'\n", unidade->NomeDBF);
    Campos *campo = unidade->Campos;
    while (campo != NULL) {
        Pdados *dado = campo->Pdados;
        while (dado != NULL) {
            Pdados *temp = dado;
            dado = dado->prox;
            free(temp); // libera a memoria , exclusao fisica
        }
        // define dps a lista como vazia
        campo->Pdados = NULL; 
        campo = campo->prox;
    }

    printf("Todos os registros foram removidos fisicamente!\n");
}*/


/*if (unidade == NULL) {
    printf("Nenhuma unidade esta em uso.\n");
    return;
}*/

void zap(dUnidade *unidade) {
    if (unidade == NULL) {
        printf("Nenhuma unidade está em uso.\n");
        return;
    }
    if (unidade->Campos == NULL) {
        printf("A unidade '%s' já está completamente vazia.\n", unidade->NomeDBF);
        return;
    }
    printf("\nExecutando ZAP na unidade '%s'\n", unidade->NomeDBF);
    Campos *campo = unidade->Campos;
    while (campo != NULL) {
        Pdados *dado = campo->Pdados;
        while (dado != NULL) {
            Pdados *temp = dado;
            dado = dado->prox;
            free(temp); 
        }
        // libera o próprio campo após remover os dados...
        Campos *tempCampo = campo;
        campo = campo->prox;
        free(tempCampo);
    }

    // define a lista como vazia
    unidade->Campos = NULL;

    printf("Todos os registros foram removidos fisicamente!\n");
}
