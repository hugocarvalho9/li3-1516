#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Clientes.h"

#define SIZEARRAY 20
#define PAGINA 20

typedef struct _cliente {
    CodigoCli codigo;
}*cliente;

typedef enum balancefactor { ESQUERDA , EQUILIBRADO , DIREITA } BalanceFactor;

typedef struct infoCli {
    cliente cli;
    BalanceFactor eql;
    struct infoCli *esq, *dir;
}*InfoCli;

typedef struct dadosCli{
    int size;
    int ocupado;
    int pagina;
    int npag;
    cliente *cliente;
}*DadosCli;

/** Funções de adição de nodos á árvore **/
CATALOGOCLI insereCli (CATALOGOCLI,cliente_t,int *);
CATALOGOCLI insereEsqCli (CATALOGOCLI,cliente_t,int *c);
CATALOGOCLI insereDirCli (CATALOGOCLI,cliente_t,int *c);
CATALOGOCLI  equiEsqCli (CATALOGOCLI);
CATALOGOCLI equiDirCli (CATALOGOCLI);
CATALOGOCLI rodaDirCli (CATALOGOCLI);
CATALOGOCLI  rodaEsqCli (CATALOGOCLI);


/** Gets da Lista **/
int getOcupadosDadosCli (DadosCli a){
    return a->ocupado;
}

int getSizeDadosCli (DadosCli a){
    return a->size;
}

int getPaginaDadosCli (DadosCli a){
    return a->pagina;
}

int getNpagDadosCli (DadosCli a){
    return a->npag;
}

CodigoCli getCodCliDadosCli (DadosCli a,int ind){
    return a->cliente[ind]->codigo;
}

void irParaPagDadosCli (CLIENTES a,int i){
    a->pagina=i*PAGINA;
}

/** Funções da Lista **/
DadosCli iniciarDadosCli(){
    DadosCli a = malloc(sizeof(struct dadosCli));
    a->cliente = malloc(sizeof(struct _cliente)*SIZEARRAY);
    a->ocupado=0;
    a->pagina=0;
    a->npag=PAGINA;
    a->size=SIZEARRAY;
    return a;
}

cliente cpyCli (CodigoCli c){
    cliente new = malloc(sizeof(struct _cliente));
    new->codigo = malloc(sizeof(char)*(strlen(c)+1));
    strcpy(new->codigo,c);
    return new;
}


void addClienteDadosCli (DadosCli a,CodigoCli p){
    if (p!=NULL) {
        if (a->ocupado>=a->size-1) {
            (a->size)*=2;
            a->cliente = realloc(a->cliente,(sizeof(struct _cliente)*(a->size))+sizeof(int)*2);
        }
        (a->cliente[a->ocupado])=cpyCli(p);
        a->ocupado++;
    }
}

int cmpCli (cliente_t c1,cliente_t c2){
    return strcmp(c1->codigo, c2->codigo);
}


void apagarDadosCli(DadosCli a){
    int i=0;
    while (i<a->ocupado) {
        if (a->cliente[i]!=NULL)
            free(a->cliente[i]);
        a->cliente[i]=NULL;
        i++;
    }
    a->ocupado=0;
    free(a->cliente);
    free(a);
}


/*  *   *   *   *   *   Funções relacionadas com a estrutura de dados   *   *   *   *   *   */

/** Gets da estructura/Catalogo **/
InfoCli getInfoCliDir (InfoCli c){
    return c->dir;
}

InfoCli getInfoCliEsq (InfoCli c){
    return c->esq;
}

cliente_t getClienteCli (InfoCli c){
    return c->cli;
}

CodigoCli getCodigoCli (cliente_t c){
    return c->codigo;
}

/* Função que verefica se o cliente se encontra na árvore */
int existeCli(CodigoCli c,CATALOGOCLI cli) {
    int dif = 0;
    if (cli!=NULL && cli->cli!=NULL && cli->cli->codigo!=NULL) {
            dif = strcmp(c,cli->cli->codigo);
            if (dif == 0)
                return 1;
            else
                if (dif > 0)
                    return existeCli(c,cli->dir);
                else
                    return existeCli(c,cli->esq);
    }
    return 0;
}

