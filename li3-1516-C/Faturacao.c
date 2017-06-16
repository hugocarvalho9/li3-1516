#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Faturacao.h"

#define SIZEHASH 676

typedef enum balancefactor { ESQUERDA , EQUILIBRADO , DIREITA } BalanceFactor;

/** Estrutura para cada linha de venda **/
typedef struct venda {
    produto_t prod;
    double preco;
    int und;
    char tipo;
    int mes;
    int filial;
} *Venda;

/** Nodos da Árvore **/
typedef struct infoVenda {
	Venda venda;
	BalanceFactor eql;
	struct infoVenda *dir,*esq;
} *NodoVenda;

/** Estructura da Hash **/
typedef struct CatVenda {
    int size;
    int ocupado;
    NodoVenda vendas[SIZEHASH];
} *HashVenda;

/** Funções de inserção de infos na árvore **/
struct infoVenda *insereVenda (struct infoVenda *,struct venda*,int *);
struct infoVenda *insereEsqVenda (struct infoVenda *,struct venda*,int *);
struct infoVenda *insereDirVenda (struct infoVenda *,struct venda*,int *);
struct infoVenda *equiEsqVenda (struct infoVenda *);
struct infoVenda *equiDirVenda (struct infoVenda *);
struct infoVenda *rodaDirVenda (struct infoVenda *);
struct infoVenda *rodaEsqVenda (struct infoVenda *);


/** Funções da Hash **/
HashVenda iniciarFATURACAO() {
    HashVenda cat = (HashVenda) malloc(sizeof(struct CatVenda));
    cat->size = SIZEHASH;
    cat->ocupado = 0;
    int i = 0;
    while (i < cat->size)
        cat->vendas[i++] = NULL;
    return cat;
}

int indiceCatVenda(CodigoProd p) {
    int r=(p[0]-65)*26+(p[1]-65);
    return r;
}
/* Adiciona uma venda ao hash/array, introduzindo-a na respectiva árvore. A hash é
 constituída por apontadores para árvores expecíficas, por exemplo a árvore da
 posição 0 será constituida só por vendas nas quais o código do produto começa
 pelos caracteres AA. Na posição 1 serão as vendas com os caracteres AB e assim
 sucessivamente. O índice de uma árvore de dados produtos é dado pela função 
 indiceHashVenda(Prod). */

void addCatVenda(HashVenda h, char *lvenda) {
    Venda v = alocarVendas(lvenda);
    if (v != NULL) {
        int i = indiceCatVenda(getCodProduto(v->prod));
        int *cresceu = malloc(sizeof(int));
        *cresceu = 0;
        h->ocupado++;
        h->vendas[i] = insereVenda(h->vendas[i], v, cresceu);
        free(cresceu);
    }
}

/* F U N Ç Õ E S   D A   Á R V O R E */

/** Gets de árvores **/

produto_t getProdutoInfoFat (Venda f){return f->prod;}

int getUndInfoFat (Venda f){return f->und;}

int getFilialInfoFat (Venda f){return f->filial;}

int getMesInfoFat (Venda f){return f->mes;}

double getPrecoInfoFat (Venda f){return f->preco;}

char getTipoInfoFat (Venda f){return f->tipo;}

Venda alocarVendas(char *linha) {
    char *aux;
    Venda new = (Venda) malloc(sizeof(struct venda));
    aux=strtok(linha, " ");
    new->prod = cpyProd(aux);
    new->preco = atof(strtok(NULL, " "));          /* Aloca o valor do preço */
    new->und = atoi(strtok(NULL, " "));            /* Aloca o número de unidades do produto */
    new->tipo = *strtok(NULL, " ");                /* Aloca o tipo de venda */
    strtok(NULL, " ");                            /* código do cliente que neste caso não é alocado*/
    new->mes = atoi(strtok(NULL, " "));            /* Aloca o mês */
    new->filial = atoi(strtok(NULL, " \r\n"));     /* Aloca o filial */
    return new;
}

