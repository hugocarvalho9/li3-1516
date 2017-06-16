#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Filial.h"

#define SIZEHASH 26

typedef enum balancefactor { ESQUERDA , EQUILIBRADO , DIREITA } BalanceFactor;

/** Estrutura para cada linha de Filial **/
typedef struct filial {
    produto_t prod;
    double preco;
    int und;
    char tipo;
    int mes;
    cliente_t cli;
    int filial;
}*Filial;

/** Nodos da Árvore **/
typedef struct infoFilial {
    Filial filial;
    BalanceFactor eql;
    struct infoFilial *dir,*esq;
}*NodoFilial;

/** Estructura da Cat **/
typedef struct CatFilial {
    int size;
    int ocupado;
    NodoFilial filial[SIZEHASH];
}*HashFilial;

/* Array de produtosVendidos */
typedef struct produtoV{
    produto_t codigo;
    int nClientes;
    int unidades;
}*ProdutoV;

/** Funções de addição de nodos á átvore **/
struct filial *alocarFilial (char *);
struct infoFilial *insereFilial (struct infoFilial *,struct filial*,int *);
struct infoFilial *insereEsqFilial (struct infoFilial *,struct filial*,int *);
struct infoFilial *insereDirFilial (struct infoFilial *,struct filial*,int *);
struct infoFilial *equiEsqFilial (struct infoFilial *);
struct infoFilial *equiDirFilial (struct infoFilial *);
struct infoFilial *rodaEsqFilial (struct infoFilial *);
struct infoFilial *rodaDirFilial (struct infoFilial *);


/** Funções da Cat **/

/** Gets da hash **/
int getSizeCatFil (HashFilial f){
    return f->size;
}

int getOcupadosCatFil (HashFilial f){
    return f->ocupado;
}

NodoFilial getInfoCatFil (HashFilial f,int indece){
    return f->filial[indece];
}

struct CatFilial *iniciarModuloFilial(){
    HashFilial cat = (HashFilial) malloc(sizeof(struct CatFilial));
    cat->size = SIZEHASH;
    cat->ocupado = 0;
    int i = 0;
    while (i < cat->size)
        cat->filial[i++] = NULL;
    return cat;
}

int indiceCatFilial(CodigoCli p){
    int r = (p[0] - 65);
    return r;
}

/* adição de um código de filial na estrutura Cat */
void addCatFilial (MODULOFILIAL *h, char *linha){
    Filial f = alocarFilial(linha);
    if (f != NULL) {
        int i = indiceCatFilial(getCodigoCli(f->cli));
        int fil = f->filial-1;
        int *cresceu = malloc(sizeof(int));
        *cresceu = 0;
        (h[fil])->ocupado++;
        (h[fil])->filial[i] = insereFilial((h[fil])->filial[i], f, cresceu);
        free(cresceu);
    }
}


/** Funções da árvore **/

/** Gets de árvores **/

produto_t getProdutoFil (Filial f) {return f->prod;}

cliente_t getClienteFil (Filial f) {return f->cli;}

int getUndFil (Filial f) {return f->und;}

int getFilialFil (Filial f) {return f->filial;}

int getMesFil (Filial f) {return f->mes;}

double getPrecoFil (Filial f) {return f->preco;}

char getTipoFil (Filial f) {return f->tipo;}


Filial alocarFilial (char *linha) {
    char *aux;
    Filial new = (Filial)malloc(sizeof(struct filial));
    aux = strtok(linha," ");
    new->prod =cpyProd(aux);                       /* Aloca o código do produto */
    new->preco = atof(strtok(NULL," "));          /* Aloca o valor do preço */
    new->und = atoi(strtok(NULL," "));            /* Aloca o número de unidades do produto */
    new->tipo = *strtok(NULL," ");                /* Aloca o tipo de venda */
    aux = strtok(NULL," ");
    new->cli = cpyCli(aux);                       /* Aloca o código do cliente */
    new->mes = atoi(strtok(NULL," "));            /* Aloca o mês */
    new->filial = atoi(strtok(NULL," \r\n"));     /* Aloca o filial */
    return new;
}

/* Inserção de um infoFilial á árvore */
NodoFilial insereFilial (NodoFilial filial, Filial f, int *cresceu){
    if(filial == NULL){
        filial = (NodoFilial) malloc(sizeof(struct infoFilial));
        filial->eql = EQUILIBRADO;
        filial->filial = f;
        filial->esq = NULL;
        filial->dir = NULL;
        *cresceu = 1;
    }
    else {
        int dif = strcmp(getCodigoCli(f->cli), getCodigoCli(filial->filial->cli));
        if(dif > 0)
            filial = insereDirFilial(filial, f, cresceu);
        else
            if(dif < 0)
                filial = insereEsqFilial(filial, f, cresceu);
            else
                filial = insereEsqFilial(filial, f, cresceu);
    }
    return filial;
}

