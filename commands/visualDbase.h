#ifndef NOME_DO_ARQUIVO_H
#define NOME_DO_ARQUIVO_H

void ClearTela(void)
{ // limpa tela pricipal e mensagem
    int x, y;
    for (x = 1; x <= 79; x++)
    {
        for (y = 1; y <= 20; y++)
        {
            gotoxy(x, y);
            printf(" ");
        }
    }
    /*/for(x=15;x<78;x++){
     gotoxy(x,23);
     printf(" ");
    }/*/
}


void Moldura(int CI, int LI, int CF, int LF)
{
    int i;
    gotoxy(CI, LI);
    printf("%c", 201);
    gotoxy(CI, LF);
    printf("%c", 200);
    gotoxy(CF, LI);
    printf("%c", 187);
    gotoxy(CF, LF);
    printf("%c", 188);
    for (i = CI + 1; i < CF; i++)
    {
        gotoxy(i, LI);
        printf("%c", 205);
        gotoxy(i, LF);
        printf("%c", 205);
    }
    for (i = LI + 1; i < LF; i++)
    {
        gotoxy(CI, i);
        printf("%c", 186);
        gotoxy(CF, i);
        printf("%c", 186);
    }
}

void tela1(void)
{
    system("cls");
    Moldura(1, 1, 80, 16);
    conteudotela1();
    textcolor(0);
	textbackground(7);
	gotoxy(1,22);
	printf("Command Line      ||<?:>||                  ||                  ||     ||Num   ");//  /t nao printa branco wtf
	textcolor(7);
	textbackground(0);
	char c;
    do {
    	gotoxy(1,21);
        c = getch();  
    } while(c != 27);
    
    
}
void conteudotela1(void){
	gotoxy(16, 3);
	printf("dBase Simulator with Linked List. version 1.0");
	gotoxy(7, 4);
	printf("Copyright Caio Collete and Joao Lescovar, 2025. All Rights Reserved");
	gotoxy(29, 5);
	printf("dBase III plus Simulation");
	gotoxy(13, 6);
	printf("FIPP - Computer Science Faculty of Presidente Prudente");
	gotoxy(18, 7);
	printf("Data Structures II - Work 1st Semester - 2025");
	
	gotoxy(12,24);
	printf("Press [ESC] to start the dBase III PLUS simulator in C");
	
}

void commandline(char *diretorio){
	limparescrita();
	textcolor(0);
	textbackground(7);
	limparcommandline();
	gotoxy(1,22);
	printf("Command Line     ||<%s>||                  ||                  ||     ||Num   ",diretorio);//  /t nao printa branco wtf
	textcolor(7);
	textbackground(0);
	limparmsg();
	gotoxy(25,24);
	printf("Enter a dBase III Plus command.");
	fflush(stdin);
    gotoxy(1,21);
}

void commandinvalido(char *diretorio){
	textcolor(0);
	textbackground(7);
	gotoxy(1,22);
	printf("INVALID COMMAND    ||<%s>||                 ||                 ||     ||Num   ",diretorio);//  /t nao printa branco wtf
	textcolor(7);
	textbackground(0);
	limparmsg();
	gotoxy(22,24);
	printf("INVALID COMMAND, Press [BACKSPACE]");
	limparescrita();
    char c;
    do {
    	gotoxy(1,21);
        c = getch();  
    } while(c != 32);
}
void commandCreate(char *diretorio, char *nomearquivo, int number){
	limparescrita();
	textcolor(0);
	textbackground(7);
	limparcommandline();
	gotoxy(1,22);
	printf("Create     ||<%s>||    %s    ||         %d        ||     ||Num   ",diretorio,nomearquivo,number);//  /t nao printa branco wtf
	textcolor(7);
	textbackground(0);
	limparmsg();
	gotoxy(25,24);
	printf("fill in the data to create.");
	fflush(stdin);
    gotoxy(1,21);
}
void limparmsg(void)
{	//limpa a msg da ultima linha
    gotoxy(1,24);
    printf("%77s", "");  // Imprime 79 espaços em branco
}
void limparcommandline(void){
	gotoxy(1,22);
	printf("%77s", "");
}
void limparescrita(void){
	gotoxy(1,21);
	printf("%77s", "");
}

#endif
