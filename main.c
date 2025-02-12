#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "settodefault.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio2.h>
#else
    #include <unistd.h> // sleep on MacOS
    #include "./conio3/conio3.h"
#endif


#include "db.h"
#include "commands.h"

#define MAXCOMMAND 128
#define NUM_PREFIXOS 19

struct tpcommand{
	int type;
	char value[MAXCOMMAND]; 
};
typedef struct tpcommand Command;

const char *prefixos[NUM_PREFIXOS] = {
    "SET DEFAULT TO ", // 0
    "CREATE ", // 1
    "DIR", // 2
    "QUIT", // 3
    "LIST STRUCTURE", // 4
    "APPEND", // 5
    "LIST FOR NOME = ", // 6
    "LIST", // 7
    "CLEAR", // 8
    "LOCATE FOR NOME = ", // 9
    "GOTO ", // 10
    "DISPLAY", //11
    "EDIT", //12
    "DELETE ALL", // 13
    "DELETE", // 14
    "RECALL", // 15
    "SET DELETED ", // 16
    "PACK", // 17
    "ZAP" // 18
};


void to_upper_str(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

Command processarComando(char *entrada) {
    Command command;
    int i = 0;

    while (i < NUM_PREFIXOS && strncmp(entrada, prefixos[i], strlen(prefixos[i])) != 0) {
        i++;
    }

    if (i < NUM_PREFIXOS) {
        command.type = i;

        strncpy(command.value, entrada + strlen(prefixos[i]), MAXCOMMAND - 1);
        command.value[MAXCOMMAND - 1] = '\0';
    } 
	else {
        command.type = -1;
        strcpy(command.value, "INVALID COMMAND");
    }

    return command;
}


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
        
        switch(command.value){
            case 0: setDefault(&dbase, command.value, &dbAtual);
                    break;
            case 1: break;
        }
        
		
        
#ifdef _WIN32
        sleep(3000); // milisec
        system("cls");
#else
        sleep(3); // sec
        system("clear");
#endif
	}
	
	return 0;
}
