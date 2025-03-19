#include <stdio.h>  
#include <stdlib.h> 
void clear() { //9
    #ifdef _WIN32
        system("cls");  // windows
    #else
        system("clear"); // macOS do caiocollete
    #endif
}

void deletee(dUnidade *unidade) {
    if (unidade == NULL) {
        printf("Nenhuma unidade está em uso.\n");
    }
    else{
        if (unidade->Status == NULL) {
            printf("Erro: Status do registro não encontrado\n");
        }
        else{
            unidade->Status->Status = 'D';// esse 'D' mostre o registro foi deletado logicamente
            printf("Registro atual unidade: '%s' marcado para exclusão\n", unidade->NomeDBF);//alterar escrita
        }
    }
    
}

void delete_all(dUnidade *unidade) {
    if (unidade == NULL) {
        printf("Nenhuma unidade esta em uso\n");
    }
    else{
        if (unidade->Campos == NULL) {
            printf("A unidade '%s' não possui registros\n", unidade->NomeDBF);
        }
        else{
            //remover esse printf dps
            printf("todos os registros da unidade '%s' para exclusão\n\n", unidade->NomeDBF);
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

            printf("Todos registros foram marcados para exclusão!\n");
        }
    }
}
