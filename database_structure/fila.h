/*
	FILA PARA PDADOS - USANDO NO APPEND
*/

struct fila{
	Pdados *info;
	struct fila *prox;
};
typedef struct fila Fila;

void init(Fila **F){
	*F=NULL;
}

char isEmpty(Fila *F){
	return F==NULL;
}

Pdados* fim(Fila *F){
	if(!isEmpty(F)){
		while(F->prox!=NULL)
			F=F->prox;
		return F->info;
	}
	return NULL;
}

void enqueue(Fila **F, Pdados *info){
	Fila *nova = (Fila*)malloc(sizeof(Fila));
	Fila *aux;
	nova->info=info;
	nova->prox=NULL;
	aux = *F;
	
	if(!isEmpty(aux)){
		while(aux->prox!=NULL){
			aux=aux->prox;
		}
		aux->prox=nova;
	}
	else{
		*F=nova;
	}
}

Pdados dequeue(Fila **F, Pdados **info){
	Fila *aux = *F;
	*F=(*F)->prox;
	*info=aux->info;
	free(aux);
	aux=NULL;
}
