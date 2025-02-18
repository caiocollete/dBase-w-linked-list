void createdbf(dBase *db, char *namedbf){
    dUnidade *novaUnidade;
    dUnidade *nova = (dUnidade*)malloc(sizeof(dUnidade));
    char data[MAXDATA], FieldName[MAXFIELDNAME], Type;
    int Desc, Width;
    strcpy(FieldName, " ");
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    strcpy(nova->NomeDBF, namedbf);
    printf("Data (00/00/0000): ");
    fgets(data, sizeof(data), stdin);
    printf("\n");
    printf("Hora (00:00): ");
    fgets(Hora, sizeof(Hora), stdin);
    printf("\n");
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    
    while(strcmp(FieldName, "EXIT")!=0){
        printf("FieldName: ");
        fgets(FieldName, sizeof(FieldName), stdin);
        printf("\n");
        printf("Type: ");
        scanf(" %c", &Type);
        printf("\n");
        printf("Width: ");
        scanf("%d", &Width);
        printf("\n");
        printf("Desc: ");
        scanf("%d", &Desc);
        printf("\n");
        
        // criar uma struct Campos e inserir os dados nela
        novoCampo=(Campos*)malloc(sizeof(Campos));
        strcpy(novoCampo->FieldName, FieldName);
        novoCampo->Type = Type;
        novoCampo->Desc = Desc;
        novoCampo->Width = Width;
        novoCampo->Pdados = NULL;
        novoCampo->prox = NULL;
        
        // depois inserir na lista encadeada de campos (valor de "dUnidade nova")
        if(nova->Campos==NULL){
            nova->Campos = novoCampo;
        }
        else{
            Campo *aux = nova->Campos;
            while(aux->prox!=NULL){
                aux = aux->prox;
            }
            aux->prox=novoCampo;
        }
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
}