/* Função principal de inserção de uma venda numa árvore. */
NodoVenda insereVenda(NodoVenda vendas, Venda v, int *cresceu) {
    if(vendas == NULL){
        vendas = (NodoVenda) malloc(sizeof(struct infoVenda));
        vendas->esq = NULL;
        vendas->dir = NULL;
        vendas->eql = EQUILIBRADO;
        vendas->venda = v;
        *cresceu = 1;
    }
    else {
        int dif = cmpProd(v->prod,vendas->venda->prod);
        if(dif >= 0)
            vendas = insereDirVenda(vendas, v, cresceu);
        else
            vendas = insereEsqVenda(vendas, v, cresceu);
    }
    return vendas;
}

/* Função auxiliar de inserção que insere uma dada venda no info da esquerda e
 prossegue com o balanceamento da árvore se for necessário. */
NodoVenda insereEsqVenda(NodoVenda p, Venda v, int *cresceu) {
    p->esq = insereVenda(p->esq, v, cresceu);
    if(*cresceu)
        /* Verificação do equilíbrio da árvore binária */
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
                p = equiEsqVenda(p);
                *cresceu = 0;
                break;
        }
    return p;
}

/* Faz o mesmo que a função insereEsqVenda só que para o info da direita. */
NodoVenda insereDirVenda(NodoVenda p, Venda v, int *cresceu) {
    p->dir = insereVenda(p->dir, v, cresceu);
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
                p = equiDirVenda(p);
                *cresceu = 0;
                break;
        }
    return p;
}

