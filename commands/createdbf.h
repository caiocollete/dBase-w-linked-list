void createdbf(dBase *db, char *namedbf){
    
    Campos *novoCampo;
    dUnidade *aux = db->unidade;
    dUnidade *nova = (dUnidade*)malloc(sizeof(dUnidade));
    char FieldName[MAXFIELDNAME], Type;
    int Dec, Width;
    strcpy(FieldName, " ");
/*#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif*/
    strcpy(nova->NomeDBF, namedbf);
    gotoxy(1,3);
    printf("Data (00/00/0000): ");
    gotoxy(20,3);
	fflush(stdin);
    fgets(nova->Data, sizeof(MAXDATA), stdin);
    gotoxy(1,4);
    printf("Hora (00:00): ");
    gotoxy(15,4);
    fflush(stdin);
    fgets(nova->Hora, sizeof(MAXHORA), stdin);
    nova->Campos=NULL;
/*#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif*/

    gotoxy(1,5);
    printf("FieldName: ");
    fflush(stdin);
    fgets(FieldName, sizeof(FieldName), stdin);
    
    while(strcmp(FieldName, "EXIT\n")!=0){

    	gotoxy(1,6);
        printf("Type: ");
        fflush(stdin);
        scanf("%c", &Type);
        gotoxy(1,7);
        printf("Width: ");
        scanf("%d", &Width);
        gotoxy(1,8);
        printf("Desc: ");
        scanf("%d", &Dec);
        ClearTela();
        // criar uma struct Campos e inserir os dados nela
        novoCampo=(Campos*)malloc(sizeof(Campos));
        strcpy(novoCampo->FieldName, FieldName);
        novoCampo->Type = Type;
        novoCampo->Dec = Dec;
        novoCampo->Width = Width;
        novoCampo->Pdados = NULL;
        novoCampo->prox = NULL;
        
        // depois inserir na lista encadeada de campos (valor de "dUnidade nova")
        if(nova->Campos==NULL){
            nova->Campos = novoCampo;
        }
        else{
            Campos *camposAux = nova->Campos;
            while(camposAux->prox!=NULL){
                camposAux = camposAux->prox;
            }
            camposAux->prox=novoCampo;
        }
        
        // inserir a new.DBF na db
       if (aux == NULL) {  // Se a lista de unidades está vazia
            db->unidade = nova;
        } else {
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = nova;
            nova->ant = aux;
            nova->prox=NULL;
        }	
        
        gotoxy(1,5);
	    printf("FieldName: ");
	    fflush(stdin);
	    fgets(FieldName, sizeof(FieldName), stdin);
	
    }
    ClearTela();
}
