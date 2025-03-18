/*
	FILA PARA Status - USANDO NO APPEND
*/

struct filaStatus{
	Status *info;
	struct filaStatus *prox;
};
typedef struct filaStatus FilaStatus;

void initS(FilaStatus **F){
	*F=NULL;
}

char isEmptyS(FilaStatus *F){
	return F==NULL;
}

Status* fimS(FilaStatus *F){
	if(!isEmptyS(F)){
		while(F->prox!=NULL)
			F=F->prox;
		return F->info;
	}
	return NULL;
}

void enqueueS(FilaStatus **F, Status *info){
	FilaStatus *nova = (FilaStatus*)malloc(sizeof(FilaStatus));
	FilaStatus *aux;
	nova->info=info;
	nova->prox=NULL;
	aux = *F;
	
	if(!isEmptyS(aux)){
		while(aux->prox!=NULL){
			aux=aux->prox;
		}
		aux->prox=nova;
	}
	else{
		*F=nova;
	}
}

Status dequeueS(FilaStatus **F, Status **info){
	if (!isEmptyS(*F)) {
		FilaStatus *aux = *F;
		*F=(*F)->prox;
		*info=aux->info;
		free(aux);
		aux=NULL;
	}
}
