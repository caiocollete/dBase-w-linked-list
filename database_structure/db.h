#define MAXNAME 64
#define MAXDATA 10
#define MAXHORA 5
#define MAXFIELDNAME 64
#define MAXBYTES 50

union dados{
	float N;
	char D[MAXDATA];
	int L;
    char C[MAXBYTES];
    char M[MAXBYTES];
};
struct tppdados{
	union dados Valor;
	struct tppatual *prox;
};
typedef	struct tppdados Pdados;

struct tpcampos{
	struct tppdados *Patual;
	char FieldName[MAXFIELDNAME];
	char Type; /* N-NUMERIC / D-DATE / L-LOGICAL / C-CHARACTER(MAX.50 BYTES) / M-MEMO(50 BYTES) */
	int Width;
	int Dec;
	struct tppdados *Pdados;
	struct tpcampos *prox;
};
typedef struct tpcampos Campos;

struct tpstatus{
	char Status;
	struct tpstatus *prox;
};
typedef struct tpstatus Status;

struct tpunidade{
	struct tpunidade *ant, *prox;
	char NomeDBF[MAXNAME];
	char Data[MAXDATA]; // "01/01/2000"
	char Hora[MAXHORA]; // "00:00"
	struct tpstatus *Status;
    struct tpcampos *Campos;
};
typedef struct tpunidade dUnidade;

struct tpdbase{
	struct tpdbase *ant, *prox;
	char disco[2]; // "C:"
	struct tpunidade *unidade;
};
typedef struct tpdbase dBase;


//DATASEEDER

void inicializarBase(dBase **base) {
    *base = (dBase *)malloc(sizeof(dBase));
    strcpy((*base)->disco, "C:");
    (*base)->ant = NULL;
    (*base)->prox = NULL;
    (*base)->unidade = NULL;
}

dUnidade *criarUnidade(const char *nome, const char *data, const char *hora) {
    dUnidade *unidade = (dUnidade *)malloc(sizeof(dUnidade));
    strcpy(unidade->NomeDBF, nome);
    strcpy(unidade->Data, data);
    strcpy(unidade->Hora, hora);
    unidade->Status = (Status *)malloc(sizeof(Status));
    unidade->Status->Status = 'A'; // Ativo
    unidade->Status->prox = NULL;
    unidade->Campos = NULL;
    unidade->ant = unidade->prox = NULL;
    return unidade;
}

Campos *criarCampo(const char *nome, char tipo, int width, int dec) {
    Campos *campo = (Campos *)malloc(sizeof(Campos));
    strcpy(campo->FieldName, nome);
    campo->Type = tipo;
    campo->Width = width;
    campo->Dec = dec;
    campo->Pdados = NULL;
    campo->prox = NULL;
    return campo;
}

void adicionarUnidade(dBase *base, dUnidade *unidade) {
    unidade->prox = base->unidade;
    if (base->unidade != NULL)
        base->unidade->ant = unidade;
    base->unidade = unidade;
}

void adicionarCampo(dUnidade *unidade, Campos *campo) {
    campo->prox = unidade->Campos;
    unidade->Campos = campo;
}

void exibirBase(dBase *base) {
    printf("Base: %s\n", base->disco);
    dUnidade *u = base->unidade;
    while (u) {
        printf("Unidade: %s | Data: %s | Hora: %s | Status: %c\n", u->NomeDBF, u->Data, u->Hora, u->Status->Status);
        Campos *c = u->Campos;
        while (c) {
            printf("  Campo: %s | Tipo: %c | Largura: %d | Dec: %d\n", c->FieldName, c->Type, c->Width, c->Dec);
            c = c->prox;
        }
        u = u->prox;
    }
}

void dataseeder(dBase **base) {
    inicializarBase(base);

    dUnidade *unidade1 = criarUnidade("Clientes.DBF", "10/02/2025", "14:30");
    adicionarCampo(unidade1, criarCampo("Nome", 'C', 50, 0));
    adicionarCampo(unidade1, criarCampo("Idade", 'N', 3, 0));
    adicionarCampo(unidade1, criarCampo("Saldo", 'N', 10, 2));
    adicionarUnidade(*base, unidade1);

    dUnidade *unidade2 = criarUnidade("Pedidos.DBF", "10/02/2025", "15:00");
    adicionarCampo(unidade2, criarCampo("ID Pedido", 'N', 5, 0));
    adicionarCampo(unidade2, criarCampo("Valor", 'N', 10, 2));
    adicionarUnidade(*base, unidade2);

    exibirBase(*base);
}