NodoFilial insereEsqFilial(NodoFilial p, Filial v, int *cresceu){
    p->esq = insereFilial(p->esq, v, cresceu);
    if(*cresceu)
        switch (p->eql) {
            case DIREITA:
                p->eql = EQUILIBRADO;
                *cresceu = 0;
                break;
            case EQUILIBRADO:
                p->eql = ESQUERDA;
                *cresceu = 1;
                break;
            case ESQUERDA:
                p = equiEsqFilial(p);
                *cresceu = 0;
                break;
        }
    return p;
}

NodoFilial insereDirFilial(NodoFilial p, Filial v, int *cresceu){
    p->dir = insereFilial(p->dir, v, cresceu);
    if(*cresceu)
        switch (p->eql) {
            case ESQUERDA:
                p->eql = EQUILIBRADO;
                *cresceu = 0;
                break;
            case EQUILIBRADO:
                p->eql = DIREITA;
                *cresceu = 1;
                break;
            case DIREITA:
                p = equiDirFilial(p);
                *cresceu = 0;
                break;
        }
    return p;
}


struct infoFilial *equiDirFilial(NodoFilial p){
    if(p->dir->eql == DIREITA){
        p = rodaEsqFilial(p);
        p->eql = EQUILIBRADO;
        p->esq->eql = EQUILIBRADO;
    }
    else {
        p->dir = rodaDirFilial(p->dir);
        p = rodaEsqFilial(p);
        switch (p->eql) {
            case EQUILIBRADO:
                p->esq->eql = EQUILIBRADO;
                p->dir->eql = EQUILIBRADO;
                break;
            case ESQUERDA:
                p->esq->eql = EQUILIBRADO;
                p->dir->eql = DIREITA;
                break;
            case DIREITA:
                p->esq->eql = ESQUERDA;
                p->dir->eql = EQUILIBRADO;
        }
        p->eql = EQUILIBRADO;
    }
    return p;
}

struct infoFilial *rodaDirFilial(NodoFilial p){
    NodoFilial aux = NULL;
    if((!p) || (!p->esq));
    else {
        aux = p->esq;
        p->esq = aux->dir;
        aux->dir = p;
        p = aux;
    }
    return p;
}

NodoFilial equiEsqFilial(NodoFilial p){
    if(p->esq->eql == ESQUERDA){
        p = rodaDirFilial(p);
        p->eql = EQUILIBRADO;
        p->dir->eql = EQUILIBRADO;
    }
    else {
        p->esq = rodaEsqFilial(p->esq);
        p = rodaDirFilial(p);
        switch (p->eql) {
            case EQUILIBRADO:
                p->dir->eql = EQUILIBRADO;
                p->esq->eql = EQUILIBRADO;
                break;
            case DIREITA:
                p->dir->eql = EQUILIBRADO;
                p->esq->eql = ESQUERDA;
                break;
            case ESQUERDA:
                p->dir->eql = DIREITA;
                p->esq->eql = EQUILIBRADO;
        }
        p->eql = EQUILIBRADO;
    }
    return p;
}


NodoFilial rodaEsqFilial(NodoFilial p){
    NodoFilial aux = NULL;
    if((!p) || (!p->dir));
    else {
        aux = p->dir;
        p->dir = aux->esq;
        aux->esq = p;
        p = aux;
    }
    return p;
}

void apagarInfoFilial(NodoFilial v){
    if(v != NULL){
        apagarInfoFilial(v->dir);
        v->dir = NULL;
        apagarInfoFilial(v->esq);
        v->esq = NULL;
        apagaProduto(v->filial->prod);
        v->filial->prod = NULL;
        apagarCliente(v->filial->cli);
        v->filial->cli=NULL;
        free(v->filial);
        v->filial = NULL;
        free(v);
    }
}

void apagarModuloFilial(MODULOFILIAL catalogo){
    int i = 0;
    while (i < (catalogo->size)) {
        apagarInfoFilial(catalogo->filial[i]);
        catalogo->filial[i] = NULL;
        i++;
    }
}

