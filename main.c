#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "commands.h"

#define MAXCOMMAND 128
#define NUM_PREFIXOS 19

struct tpcommand{
	int type;
	char value[MAXCOMMAND]; 
};
typedef tpcommand Command;

const char *prefixos[NUM_PREFIXOS] = {
    "SET DEFAULT TO ",
    "CREATE ",
    "DIR", // 3
    "QUIT", // 4
    "LIST STRUCTURE", // 5
    "APPEND", // 6
    "LIST", // 7
    "LIST FOR NOME = ",
    "CLEAR", // 9
    "LOCATE FOR NOME = ",
    "GOTO ",
    "DISPLAY", //12
    "EDIT", //13
    "DELETE", //14
    "DELETE ALL", //15
    "RECALL", //16
    "SET DELETED ",
    "PACK", //18
    "ZAP" //19
};

Command processarComando(char *entrada) {
	Command command;
    for(int i=0; i<NUM_PREFIXOS; i++){
    	if (strncmp(entrada, prefixos[i], strlen(prefixos[i])) == 0) {
			command.type=i;
			if(i!=3 && i!=4 && i!=5 && i!=6 && i!=7 && i!=9 && i!=12 && i!=13 && i!=14 && i!=15 && i!=16 && i!=18 && i!=19){
				strcpy(command.value, /* preciso pegar as ultimas partes */);
			}
    	}	
	}
}

int main(void){
	
	Command command;
	char ent[MAXCOMMAND];
	
	printf("[db@localhost] $ ");
	gets(ent);
	command=processarComando(ent)
	
	return 0;
}
