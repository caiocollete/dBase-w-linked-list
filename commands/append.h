void append(dUnidade **unidade) {
    if (*unidade == NULL) {
        printf("Define a DB to use\nYou can define with 'USE name.dbf'\n");
        return;
    }

    Campos *aux = (*unidade)->Campos;
    
    while (aux != NULL) {
        Pdados *novo = (Pdados *)malloc(sizeof(Pdados));
        if (novo == NULL) {
            printf("Erro ao alocar memória!\n");
            return;
        }
        novo->prox = NULL;

        printf("%s: ", aux->FieldName);
        switch (aux->Type) {
            case 'N': 
                scanf("%f", &novo->Valor.N);
                break;
            case 'D':
                printf("(00/00/0000) ");
                fgets(novo->Valor.D, sizeof(novo->Valor.D), stdin);
                novo->Valor.D[strcspn(novo->Valor.D, "\n")] = '\0'; // Remove o '\n'
                break;
            case 'L': 
                scanf("%d", &novo->Valor.L);
                break;
            case 'C': 
                fgets(novo->Valor.C, sizeof(novo->Valor.C), stdin);
                novo->Valor.C[strcspn(novo->Valor.C, "\n")] = '\0'; // Remove o '\n'
                break;
            case 'M': 
                fgets(novo->Valor.M, sizeof(novo->Valor.M), stdin);
                novo->Valor.M[strcspn(novo->Valor.M, "\n")] = '\0'; // Remove o '\n'
                break;
            default:
                printf("Tipo desconhecido!\n");
                free(novo);
                return;
        }

        // Adiciona na lista de dados do campo correspondente
        if (aux->Pdados == NULL) {
            aux->Pdados = novo;
        } else {
            Pdados *auxDados = aux->Pdados;
            while (auxDados->prox != NULL) {
                auxDados = auxDados->prox;
            }
            auxDados->prox = novo;
        }

        aux = aux->prox; // Avança para o próximo campo
    }
}
