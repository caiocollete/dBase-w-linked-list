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
typedef struct tpcommand Command;

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
    int i = 0;

    while (i < NUM_PREFIXOS && strncmp(entrada, prefixos[i], strlen(prefixos[i])) != 0) {
        i++;
    }

    if (i < NUM_PREFIXOS) {
        command.type = i;

        strncpy(command.value, entrada + strlen(prefixos[i]), MAXCOMMAND - 1);
        command.value[MAXCOMMAND - 1] = '\0';
    } else {
        command.type = -1;
        strcpy(command.value, "INVALID COMMAND");
    }

    return command;
}

int main(void){
	
	Command command;
	char ent[MAXCOMMAND];
	
	printf("[db@localhost] $ ");
	gets(ent);
	command=processarComando(ent);
	printf("[%d] %s", command.type, command.value);
	
	return 0;
}
