#ifndef Filial_h
#define Filial_h
#include "Clientes.h"
#include "Produtos.h"

typedef struct infoFilial* InfoFilial;

typedef struct CatFilial* MODULOFILIAL;

typedef struct filial* Filial;

void addCatFilial (MODULOFILIAL*,char *);
MODULOFILIAL iniciarModuloFilial();
int indiceCatFilial (CodigoCli);
void apagarInfoFilial(InfoFilial);
void apagarModuloFilial (MODULOFILIAL);

/* Querie 4 */
void queri4ProdF(MODULOFILIAL *,CATALOGOPROD,DadosProd *,DadosProd *,DadosProd *);

/* Querie 5 */
void querie5aux(CodigoCli, int [3][12],MODULOFILIAL *);

/* Querie 7 */
void clienteTodosFiliais(CATALOGOCLI,MODULOFILIAL *, CLIENTES);

/* QUerie 8 */
void querie8aux (CodigoProd,MODULOFILIAL *,int,CLIENTES,CLIENTES);

/* Querie 12 */
void cliSemCompras(CATALOGOCLI,MODULOFILIAL *, CLIENTES);

#endif
