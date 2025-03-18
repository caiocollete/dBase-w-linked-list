void setdelete(int *viewDelete, char *value){
	if(*viewDelete == NULL || value==NULL){
		printf("Missing parameters");
	}
	else{
		if(strcmp(value,"ON")==0)
			*viewDelete=1;
		else 
			*viewDelete=0;
	}
}
