void setdelete(int *viewDelete, char *value) {
    if (viewDelete == NULL || value == NULL) {
        printf("Missing parameters\n");
    }
    else{
      	if(strcmp(value, "ON") == 0){
	       *viewDelete = 1;
	       printf("viewDelete ON\n");
	    }
		else {
	        *viewDelete = 0;
	        printf("viewDelete OFF\n");
	    }
    }
}