/* Inserção de um cliente na árvore */
/* Exemplo 
        (A3439)
          / \
    (A3401) (B6149)

*/
InfoCli addCliInfoCli (InfoCli c,CodigoCli cod,int *cresceu){
    cliente_t cli = malloc(sizeof(struct _cliente));
    cli->codigo = malloc(sizeof(char)*(strlen(cod)+1));
    strcpy(cli->codigo,cod);
    c = insereCli(c,cli,cresceu);
    return c;
}


InfoCli insereCli(InfoCli p,cliente_t cli, int *cresceu) {
    if(p == NULL || p->cli==NULL) {
        if (p!=NULL){
            free(p);
            p=NULL;
        }
        p = (struct infoCli *) malloc(sizeof(struct infoCli));
        p->cli = malloc(sizeof(struct _cliente));
        p->cli = cli;
        p->eql = EQUILIBRADO;
        p->esq = NULL;
        p->dir = NULL;
        *cresceu = 1;
    }
    else {
        /* Sendo a árvore uma arvore binária de procura, é necessario organizar cada cliente consoante o seu código. */
        int dif = strcmp(getCodigoCli(cli),p->cli->codigo);
        if(dif > 0)
            /* Os códigos são ordenados alfabeticamente da esquerda para a direita. */
            /* Os maiores ficam à direita. */
            p = insereDirCli(p,cli,cresceu);
        else
            if(dif < 0)
                /* Os menores ficam à esquerda */
                p = insereEsqCli(p,cli,cresceu);
            else
                return p;
    }
    return p;
}

/* Função auxiliar da função insere Cli para inserir o código do cliente de modo a manter a árvore balanceada. */
InfoCli insereEsqCli(InfoCli p,cliente_t cod, int *cresceu) {
    p->esq = insereCli(p->esq, cod, cresceu);
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
                p = equiEsqCli(p);
                *cresceu = 0;
                break;
        }
    return p;
}

/* Função auxiliar da função insere Cli para inserir o código do cliente de modo a manter a árvore balanceada*/
InfoCli insereDirCli(InfoCli p,cliente_t cod, int *cresceu) {
    p->dir = insereCli(p->dir, cod, cresceu);
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
                p = equiDirCli(p);
                *cresceu = 0;
                break;
        }
    return p;
}

InfoCli equiDirCli(InfoCli p) {
    /*Após o cliente ser adicinado ao lado direito da árvore, se se verificar que há um desequilibrio à direita é feita uma rotação para a esquerda. */
    if(p->dir->eql == DIREITA){
        p = rodaEsqCli(p);
        p->eql = EQUILIBRADO;
        p->esq->eql = EQUILIBRADO;
    }
    else {
        /* Se ao ser adicionado um elemento à direita houver desequilíbrio à esquerda do nodo da direita temos de fazer dupla rotação. */
        p->dir = rodaDirCli(p->dir);
        p = rodaEsqCli(p);
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

InfoCli rodaDirCli(InfoCli p) {
    InfoCli aux = NULL;
    if((!p) || (!p->esq));
    else {
        aux = p->esq;
        p->esq = aux->dir;
        aux->dir = p;
        p = aux;
    }
    return p;
}

InfoCli equiEsqCli(InfoCli p) {
    if(p->esq->eql == ESQUERDA){
        p = rodaDirCli(p);
        p->eql = EQUILIBRADO;
        p->dir->eql = EQUILIBRADO;
    }
    else {
        p->esq = rodaEsqCli(p->esq);
        p = rodaDirCli(p);
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


InfoCli rodaEsqCli(InfoCli p) {
    InfoCli aux = NULL;
    if((!p) || (!p->dir));
    else {
        aux = p->dir;
        p->dir = aux->esq;
        aux->esq = p;
        p = aux;
    }
    return p;
}

InfoCli iniciarCATALOGOCLI() {
    return NULL;
}

void apagarCliente (cliente c){
    free(c->codigo);
    c->codigo=NULL;
    free(c);
    c=NULL;
}

void apagarCatalogoCli(InfoCli c) {
    if(c != NULL){
        apagarCatalogoCli(c->dir);
        c->dir = NULL;
        apagarCatalogoCli(c->esq);
        c->esq = NULL;
        free(c->cli->codigo);
        c->cli->codigo=NULL;
        free(c->cli);
        c->cli=NULL;
        free(c);
        c=NULL;
    }
}

CATALOGOCLI iniciaCatalogo() {
    return NULL;
}

int isEmptyCli (CodigoCli c) {
    return (c == NULL);
}