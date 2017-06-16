#ifndef Produtos_h
#define Produtos_h

typedef struct CatProd* CATALOGOPROD;
typedef struct InfoProd* APRODUTOS;
typedef struct _produto* produto_t;
typedef char* CodigoProd;
typedef struct dadosProd* DadosProd;

/** CATALOGO **/
struct CatProd* iniciarCATALOGOPROD();
struct CatProd* iniciarPROD();
int indiceCatProd (CodigoProd);
produto_t  addProdutoCat (CodigoProd);
void addCatProd (CATALOGOPROD,CodigoProd);
int existeProd(char *p,APRODUTOS prod);
void apagarCATALOGOPROD(CATALOGOPROD);
void apagarInfoProd(struct InfoProd *);
void apagaProduto (produto_t);

/** Lista de Produtos **/
void addDadosProd(DadosProd ,APRODUTOS);
void adicionaProduto (DadosProd a,produto_t);
DadosProd iniciarDadosProd(int );
DadosProd criarDadosProd (char *,CATALOGOPROD);
void apagarDadosProd(DadosProd);

/* Gets */
int getSizeCatProd (CATALOGOPROD);

APRODUTOS getInfoCatProd (CATALOGOPROD,int);
produto_t getProdutoInfoProd (APRODUTOS p);
struct InfoProd *getSegInfoProd (APRODUTOS p);
struct InfoProd *getAntInfoProd (APRODUTOS p);

 
CodigoProd getCodProduto(produto_t);
produto_t cpyProd(CodigoProd);
int cmpProd (produto_t,produto_t);
CodigoProd getCodProdInfoProd (APRODUTOS p);

int getOcupadosDadosProd (DadosProd);
CodigoProd getProdDadosProd (DadosProd,int);
int getPaginaDadosProd (DadosProd);
int getNpagDadosProd (DadosProd);
void irParaPagDadosProd (DadosProd,int);

CodigoProd iniciaProduto();
DadosProd iniciaDados ();
int isEmptyProd(CodigoProd);

#endif

