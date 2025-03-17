#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCOMMAND 128
#define NUM_PREFIXOS 20

#include "./database_structure/db.h"

#include "./database_structure/fila.h"

#include "./commands/commands.h"
#include "./commands/settodefault.h"
#include "./commands/createdbf.h"
#include "./commands/dir.h"
#include "./commands/list.h"
#include "./commands/use.h"
#include "./commands/append.h"

#include "./commands/locate.h"
#include "./commands/goto.h"
#include "./commands/pack.h"
#include "./commands/recall.h"
#include "./commands/zap.h"
#include "./commands/clear_delete.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio2.h>
#else
    #include <unistd.h> // sleep on MacOS
#endif


int main(void){

    dBase *dbase = NULL, *dbAtual=NULL;
    dUnidade *unidadeAtual=NULL;
	Command command;
	char ent[MAXCOMMAND];
    ent[strcspn(ent, "\n")] = 0;
    to_upper_str(ent);
    
    dataseeder(&dbase);
	
	while(strcmp("QUIT", ent)!=0){
		printf("[db@localhost] $ ");
        
        fgets(ent, sizeof(ent), stdin);
        ent[strcspn(ent, "\n")] = 0;
        to_upper_str(ent);
        
		command=processarComando(ent);
        printf("[%d] %s\n", command.type, command.value);
        
        switch(command.type){
            case 0: setDefault(&dbase, command.value, &dbAtual, &unidadeAtual); break;
            case 1: createdbf(dbAtual, command.value); break;
            case 2: dir(dbAtual); break;
            case 3: /*QUIT*/ break;
            case 4: use(dbAtual, &unidadeAtual,command.value); break;
            case 5: liststructure(dbAtual, unidadeAtual); break;
            case 6: append(&unidadeAtual); break;
            case 7: listfor(command.value, unidadeAtual); break;
            case 8: list(unidadeAtual); break;
            case 9: clear(); break; // ao dar clear temos que escrever novamente a interface
            
            case 10: 
            case 11: gotoo(unidadeAtual, command.value); break
            case 12:
            case 13:
                
            case 14: delete_all(unidadeAtual); break;
            case 15: deletee(unidadeAtual); break;
            case 16: recall_all(unidadeAtual); break;
            case 17: break; // faltando
            case 18: pack(unidadeAtual); break;
            case 19: zap(unidadeAtual); break;
            case 20: recall(unidadeAtual); break;
            
        }
        
        
#ifdef _WIN32
		getch();
        system("cls");
#else
		sleep(3);
        system("clear");
#endif
	}
	
	return 0;
}
