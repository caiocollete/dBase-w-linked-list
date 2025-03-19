#include <stdio.h>
#include <stdlib.h>  // (malloc, free)


void recall(dUnidade *unidade) {
    if (unidade == NULL) {
        printf("Nenhuma unidade esta em uso.\n");
    }
    else{
        if (unidade->Status == NULL) {
            printf("Erro: Status do registro não encontrado\n");
        }
        else{
            if (unidade->Status->Status == 'D') {
                unidade->Status->Status = 'A'; // o 'A' para indicar q foi ativado o registro que estava 'D'
                printf("\nRegistro atual da unidade '%s' foi restaurado\n", unidade->NomeDBF);
            }
            else {
                printf("\nRegistro atual marcado não está como excluído\n");//rever printf
            }
        }
    }
}

void recall_all(dUnidade *unidade) {
    if (unidade == NULL) {
        printf("Nenhuma unidade esta em uso.\n");
    }
    else{
        if (unidade->Campos == NULL) {
            printf("A unidade '%s' não possui registros\n", unidade->NomeDBF);
        }
        else{
            //rever printf
            printf("\nRestaurando todos os registros da unidade '%s'\n", unidade->NomeDBF);
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
            //rever printf
            printf("Todos os registros foram restaurados!\n");
        }
    }
}
