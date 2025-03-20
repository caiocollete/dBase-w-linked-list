#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCOMMAND 128
#define NUM_PREFIXOS 20

#include "./database_structure/db.h"

#include "./database_structure/fila.h"
#include "./database_structure/filaStatus.h"

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
#include "./commands/setdelete.h"
#include "./commands/zap.h"
#include "./commands/clear_delete.h"
#include "./commands/visualDbase.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio2.h>
#else
    #include <unistd.h> // sleep on MacOS
#endif


int main(void){

	char dire[100] ="?"; // exibir o DIRETORIO 	 NA INTERFACE
    dBase *dbase = NULL, *dbAtual=NULL;
    dUnidade *unidadeAtual=NULL;
    int viewDelete=0;
	Command command;
	char ent[MAXCOMMAND];
    ent[strcspn(ent, "\n")] = 0;
    to_upper_str(ent);
    
    dataseeder(&dbase);
    //Aqui começas a exibição da tela "introdução"
	tela1();
	clear();
	while(strcmp("QUIT", ent)!=0){
		//clear();
		commandline(dire);  
		fflush(stdin);
        fgets(ent, sizeof(ent), stdin);
        ent[strcspn(ent, "\n")] = 0;
        to_upper_str(ent);
        
		command=processarComando(ent);
		
		gotoxy(58,18);
		//remover esse printf quando acabar as telas toda.
        printf("[%d] %s\n", command.type, command.value);
        
        
        /*Interface: Bem vindo, setdefault, create, dir, clear*/
        switch(command.type){
            case 0: setDefault(&dbase, command.value, &dbAtual, &unidadeAtual);
            strcpy(dire, command.value);
        	strncpy(dire, command.value, sizeof(dire) - 1);
    		dire[sizeof(dire) - 1] = '\0';
        	commandline(dire);
			break; 
            case 1: commandCreate(dire, command.value);
					createdbf(dbAtual, command.value); break;
            case 2: commandDir(dire);
					dir(dbAtual); 
					clear();break;
            case 3: /*QUIT*/ break; 
            case 4: use(dbAtual, &unidadeAtual,command.value); break;
            case 5: liststructure(dbAtual, unidadeAtual); break;
            case 6: append(&unidadeAtual); break;
            case 7: listfor(command.value, unidadeAtual, viewDelete); break;
            case 8: list(unidadeAtual, viewDelete); break;
            case 9: clear(); break; 
            
            case 10: locate(command.value, unidadeAtual, viewDelete); break;
            case 11: gotoo(unidadeAtual, command.value); break;
            case 12: break; 
            case 13: break;
                
            case 14: delete_all(unidadeAtual); break;
            case 15: deletee(unidadeAtual); break;
            case 16: recall_all(unidadeAtual); break;
            case 17: setdelete(&viewDelete, command.value); break; 
            case 18: pack(unidadeAtual); break;
            case 19: zap(unidadeAtual); break;
            case 20: recall(unidadeAtual); break;
            default: commandinvalido(dire);break; //interface concluida
        }
        
        

	}
	
	return 0;
}
