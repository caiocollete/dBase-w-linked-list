#define MAXNAME 64
#define MAXDATA 10
#define MAXHORA 5
#define MAXFIELDNAME 64

struct tppdados{
	int ValorN;
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
	bool Status;
	struct tpstatus *prox;
};
typedef struct tpstatus Status;

struct tpunidade{
	struct tpunidade *ant, *prox;
	char NomeDBF[MAXNAME];
	char Data[MAXDATA]; // "01/01/2000"
	char Hora[MAXHORA]; // "00:00"
	struct tpstatus *Status;
};
typedef struct tpunidade dUnidade;

struct tpdbase{
	struct tpdbase *ant, *prox;
	char disco[2]; // "C:"
	struct tpunidade *unidade;
};
typedef struct tpdbase dBase;
