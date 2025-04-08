void setdelete(int *viewDelete, char *value) {
	char c;
    if (viewDelete == NULL || value == NULL) {
        limparmsg();
		gotoxy(28,24);
		printf("Missing parameters, Press [SPACE]");
		do {
    	gotoxy(1,21);
        c = getch();  
    	}while(c != 32);
    }
    else{
      	if(strcmp(value, "ON") == 0){
	        *viewDelete = 1;
	       	
		}
		else if(strcmp(value, "OFF") == 0){
	        *viewDelete = 0;
	        
	    }
	    else{
	    	limparmsg();
			gotoxy(20,24);
			printf("Type 'ON' or 'OFF', Press [SPACE]");
			do {
		    	gotoxy(1,21);
		        c = getch();  
    		}while(c != 32);
	    }
    }
}

