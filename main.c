#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCOMMAND 128
#define NUM_PREFIXOS 19

#include "./database_structure/db.h"

#include "./commands/commands.h"
#include "./commands/settodefault.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio2.h>
#else
    #include <unistd.h> // sleep on MacOS
    #include "./conio3/conio3.h"
#endif


int main(void){

    dBase *dbase = NULL, *dbAtual=NULL;
    
	Command command;
	char ent[MAXCOMMAND];
    ent[strcspn(ent, "\n")] = 0;
    to_upper_str(ent);
	
	while(strcmp("QUIT", ent)!=0){
		printf("[db@localhost] $ ");
        
        fgets(ent, sizeof(ent), stdin);
        ent[strcspn(ent, "\n")] = 0;
        to_upper_str(ent);
        
		command=processarComando(ent);
        printf("[%d] %s\n", command.type, command.value);
        
        switch(command.type){
            case 0: setDefault(&dbase, command.value, &dbAtual);
            		printf("Defining an disk...");
                    break;
            case 1: break;
        }
        
        sleep(3); // sec
        
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
	}
	
	return 0;
}
