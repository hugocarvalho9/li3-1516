#ifndef Faturacao_h
#define Faturacao_h
#include "Produtos.h"

typedef struct infoVenda* VENDAS;

typedef struct CatVenda* FATURACAO;

typedef struct venda* Vendas;

/* Funções de manipulação de estructuras */

Vendas alocarVendas (char *);
void addCatVenda (FATURACAO ,char *);
struct CatVenda *iniciarFATURACAO();
int indiceCatVenda (CodigoProd);
void apagarInfoVendas(struct infoVenda*);
void apagarFATURACAO (FATURACAO );

/* Querie3 */
void querie3F(FATURACAO,int,CodigoProd,float [2][4],int [2][4]);

/* Querie4 */
void queri4ProdG(FATURACAO,CATALOGOPROD,DadosProd *);
int existeProdFaturacao(CodigoProd, FATURACAO);
/* Queri6 */
int auxquerie6(FATURACAO, int, int, double*);
    
#endif
