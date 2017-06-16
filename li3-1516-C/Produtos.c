#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Produtos.h"

#define SIZEHASH 26
#define SIZEARRAY 1000
#define PAGINA 20

typedef struct _produto {
    CodigoProd codigo;
}*produto;

typedef enum balancefactor { ESQUERDA , EQUILIBRADO , DIREITA } BalanceFactor;

/** Estructura da Árvore **/
typedef struct InfoProd {
    produto prod;
    BalanceFactor eql;
    struct InfoProd *esq, *dir;
}*NodoProd;

/** Estructura da Hash **/
typedef struct CatProd {
    int size;
    int ocupado;
    NodoProd codProdutos[SIZEHASH];
}*CatProd;

typedef struct dadosProd{
    int size;
    int ocupado;
    int pagina;
    int npag;
    produto *produtos;
}*Array;


/* Funções internas de adição de nodos á árvore */
struct InfoProd *insereProd (struct InfoProd *,produto_t,int *);
struct InfoProd *insereEsqProd (struct InfoProd *,produto_t,int *);
struct InfoProd *insereDirProd (struct InfoProd *,produto_t,int *);
struct InfoProd *equiEsqProd (struct InfoProd *);
struct InfoProd *equiDirProd (struct InfoProd *);
struct InfoProd *rodaDirProd (struct InfoProd *);
struct InfoProd *rodaEsqProd (struct InfoProd *);


/*  *   *   *   *   *   *   *   *   *   Funções da Hash     *   *   *   *   *   *   *   *   *   */

/** Gets da hash **/
int getSizeCatProd (CatProd p){
    return p->size;
}

int getOcupadosCatProd (CatProd p){
    return p->ocupado;
}

APRODUTOS getInfoCatProd (CatProd h,int ind){
    return h->codProdutos[ind];
}

CatProd iniciarCATALOGOPROD(){
    return NULL;
}

CatProd iniciarPROD(){
    CatProd cat = malloc(sizeof(struct CatProd));
    cat->size=SIZEHASH;
    cat->ocupado=0;
    int i=0;
    while (i<cat->size)
        cat->codProdutos[i++]=NULL;
    return cat;
}

/* O indice é determinado segundo os 2 primeiros caracteres */
int indiceCatProd (CodigoProd p){
    /*int r=(p[0]-65)*26+(p[1]-65);*/
    int r=(p[0]-65);
    return r;
}

produto_t  addProdutoCat (CodigoProd p){
    produto new = malloc(sizeof(struct _produto));
    new->codigo = malloc(sizeof(char)*(strlen(p)+1));
    strcpy(new->codigo, p);
    return new;
}

/* Inserção do produto no array/Hash*/
void addCatProd (CatProd h,CodigoProd p){
    if (p!=NULL) {
        /*Índice determina a posição da árvore onde o produto será colocado */
        produto prod = addProdutoCat(p);
        int i=indiceCatProd(p);
        int *cresceu=malloc(sizeof(int));
        *cresceu=0;
        h->ocupado++;
        h->codProdutos[i]=insereProd(h->codProdutos[i], prod, cresceu);
        free(cresceu);
    }
}

/* Dado um produto e uma árvore a função verefica se este esta na árvore */
int existeProd(CodigoProd p,APRODUTOS prod){
    int dif=0;
    if(prod!=NULL && prod->prod!=NULL){
        dif = strcmp(p,prod->prod->codigo);
        if(dif == 0)
            return 1;
        else
            if(dif > 0)
                return existeProd(p,prod->dir);
            else
                return existeProd(p,prod->esq);
    }
    return 0;
}

/*  *   *   *   *   *   *   *   *   *    Funções da árvore de produtos   *  *   *   *   *   *   *   *   *   */

/** Gets das árvores **/
CodigoProd getCodProduto (produto p){
    return p->codigo;
}

produto getProdutoInfoProd (APRODUTOS p){
    return p->prod;
}

CodigoProd getCodProdInfoProd (APRODUTOS p){
    return p->prod->codigo;
}

NodoProd getSegInfoProd (APRODUTOS p){
    return p->dir;
}

NodoProd getAntInfoProd (APRODUTOS p){
    return p->esq;
}

produto cpyProd(CodigoProd p){
    produto new = malloc(sizeof(struct _produto));
    new->codigo = malloc(sizeof(char)*(strlen(p)+1));
    strcpy(new->codigo, p);
    return new;
}

