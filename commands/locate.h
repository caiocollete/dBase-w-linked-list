void locate(char *parm, dUnidade *unidAt, char viewDelete) {
    Campos *campoFiltro;
    Status *statusAtual;
    char filterField[MAXNAME], filter[MAXNAME], c;;
    int i = 0, j = 0, count = 0;
    
    // Parse do par?metro
    while (parm[i] != '=' && parm[i] != '\0') i++;
    
    if (parm[i] == '=') {
        // Extrair nome do campo
        while (j < i && parm[j] == ' ') j++;
        strncpy(filterField, parm + j, i - j);
        filterField[i - j] = '\0';
        
        // Extrair valor do filtro
        i++;
        while (parm[i] == ' ') i++;
        strcpy(filter, parm + i);

        // Localizar campo
        campoFiltro = unidAt->Campos;
        if (findField(filterField, &campoFiltro)) {
            // Inicializar ponteiros
            statusAtual = unidAt->Status;
            Campos *auxCampos = unidAt->Campos;
            while (auxCampos) {
                auxCampos->Patual = auxCampos->Pdados;
                auxCampos = auxCampos->prox;
            }

            // Percorrer registros
            while (statusAtual) {
                int filtroOK = 0;
                int mostrar = (viewDelete || statusAtual->Status == 'A');

                // Verificar filtro
                if (campoFiltro->Patual) {
                    switch (campoFiltro->Type) {
                        case 'N':
                            filtroOK = (campoFiltro->Patual->Valor.N == atof(filter));
                            break;
                        case 'D': case 'C': case 'M': {
                            char valCampo[MAXNAME], valFiltro[MAXNAME];
                            strcpy(valCampo, campoFiltro->Type == 'D' ? 
                                campoFiltro->Patual->Valor.D :
                                campoFiltro->Type == 'C' ? 
                                campoFiltro->Patual->Valor.C : 
                                campoFiltro->Patual->Valor.M);
                            strcpy(valFiltro, filter);
                            to_upper_str(valCampo);
                            to_upper_str(valFiltro);
                            filtroOK = (strcmp(valCampo, valFiltro) == 0);
                            break;
                        }
                        case 'L':
                            filtroOK = (campoFiltro->Patual->Valor.L == atoi(filter));
                            break;
                    }
                }

                // Contar se atender ambos crit?rios
                if (filtroOK && mostrar) {
                    count++;
                }

                // Avan?ar registros
                Campos *campoAvancar = unidAt->Campos;
                while (campoAvancar) {
                    if (campoAvancar->Patual) {
                        campoAvancar->Patual = campoAvancar->Patual->prox;
                    }
                    campoAvancar = campoAvancar->prox;
                }
                statusAtual = statusAtual->prox;
            }

            // Exibir resultado
            if (count > 0) {
                gotoxy(1,20);
                printf("Record: %d\n", count);
                limparmsg();
				gotoxy(26,24);
			     printf("These were the records, Press [SPACE]");
		    	do{
			    	gotoxy(1,21);
			        c = getch();  
		    	}while(c != 32);
            } 
			else {
                limparmsg();
                gotoxy(10,24);
                printf("No records match the criteria, Press [SPACE]");
                do{
                    gotoxy(1,21);
                    c = getch();  
                }while(c != 32);
            }

            // Resetar ponteiros
            auxCampos = unidAt->Campos;
            while (auxCampos) {
                auxCampos->Patual = auxCampos->Pdados;
                auxCampos = auxCampos->prox;
            }
        } 
		else {
            limparmsg();
			gotoxy(12,24);
		    printf("field  %s not found!, Press [SPACE]",filterField);
	    	do{
		    	gotoxy(1,21);
		        c = getch();  
	    	}while(c != 32);
        }
    } 
	else {
        limparmsg();
		gotoxy(10,24);
	    printf("Invalid format! Use: FIELD=VALUE, Press [SPACE]");
    	do{
	    	gotoxy(1,21);
	        c = getch();  
    	}while(c != 32);
    }
}
