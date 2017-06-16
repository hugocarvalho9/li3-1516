#ifndef Clientes_h
#define Clientes_h

typedef struct infoCli*  CATALOGOCLI;
typedef struct dadosCli* CLIENTES;

typedef char* CodigoCli;

struct _cliente;
typedef struct _cliente* cliente_t;

int existeCli(CodigoCli,CATALOGOCLI);

CLIENTES iniciarDadosCli();
cliente_t cpyCli (CodigoCli c);
int cmpCli (cliente_t,cliente_t);

int getOcupadosDadosCli (CLIENTES);
int getSizeDadosCli (CLIENTES);
CodigoCli getCodCliDadosCli (struct dadosCli*,int);
void addClienteDadosCli (struct dadosCli*,CodigoCli);
void apagarDadosCli(CLIENTES);
void irParaPagDadosCli (CLIENTES,int);
int getPaginaDadosCli (CLIENTES);
int getNpagDadosCli (CLIENTES);


CATALOGOCLI iniciarCATALOGOCLI();
CATALOGOCLI addCliInfoCli (CATALOGOCLI,CodigoCli,int *);
void apagarCatalogoCli(CATALOGOCLI);
CATALOGOCLI  getInfoCliDir (CATALOGOCLI);
CATALOGOCLI  getInfoCliEsq (CATALOGOCLI);
cliente_t getClienteCli (CATALOGOCLI);
CodigoCli getCodigoCli (cliente_t);

void apagarCliente (cliente_t);

CATALOGOCLI iniciaCatalogo();
int isEmptyCli (CodigoCli );

#endif




