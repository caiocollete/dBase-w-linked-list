struct tpcommand{
	int type;
	char value[MAXCOMMAND]; 
};
typedef struct tpcommand Command;

const char *prefixos[NUM_PREFIXOS] = {
    "SET DEFAULT TO ", // 0 done
    "CREATE ", // 1 done
    "DIR", // 2 done
    "QUIT", // 3 done
    "USE ", // 4 done
    "LIST STRUCTURE", // 5 done
    "APPEND", // 6 testing
    "LIST FOR NOME = ", // 7
    "LIST", // 8 doing
    "CLEAR", // 9
    "LOCATE FOR NOME = ", // 10
    "GOTO ", // 11
    "DISPLAY", //12
    "EDIT", //13
    "DELETE ALL", // 14
    "DELETE", // 15
    "RECALL", // 16
    "SET DELETED ", // 17
    "PACK", // 18
    "ZAP" // 19
};


void to_upper_str(char *str) {
	int i;
    for (i = 0; str[i]; i++) {
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