/* Função auxiliar da função insereDirVenda que se encarrega de ajustar a árvore de modo a se manter equilibrada. */
NodoVenda equiDirVenda(NodoVenda p) {
    if(p->dir->eql == DIREITA){
        p = rodaEsqVenda(p);
        p->eql = EQUILIBRADO;
        p->esq->eql = EQUILIBRADO;
    }
    else {
        p->dir = rodaDirVenda(p->dir);
        p = rodaEsqVenda(p);
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

/* Rotação de uma árvore ou sub-árvore para a direita. */
/* Exemplo:

        (A)             (B)
        / \             / \
      (B) NULL  =>    (C) (A)
      / \             / \ / \
    (C) NULL       NULL(NULL)NULL    */

NodoVenda rodaDirVenda(NodoVenda p) {
    NodoVenda aux = NULL;
    if((!p) || (!p->esq));
    else {
        aux = p->esq;
        p->esq = aux->dir;
        aux->dir = p;
        p = aux;
    }
    return p;
}

/* Temos situações em que apenas uma rotação para esquerda ou uma rotação para a
 direita não é suficiente, nesses casos temos que fazer uma rotação dupla. */
NodoVenda equiEsqVenda(NodoVenda p) {
    if(p->esq->eql == ESQUERDA){
        p = rodaDirVenda(p);
        p->eql = EQUILIBRADO;
        p->dir->eql = EQUILIBRADO;
    }
    else {
        p->esq = rodaEsqVenda(p->esq);
        p = rodaDirVenda(p);
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


/* Rotação de uma árvore ou sub-árvore para a direita. */
/* Exemplo:

        (A)                 (B)
        / \                 / \
     NULL (B)       =>    (A) (C)
          / \             / \ / \
       NULL (C)        NULL(NULL)NULL    */

NodoVenda rodaEsqVenda(NodoVenda p) {
    NodoVenda aux = NULL;
    if((!p) || (!p->dir));
    else {
        aux = p->dir;
        p->dir = aux->esq;
        aux->esq = p;
        p = aux;
    }
    return p;
}

/* Função recursiva que liberta a memória alocada de uma dade árvore. */
void apagarInfoVendas(NodoVenda v) {
    if(v != NULL){
        apagarInfoVendas(v->dir);
        v->dir = NULL;
        apagarInfoVendas(v->esq);
        v->esq = NULL;
        apagaProduto(v->venda->prod);
        free(v->venda);
        free(v);
    }
}

void apagarFATURACAO(FATURACAO catalogo) {
    int i = 0;
    while (i < (catalogo->size)) {
        apagarInfoVendas(catalogo->vendas[i]);
        catalogo->vendas[i] = NULL;
        i++;
    }
}

/* QUERIE 3 */
void auxQuerie3F(NodoVenda v, int mes,CodigoProd p, float faturado[2][4], int numero[2][4]) {
    if (v!=NULL) {
        int dif = strcmp(getCodProduto(v->venda->prod), p);
        if (dif < 0)
            auxQuerie3F(v->dir, mes, p, faturado, numero);
        else
            if (dif > 0)
                auxQuerie3F(v->esq, mes, p, faturado, numero);
            else
                if (v->venda->mes == mes) {
                    if (v->venda->tipo != 'P'){
                        faturado[0][v->venda->filial+1] += (v->venda->und) * (v->venda->preco);
                        numero[0][v->venda->filial+1] += v->venda->und;
                    }
                    else {
                        faturado[1][v->venda->filial+1] += (v->venda->und) * (v->venda->preco);
                        numero[1][v->venda->filial+1] += v->venda->und;
                    }
                    auxQuerie3F(v->esq, mes, p, faturado, numero);
                    auxQuerie3F(v->dir, mes, p, faturado, numero);
                }
                else {
                    auxQuerie3F(v->dir, mes, p, faturado, numero);
                    auxQuerie3F(v->esq, mes, p, faturado, numero);
                }
    }
}

void querie3F(FATURACAO f, int mes,CodigoProd p, float fat[2][4], int num[2][4]) {
    int indice = indiceCatVenda(p);
    int i = 0;
    while (i < 4){
        num[0][i] = 0; num[1][i] = 0;
        fat[0][i] = 0; fat[1][i] = 0;
        i++;
    }
    auxQuerie3F(f->vendas[indice], mes, p, fat, num);
    num[0][0] = num[0][1] + num[0][2] + num[0][3];
    num[1][0] = num[1][1] + num[1][2] + num[1][3];
    fat[0][0] = fat[0][1] + fat[0][2] + fat[0][3];
    fat[1][0] = fat[1][1] + fat[1][2] + fat[1][3];
}

/** QUERI 4 **/

/* Função auxliliar de querie4 que cria o array de produtos não comprados*/
/* Função que percorre as árvores do catalogo de produtos e verifica se cada produto existe na estructura da faturação*/
int existeProdInfoFaturacao(CodigoProd p, NodoVenda v) {
    int r=0;
    if(v!=NULL){
        int dif = strcmp(p,getCodProduto(v->venda->prod));
        if(dif > 0)
            r+=existeProdInfoFaturacao(p, v->dir);
        else
            if(dif < 0)
                r+=existeProdInfoFaturacao(p, v->esq);
            else{
                r++;
                return r;
            }
    }
    return r;
}

int existeProdFaturacao(CodigoProd p, FATURACAO f) {
    int r;
    int ind = indiceCatVenda(p);
    r=existeProdInfoFaturacao(p, f->vendas[ind]);
    return r;
}

void percoreInfoProdG (struct InfoProd *p,FATURACAO f,DadosProd *prodNaoComp){
    if (p!=NULL) {

    	percoreInfoProdG(getAntInfoProd(p),f,prodNaoComp);
        if (!existeProdFaturacao(getCodProdInfoProd(p), f))
            adicionaProduto(*prodNaoComp,getProdutoInfoProd(p));

        percoreInfoProdG(getSegInfoProd(p),f,prodNaoComp);
    }
}

void queri4ProdG(FATURACAO f,CATALOGOPROD pd,DadosProd *prodNaoComp){
    int i=0;
    *prodNaoComp = iniciarDadosProd(10);
    while (i<getSizeCatProd(pd)) {
        percoreInfoProdG(getInfoCatProd(pd, i),f,prodNaoComp);
        i++;
    }
}

/*QUERIE 6*/
int percorrequerie6(NodoVenda v, double *fat, int primeiro, int segundo) {
    int r = 0;
    if (v != NULL) {
        if ((v->venda->mes >= primeiro) && (v->venda->mes <= segundo)) {
            r += v->venda->und;
            *fat += (v->venda->und) * (v->venda->preco);
            r += percorrequerie6(v->esq, fat, primeiro, segundo);
            r += percorrequerie6(v->dir, fat, primeiro, segundo);
        }
        else {
            r+=percorrequerie6(v->esq, fat, primeiro, segundo);
            r+=percorrequerie6(v->dir, fat, primeiro, segundo);
        }
    }
    return r;
}

int auxquerie6(FATURACAO f, int primeiro, int segundo, double *faturado){
    int numero = 0;
    int i = 0;
    while (i < 676) {
           numero += percorrequerie6(f->vendas[i], faturado, primeiro, segundo);
           i++;     

        }
    return numero;
}