/* QUERIE 4 */
/*
void queri4ProdF(CATALOGOModuloFilial f,CATALOGOPROD pd,DadosProd *p0,DadosProd *p1,DadosProd *p2){
    int i=0;
    *p0 = iniciarDadosProd(10);
    *p1 = iniciarDadosProd(10);
    *p2 = iniciarDadosProd(10);
    
    while (i<getSizeCatProd(pd)) {
        percoreInfoProdF(getArvCatProd(pd, i),f[0],p0);
        i++;
    }
    i=0;
    while (i<getSizeCatProd(pd)) {
        percoreInfoProdF(getArvCatProd(pd, i),f[1],p1);
        i++;
    }
    i=0;
    while (i<getSizeCatProd(pd)) {
        percoreInfoProdF(getArvCatProd(pd, i),f[2],p2);
        i++;
    }
    i=0;
}

void percoreInfoProdF (struct nodoProd *p,ModuloFilial f,DadosProd *p0){
    if (p!=NULL) {
        percoreInfoProdF(getDirArvProd(p),f,p0);
        if (!existeProdFilial(getProdutoArvProd(p),f))
            adicionaProduto(*p0, getProdutoArvProd(p));
        percoreInfoProdF(getEsqArvProd(p),f,p0);
    }
}

int existeProdFilial(Produto p, ModuloFilial f) {
    int r=0,ind=0;
    while (r==0 && ind<26) {
        r+=existeProdArvFilial(p, f->filial[ind]);
        ind++;
    }
    return r;
}

int existeProdArvFilial(Produto p, NodoFilial v) {
    int r=0;
    if(v!=NULL){
        int dif = strcmp(p, v->filial->prod);
        if (dif == 0)
            r++;
        if (r==0)
            r+=existeProdArvFilial(p, v->dir);
        if (r==0)
            r+=existeProdArvFilial(p, v->esq);
        return r;
    }
    return r;
}
*/

/* QUERIE 5 */
void querie5PER (NodoFilial v, int prod_filial[3][12],CodigoCli cl) {
    if (v!=NULL) {
        int dif = strcmp(getCodigoCli(v->filial->cli),cl);
        if (dif<0)
            querie5PER(v->dir, prod_filial, cl);
        else
            if (dif>0)
                querie5PER(v->esq, prod_filial, cl);
            else {
                prod_filial[v->filial->filial-1][v->filial->mes-1] += v->filial->und;
                querie5PER(v->dir, prod_filial, cl);
                querie5PER(v->esq, prod_filial, cl);
            }
    }
}

void querie5aux(CodigoCli cl, int prod_filial[3][12],MODULOFILIAL *filial) {
    int indice = indiceCatFilial(cl);
    int i;
    
    for (i=0; i<3 ; i++)
        querie5PER(filial[i]->filial[indice], prod_filial,cl);
}

/* Queri 7 */
int auxClienteTodosFiliais(cliente_t c, NodoFilial f,CLIENTES a) {
    int r = 0;
    if(f != NULL) {
        int dif = cmpCli(c,f->filial->cli);
        if(dif > 0)
            r += auxClienteTodosFiliais(c, f->dir,a);
        else
            if(dif < 0)
                r += auxClienteTodosFiliais(c, f->esq,a);
            else {
                r++;
                return r;
            }
    }
    return r;
}

void clienteTodosFiliais(CATALOGOCLI c ,MODULOFILIAL *f, CLIENTES a) {
    int indice=0;
    if (c != NULL) {
        clienteTodosFiliais(getInfoCliEsq(c), f, a);
        indice = indiceCatFilial(getCodigoCli(getClienteCli(c)));
        if ( auxClienteTodosFiliais(getClienteCli(c), f[0]->filial[indice], a) &&
            auxClienteTodosFiliais(getClienteCli(c), f[1]->filial[indice], a) &&
            auxClienteTodosFiliais(getClienteCli(c), f[2]->filial[indice], a)) {
            addClienteDadosCli(a,getCodigoCli(getClienteCli(c)));
        }
        clienteTodosFiliais(getInfoCliDir(c), f, a);
    }
}

/* QUERIE 8 */
void querie8busca (NodoFilial v,CodigoProd p, CLIENTES prom, CLIENTES norm) {
    if (v!=NULL && v->filial!=NULL) {
        querie8busca(v->esq,p,prom,norm);
        int n = strcmp(getCodProduto(v->filial->prod), p);
        if (n==0) {
            if (v->filial->tipo == 'N')
                addClienteDadosCli(norm,getCodigoCli(v->filial->cli));
            else
                addClienteDadosCli(prom,getCodigoCli(v->filial->cli));
        }
        querie8busca(v->dir, p, prom, norm);
    }
}

void querie8aux (CodigoProd p,MODULOFILIAL *filial,int f, CLIENTES prom, CLIENTES norm) {
    int i;
    for (i=0 ; i<26 ; i++) {
        querie8busca((filial[f-1])->filial[i], p, prom, norm);
    }
    
}

/* Querie12 */
void cliSemCompras(CATALOGOCLI c ,MODULOFILIAL *f, CLIENTES a) {
    int indice=0;
    if (c != NULL) {
        cliSemCompras(getInfoCliEsq(c), f, a);
        indice = indiceCatFilial(getCodigoCli(getClienteCli(c)));
        if ( !auxClienteTodosFiliais(getClienteCli(c), f[0]->filial[indice], a) ||
             !auxClienteTodosFiliais(getClienteCli(c), f[1]->filial[indice], a) ||
             !auxClienteTodosFiliais(getClienteCli(c), f[2]->filial[indice], a) ) {
              addClienteDadosCli(a,getCodigoCli(getClienteCli(c)));
        }
        cliSemCompras(getInfoCliDir(c), f, a);
    }
}