void cpy2Prod (produto p1,produto p2){
    strcpy(p1->codigo,p2->codigo);
}

int cmpProd(produto_t p1,produto_t p2){
    return (strcmp(getCodProduto(p1),getCodProduto(p2)));
}

NodoProd insereProd (NodoProd p,produto_t cod,int *cresceu){
    if(p==NULL){
        p = (struct InfoProd *)malloc (sizeof(struct InfoProd));
        p->prod = cod;
        p->eql = EQUILIBRADO;
        p->esq = NULL;
        p->dir = NULL;
        *cresceu =1;
    }
    else {
        int dif = cmpProd(cod,p->prod);
        if(dif>0)
            p=insereDirProd(p,cod,cresceu);
        else
            if(dif<0)
                p=insereEsqProd(p,cod,cresceu);
            else
                return p;
    }
    return p;
}

NodoProd insereEsqProd (NodoProd p,produto cod,int *cresceu){
    p->esq = insereProd(p->esq,cod,cresceu);
    if(*cresceu)
        switch (p->eql) {
            case DIREITA:
                p->eql=EQUILIBRADO;
                *cresceu=0;
                break;
            case EQUILIBRADO:
                p->eql=ESQUERDA;
                *cresceu=1;
                break;
            case ESQUERDA:
                p=equiEsqProd(p);
                *cresceu=0;
                break;
        }
    return p;
}

NodoProd insereDirProd (NodoProd p,produto cod,int *cresceu){
    p->dir = insereProd(p->dir,cod,cresceu);
    if(*cresceu)
        switch (p->eql) {
            case ESQUERDA:
                p->eql=EQUILIBRADO;
                *cresceu=0;
                break;
            case EQUILIBRADO:
                p->eql=DIREITA;
                *cresceu=1;
                break;
            case DIREITA:
                p=equiDirProd(p);
                *cresceu=0;
                break;
        }
    return p;
}

NodoProd equiDirProd (NodoProd p){
    if(p->dir->eql == DIREITA){
        p=rodaEsqProd(p);
        p->eql=EQUILIBRADO;
        p->esq->eql=EQUILIBRADO;
    }
    else {
        p->dir = rodaDirProd(p->dir);
        p=rodaEsqProd(p);
        switch (p->eql) {
            case EQUILIBRADO:
                p->esq->eql = EQUILIBRADO;
                p->dir->eql = EQUILIBRADO;
                break;
            case ESQUERDA:
                p->esq->eql=EQUILIBRADO;
                p->dir->eql=DIREITA;
                break;
            case DIREITA:
                p->esq->eql=ESQUERDA;
                p->dir->eql=EQUILIBRADO;
        }
        p->eql = EQUILIBRADO;
    }
    return p;
}

NodoProd rodaDirProd (NodoProd p){
    NodoProd aux=NULL;
    if((!p) || (!p->esq));
    else {
        aux=p->esq;
        p->esq=aux->dir;
        aux->dir=p;
        p=aux;
    }
    return p;
}

NodoProd equiEsqProd (NodoProd p){
    if(p->esq->eql == ESQUERDA){
        p=rodaDirProd(p);
        p->eql=EQUILIBRADO;
        p->dir->eql=EQUILIBRADO;
    }
    else {
        p->esq = rodaEsqProd(p->esq);
        p=rodaDirProd(p);
        switch (p->eql) {
            case EQUILIBRADO:
                p->dir->eql = EQUILIBRADO;
                p->esq->eql = EQUILIBRADO;
                break;
            case DIREITA:
                p->dir->eql=EQUILIBRADO;
                p->esq->eql=ESQUERDA;
                break;
            case ESQUERDA:
                p->dir->eql=DIREITA;
                p->esq->eql=EQUILIBRADO;
        }
        p->eql = EQUILIBRADO;
    }
    return p;
}


NodoProd rodaEsqProd(NodoProd p){
    NodoProd aux=NULL;
    if((!p) || (!p->dir));
    else {
        aux=p->dir;
        p->dir=aux->esq;
        aux->esq=p;
        p=aux;
    }
    return p;
}

void apagarCATALOGOPROD (CATALOGOPROD catalogo){
    int i=0;
    while (i<(catalogo->size)) {
        apagarInfoProd(catalogo->codProdutos[i]);
        catalogo->codProdutos[i]=NULL;
        i++;
    }
}

