void locate(char *parm, dUnidade *unidAt, char viewDelete) {
    Campos *campoFiltro;
    Status *statusAtual;
    char filterField[MAXNAME], filter[MAXNAME];
    int i = 0, j = 0, count = 0;
    
    // Parse do parâmetro
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

                // Contar se atender ambos critérios
                if (filtroOK && mostrar) {
                    count++;
                }

                // Avançar registros
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
                printf("Registros encontrados: %d\n", count);
            } 
			else {
                printf("Nenhum registro corresponde ao criterio\n");
            }

            // Resetar ponteiros
            auxCampos = unidAt->Campos;
            while (auxCampos) {
                auxCampos->Patual = auxCampos->Pdados;
                auxCampos = auxCampos->prox;
            }
        } 
		else {
            printf("Campo '%s' nao encontrado!\n", filterField);
        }
    } 
	else {
        printf("Formato invalido! Use: CAMPO=VALOR\n");
    }
}
