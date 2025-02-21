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
    "USE ", // 4
    "LIST STRUCTURE", // 5
    "APPEND", // 6
    "LIST FOR NOME = ", // 7
    "LIST", // 8
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