void apagarInfoProd(NodoProd p){
    if(p!=NULL){
        apagarInfoProd(p->dir);
        p->dir=NULL;
        apagarInfoProd(p->esq);
        p->esq=NULL;
        apagaProduto(p->prod);
        free(p);
    }
}

void apagaProduto (produto p){
    if (p!=NULL) {
        if (p->codigo!=NULL)
            free(p->codigo);
        p->codigo=NULL;
        free(p);
        p=NULL;
    }
}


/*  *   *   *   *   *   __QUERI2__  *   *   *   *   *   */

/* A função apenas procura o 1º produto que começa por um dado caractere */
NodoProd procuraProd (char *l,NodoProd p) {
    CodigoProd codigo = getCodProduto(p->prod);
    if(p!=NULL){
        if((*l)>(codigo[0]))
            p=procuraProd(l,p->dir);
        else
            if((*l)<(codigo[0]))
                p=procuraProd(l,p->esq);
        return p;
    }
    return NULL;
}

/****   *   *Funções para gerir o array De produtos*   *    ****/

/* Inicialização do array usado na queri2 */
DadosProd iniciarDadosProd(int size){
    DadosProd a = malloc(sizeof(struct dadosProd));
    a->produtos = malloc(sizeof(struct _produto)*size);
    a->ocupado=0;
    a->pagina=0;
    a->npag=PAGINA;
    a->size=size;
    return a;
}

/* A função copia os produtos das 26 posições da hash de árvores para o array*/
DadosProd criarDadosProd (char *l,CATALOGOPROD p){
    int n;
    n=indiceCatProd(l);
    DadosProd a=iniciarDadosProd(SIZEARRAY);
    NodoProd aux=p->codProdutos[n++];
    if(aux!=NULL)
        addDadosProd(a,aux);
    return a;
}
/* Funçaõ auxiliar da função criaDadosProd que faz a adição de um produto de uma árvore ao array */
void addDadosProd(DadosProd a,NodoProd p) {
    if (p!=NULL && p->prod!=NULL) {
        if (a->ocupado>=a->size-1) {
            (a->size)*=2;
            a->produtos = realloc(a->produtos,(sizeof(struct _produto)*(a->size))+sizeof(int)*2);
        }
        addDadosProd(a, p->esq);
        a->produtos[a->ocupado]=cpyProd(getCodProduto(p->prod));
        a->ocupado++;
        addDadosProd(a, p->dir);
    }
}

void adicionaProduto (DadosProd a,produto p){
    if (p!=NULL) {
        if (a->ocupado>=a->size-1) {
            (a->size)*=2;
            a->produtos = realloc(a->produtos,(sizeof(struct _produto)*(a->size))+sizeof(int)*2);
        }
        a->produtos[a->ocupado]=cpyProd(p->codigo);
        a->ocupado++;
    }
}

/* Função que copia o produto alocando memória para inserir no array */
produto cpyInfoProd(NodoProd p){
    CodigoProd codigo = getCodProduto(p->prod);
    if (p!=NULL && codigo[0]!='\0') {
        produto prod=NULL;
        prod = cpyProd(getCodProduto(p->prod));
        return prod;
    }
    return NULL;
}

int getOcupadosDadosProd (DadosProd a){
    return a->ocupado;
}

int getSizeDadosProd (DadosProd a){
    return a->size;
}

int getPaginaDadosProd (DadosProd a){
    return a->pagina;
}

int getNpagDadosProd (DadosProd a){
    return a->npag;
}

CodigoProd getProdDadosProd (DadosProd a,int ind){
    return getCodProduto(a->produtos[ind]);
}


void irParaPagDadosProd (Array a,int i){
    a->pagina=i*PAGINA;
}


/*Função para libertar memória do array*/
void apagarDadosProd(DadosProd a){
    int i=0;
    while (i<a->ocupado) {
        if (a->produtos[i]!=NULL)
            free(a->produtos[i]);
        a->produtos[i]=NULL;
        i++;
    }
    a->ocupado=0;
    free(a->produtos);
    free(a);
}


CodigoProd iniciaProduto() {
    return NULL;
}

DadosProd iniciaDados () {
    return NULL;
}

int isEmptyProd(CodigoProd p) {
    return (p == NULL);
}
