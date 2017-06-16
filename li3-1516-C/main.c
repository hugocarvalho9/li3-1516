/*
Bruno Dantas
Daniel Rodrigues
Hugo Carvalho
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "Produtos.h"
#include "Clientes.h"
#include "Faturacao.h"
#include "Filial.h"

/** MENU **/

#define CLEAR_CONSOLE printf("\033[2J\033[1;1H");
#define ESP "   "

/*Cores*/
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"
#define STYLE_BOLD    "\033[1m"
#define STYLE_NO_BOLD "\033[22m"

/*Ficheiros*/
#ifdef LINIX
#define FCLIENTES "Clientes.txt"
#define FPRODUTOS "Produtos.txt"
#define FVENDAS "Vendas_1M.txt"
#elif defined(__APPLE__) || defined(MACOSX)
#define FCLIENTES "/Users/Deni/Documents/LI3/code/Clientes.txt"
#define FPRODUTOS "/Users/Deni/Documents/LI3/code/Produtos.txt"
#define FVENDAS "/Users/Deni/Documents/LI3/code/Vendas_1M.txt"
#else 
#define FCLIENTES "Clientes.txt"
#define FPRODUTOS "Produtos.txt"
#define FVENDAS "Vendas_1M.txt"
#endif

void printMenu () {
    printf("\n"STYLE_BOLD""COLOR_GREEN" ============================================== "COLOR_GREEN"GEREVENDAS"STYLE_BOLD" ================================================\n");
    printf("||                                                                                                        ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"1)"COLOR_RESET""STYLE_BOLD" Ler Ficheiros (Produtos, Clientes, Vendas);"COLOR_GREEN"                                                        ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"2)"COLOR_RESET""STYLE_BOLD" Determinar a lista e o total de produtos cujo código se inicia por uma dada letra;"COLOR_GREEN"                 ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"3)"COLOR_RESET""STYLE_BOLD" Dado um mês e um cód. de produtos, determinar o nº de vendas e faturação desse produto nesse mês;"COLOR_GREEN"  ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"4)"COLOR_RESET""STYLE_BOLD" Determinar a lista ordenada dos códigos de produtos que ninguém comprou;"COLOR_GREEN"                           ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"5)"COLOR_RESET""STYLE_BOLD" Dado um cód. de cliente, cria uma tabela com o nº total de produtos comprados, mês a mês;"COLOR_GREEN"          ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"6)"COLOR_RESET""STYLE_BOLD" Dado um intervalo fechado de meses, determinar o total de vendas nesses intervalo e a faturação;"COLOR_GREEN"   ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"7)"COLOR_RESET""STYLE_BOLD" Determinar a lista ordenada de códigos de clientes que realizaram compras em todas as filiais;"COLOR_GREEN"     ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"8)"COLOR_RESET""STYLE_BOLD" Dado um código de produto e uma filial, determinar os códigos e o nº de clientes que o compraram;"COLOR_GREEN"  ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"9)"COLOR_RESET""STYLE_BOLD" Dado um cód. de cliente e um mês, determinar a lista de códigos de produtos que mais comprou;"COLOR_GREEN"      ||\n");
    printf(""STYLE_BOLD"|| "COLOR_GREEN"10)"COLOR_RESET""STYLE_BOLD" Criar uma lista dos N produtos mais vendidos em todo o ano;"COLOR_GREEN"                                        ||\n");
    printf(""STYLE_BOLD"|| "COLOR_GREEN"11)"COLOR_RESET""STYLE_BOLD" Dado um cód. de cliente, determinar quais os 3 produtos em que mais gastou dinheiro durante o ano;"COLOR_GREEN" ||\n");
    printf(""STYLE_BOLD"|| "COLOR_GREEN"12)"COLOR_RESET""STYLE_BOLD" Determinar o nº de clientes que não realizaram compras e o nº de produtos que ninguém comprou;"COLOR_GREEN"     ||\n");
    printf("||                                                                                                        ||\n");
    printf(""STYLE_BOLD"||  "COLOR_GREEN"0)"COLOR_RESET""STYLE_BOLD" Sair do Programa"COLOR_GREEN"                                                                                   ||\n");
    printf("||                                                                                                        ||\n");
    printf(" ==========================================================================================================\n");
}

/* QUERIE 1 -> main*/
/*Produtos*/
CATALOGOPROD ler_produtos(char *f, CATALOGOPROD pd);
int prodValido(CodigoCli);
/*Clientes*/
CATALOGOCLI ler_clientes(char *f, CATALOGOCLI cl);
int cliValido(CodigoCli c);
/*Faturação e filial*/
double ler_vendas(char *f,FATURACAO fat,MODULOFILIAL *filial, CATALOGOPROD p, CATALOGOCLI c);
int validaVenda(char *linha, CATALOGOPROD pd, CATALOGOCLI cl, double *faturacao);
/*Validações*/
int valPreco(float price);
int valUnd(int unidade);
int valTipo(char tipo);
int valMes(int mes);
int valFilial(int filial);

/* QUERIE 2 -> Produtos */
void imprimeQuerie2(int npag,DadosProd a);
void querie2(CATALOGOPROD prod);


/** Queri3 -> Faturação **/
void querie3(FATURACAO f,CATALOGOPROD pr);


/** Queri4 -> Faturação/Filial **/
void queri4 (FATURACAO f,CATALOGOPROD pd);

/** Queri5 -> Filial **/
void querie5(MODULOFILIAL *filial, CATALOGOCLI cl);

    
/** Queri6 -> Faturação **/
void querie6(FATURACAO f);

/** Queri7 -> Filial **/
void querie7(CATALOGOCLI cli,MODULOFILIAL *f);
void imprimeQuerie7(int npag, CLIENTES a);

/** Queri8 -> Filial **/
void querie8 (MODULOFILIAL *filial,CATALOGOPROD pr);

/** Querie11 **/
void querie11(MODULOFILIAL *f);

/** Queri12 -> Filial/Faturação **/
void querie12(CATALOGOCLI c, CATALOGOPROD p,MODULOFILIAL *f, FATURACAO fat);

/** Funções extra **/
void apagarEstruturas(CATALOGOCLI cl, CATALOGOPROD pd, FATURACAO fat,MODULOFILIAL *filial);

/** *   *   *   *   *   * __QUERI1__ *   *   *   *   *   *  **/

/** Funções relacionadas com os produtos **/
CATALOGOPROD ler_produtos(char *f,CATALOGOPROD pd) {
    int validos = 0, lidos = 0;
    char *linha= malloc(sizeof(char)*30);
    FILE *fp = fopen(f, "r");
    CodigoProd produto = iniciaProduto();
    pd = iniciarPROD();
    
    if (fp == NULL)
        perror(ESP"Impossível ler ficheiro \"Produtos.txt\"");
    else {
        while (fgets(linha,sizeof(char) * 21, fp)) {           /* Recebe a linha do ficheiro */
            produto = strtok (linha, " \r\n");                 /* Extrai o produto dessa linha */
            if (!isEmptyProd(produto) && prodValido(produto)) {        /* Se for válido aloca o produto */
                validos++;
                addCatProd(pd, produto);
            }
            lidos++;
        }
    }
    
    fclose(fp);
    if(lidos){
        printf(ESP"Foi lido o ficheiro \"Produtos.txt\" \n");
        printf(ESP"Produtos Lidos: %d\n"ESP"Produtos Validos: %d\n", lidos, validos);
    }
    free(linha);
    return pd;
}

int prodValido(char *p) {
    int numero = atoi(p + 2);
    if (strlen(p) != 6)
        return 0;
    if (p[0] < 'A' || p[0] > 'Z')
        return 0;
    if (p[1] < 'A' || p[1] > 'Z')
        return 0;
    if (numero < 1000 || numero > 1999)
        return 0;
    return 1;
}

/** Funções relacionadas com os Clientes **/
CATALOGOCLI ler_clientes(char *f, CATALOGOCLI cl) {
    int lidos = 0,validos = 0;
    int *cresceu = malloc(sizeof(int));
    FILE *file = fopen (f, "r");
    CodigoCli cliente = malloc(sizeof(CodigoCli));
    char *linha = malloc(sizeof(char) * 100);
    cl = iniciaCatalogo();
    
    *cresceu = 0;
    if (file == NULL)
        perror(ESP"Impossível ler ficheiro \"Clientes.txt\"");
    else {
        while (fgets(linha,sizeof(char) * 100, file)) {            /* Recebe a linha do ficheiro */
            linha = strtok(linha, " \r\n");
            strcpy(cliente, linha);                                /* Copia o cliente dessa linha */
            if (!isEmptyCli(cliente) && cliValido(cliente)) {       /* Se for válido aloca o cliente */
                validos++;
                cl = addCliInfoCli(cl, cliente, cresceu);
            }
            lidos++;
        }
    }
    fclose(file);
    if(lidos){
        printf(ESP"Foi lido o ficheiro \"Clientes.txt\" \n");
        printf(ESP"Clientes lidos: %d\n"ESP"Clientes validos: %d\n", lidos, validos);
    }
    free(linha);
    free(cliente);
    free(cresceu);
    return cl;
}

int cliValido(CodigoCli t) {
    int numero = atoi(t + 1);
    if (strlen(t) != 5)                   /* verifica o comprimento */
        return 0;
    if (t[0] < 'A' || t[0] > 'Z')         /* verifica a primeira letra */
        return 0;
    if (numero < 1000 || numero > 5000)   /* verifica o número */
        return 0;
    return 1;
}


/** Funções relacionadas com as Vendas **/
double ler_vendas (char *f, FATURACAO fat,MODULOFILIAL *filial, CATALOGOPROD p, CATALOGOCLI c) {
    int lidas = 0, validas = 0;
    double faturacao;
    FILE *file;
    char *str = NULL;
    char linha[100], linhaAux[100];
    faturacao = 0;
    
    if ((file = fopen(f, "r")) != NULL){
        while((str = fgets(linha, 34, file)) != NULL) {/* Lê a linha do ficheiro */
            strcpy(linhaAux, linha);
            if (str != NULL && validaVenda(linhaAux, p, c, &faturacao)){        /* Se a linha foi lida e é válida e aloca a venda.*/
                strcpy(linhaAux, linha);
                addCatVenda(fat, linhaAux);
                addCatFilial(filial, linha);
                validas++;
            }
            lidas++;
        }
        fclose(file);
        printf(ESP"Foi lido o ficheiro \"%s\"\n", FVENDAS);
        printf(ESP"Vendas lidas: %d\n", lidas);
        printf(ESP"Vendas validas: %d\n", validas);
    }
    else
        perror("Impossível ler ficheiro \"Vendas_1M.txt\"");
    return (faturacao);
}


/* Programas auxiliares para a função validaVendas */
int valPreco(float price) {
    if (price < 0.0 || price > 999.99)
        return 0;
    return 1;
}
int valUnd(int unidade){
    if (unidade < 1 || unidade > 200)
        return 0;
    return 1;
}
int valTipo(char tipo) {
    if (!isalpha(tipo))
        return 0;
    return 1;
}
int valMes(int mes) {
    if (mes < 1 ||  mes > 12)
        return 0;
    return 1;
}
int valFilial(int filial) {
    if (filial < 1 || filial > 3)
        return 0;
    return 1;
}

/* Verifica se o código da venda é válido */
int validaVenda(char *linha,CATALOGOPROD pd, CATALOGOCLI cl, double *faturacao) {
    CodigoProd prod;
    CodigoCli cli;
    char tipo='\0';
    float preco=0;
    int und=0, filial=0, mes=0,indice=0;
    
    prod = strtok(linha," ");
    preco = atof(strtok(NULL," "));
    und = atoi(strtok(NULL," "));
    tipo = *strtok(NULL," ");
    cli = strtok(NULL," ");
    mes = atoi(strtok(NULL," "));
    filial = atoi(strtok(NULL," \r\n"));
    
    indice = indiceCatProd(prod);
    if (prodValido(prod) && valPreco(preco) && valUnd(und) && valTipo(tipo) &&
        cliValido(cli) && valMes(mes) && valFilial(filial)){
        if (existeProd(prod, getInfoCatProd(pd, indice)) && existeCli(cli, cl)){  /*Verificar se o código do produto e do cliente existem */
            (*faturacao) += preco*und;
            return 1;
        }
    }
    return 0;
}

void apagarEstruturas(CATALOGOCLI cl, CATALOGOPROD pd, FATURACAO fat,MODULOFILIAL *filial) {
    apagarCatalogoCli(cl);
    apagarCATALOGOPROD(pd);
    apagarFATURACAO(fat);
    apagarModuloFilial(filial[0]);
    apagarModuloFilial(filial[1]);
    apagarModuloFilial(filial[2]);
    printf(ESP"Foram apagadas as estruturas anteriores\n\n");
}



/* QUERIE2 */
void imprimeQuerie2(int npag, DadosProd a) {
    int pag=0,i=0,quantidadeDeProd = getOcupadosDadosProd(a);
    irParaPagDadosProd(a,npag);
    pag=getPaginaDadosProd(a);
    i=pag+getNpagDadosProd(a);
    
    while ( pag < i && pag < (quantidadeDeProd)) {
        printf(ESP"%s\n", getProdDadosProd(a, pag));
        pag++;
    }
}

void querie2(CATALOGOPROD prod) {
    int i = 1, pagina = 1,quantDeProd=0, npag=0;
    char *linha = malloc(sizeof(char)*20);
    DadosProd lista = iniciaDados();
    
    printf(ESP"Insira uma letra maiúscula : ");
    scanf("%s", linha);
    if (isupper(linha[0])){
        lista = criarDadosProd(&linha[0], prod);
        quantDeProd = getOcupadosDadosProd(lista);
        npag = (quantDeProd-1)/20+1;
        printf(ESP"Foi encontrado um total de %d produtos iniciados pela letra %c.\n", quantDeProd, linha[0]);
        
        while(i){
            printf("\n"ESP"Indique a página que deseja aceder (de 1 até %d): ", npag);
            scanf("%d", &pagina);
            pagina--;

            if (pagina >= 0 && pagina <= npag)
                imprimeQuerie2(pagina,lista);
            else
                printf(ESP"Valor inválido\n\n");
            
            printf("\n"ESP"Deseja continuar? (S/N)\n\n");
            printf(ESP);
            scanf("%s", linha);
            if (linha[0] == 'n' || linha[0] == 'N')
                i = 0;
        }
        apagarDadosProd(lista);
    }
    else printf("\n"ESP"Caractere inválido, insira uma letra maiúscula: ");
    free(linha);
}


/* QUERIE 3*/
void querie3(FATURACAO f,CATALOGOPROD pr) {
    int mes=0, num[2][4],modo=0;
    char tipo;
    CodigoProd p = malloc(sizeof(CodigoProd));
    float fat[2][4];
    
    printf(ESP"Insira o mês: ");
    scanf("%d", &mes);
        while(mes<1 || mes>12){
            printf(ESP"Mês inválido, insira novamente o mês :");
            scanf("%d", &mes);
        }
    printf(ESP"Insira o produto: ");
    scanf("%s", p);
    while (!prodValido(p) || !existeProd(p,getInfoCatProd(pr,indiceCatProd(p)))){
        printf("\n"ESP"Código inválido! Insira um Código Válido: ");
        scanf(" %s", p);
        while (prodValido(p) && !existeProd(p,getInfoCatProd(pr,indiceCatProd(p)))) {
            printf("\n"ESP"Código inválido! Insira um Código Válido: ");
            scanf(" %s", p);
        }
    }
    printf(ESP"Insira o tipo (G/F): ");
    scanf("\n%c", &tipo);
    modo = (tipo == 'G');
    
    querie3F(f, mes, p, fat, num);
    
    if (modo){
        printf("\n"ESP"Quantidade de tipo N -> %d\n"ESP"Faturado -> %.2f\n\n", num[0][0], fat[0][0]);
        printf(ESP"Quantidade de tipo P -> %d\n"ESP"Faturado -> %.2f\n\n", num[1][0], fat[1][0]);
    }
    else{
        printf("\n"ESP"Quantidade de tipo N  -> %d (FILIAL 1), %d (FILIAL 2), %d (FILIAL 3)\n", num[0][1], num[0][2], num[0][3]);
        printf(ESP"Faturado de tipo N    -> %.2f (FILIAL 1), %.2f (FILIAL 2), %.2f (FILIAL 3)\n\n", fat[0][1], fat[0][2], fat[0][3]);
        printf(ESP"Quantidade de tipo P  -> %d (FILIAL 1), %d (FILIAL 2), %d (FILIAL 3)\n", num[1][1], num[1][2], num[1][3]);
        printf(ESP"Faturado de tipo P    -> %.2f (FILIAL 1), %.2f (FILIAL 2), %.2f (FILIAL 3)\n\n", fat[1][1], fat[1][2], fat[1][3]);
    }
    free(p);
}


void querie4 (FATURACAO f,MODULOFILIAL *fil,CATALOGOPROD pd){
    char t,*linha=malloc(sizeof(char)*30);
    int pagina=0,i=1,quantDeProd=0,npag=0;
    CATALOGOPROD prodAux=pd;
    FATURACAO fatAux=f;
    MODULOFILIAL *filialAux=fil;
    DadosProd *prodNaoComp0 = malloc(sizeof(void *));
    printf(ESP"Indique o tipo de representação (G/F):");
    scanf("\n%c",&t);
    if (t != 'G') printf("\n"ESP"Não disponível!\n");
    else {
        queri4ProdG(fatAux,prodAux,prodNaoComp0);
        quantDeProd = getOcupadosDadosProd(*prodNaoComp0);
        npag = (quantDeProd-1)/20+1;
        printf(ESP"Foi encontrado um total de %d produtos nunca vendidos.\n",quantDeProd);
        while(i){
            printf(ESP"Indique a página que deseja aceder (de 1 até %d): ",npag);
            scanf(" %d",&pagina);

            if (pagina>=1 && pagina<=(npag))
                imprimeQuerie2(pagina-1,*prodNaoComp0);
            else
                printf(ESP"Valor inválido\n\n");
            
            printf("\n"ESP"Deseja continuar? (S/N)\n\n");
            printf(ESP);
            scanf(" %s",linha);
            if (linha[0]=='n' || linha[0] == 'N'){
                i=0;
                apagarDadosProd(*prodNaoComp0);
                free(prodNaoComp0);
               }
            }
        }
    free(linha);
}


/** *   *   *   *   *   * __QUERI5__ *   *   *   *   *   *  **/
void querie5(MODULOFILIAL *filial, CATALOGOCLI cl) {
    CodigoCli cliente = (CodigoCli) malloc(sizeof(CodigoCli));
    int prod_filial[3][12],i=0;
    
    while (i<12) {
        prod_filial[0][i]=0;
        prod_filial[1][i]=0;
        prod_filial[2][i]=0;
        i++;
    }
    i=0;
    printf(ESP"Insira o Código do Cliente : ");
    scanf(" %s", cliente);
    
    while (!existeCli(cliente, cl)) {
        printf("\n"ESP"Código inválido! Insira um Código Válido: ");
        scanf(" %s", cliente);
    }
    querie5aux(cliente, prod_filial, filial);
    
    printf("\n"ESP"CLIENTE: %s\n\n", cliente);
    printf(ESP"MÊS\t\tFILIAL 1\tFILIAL 2\tFILIAL 3\t\n");
    
    for (i = 0; i < 12; i++)
        printf(ESP"%3d\t%16d\t%8d\t%8d\n", i + 1, prod_filial[0][i], prod_filial[1][i], prod_filial[2][i]);
    
}

/** *   *   *   *   *   * __QUERI6__ *   *   *   *   *   *  **/
void querie6(FATURACAO f) {
    int primeiro=0, segundo=0;
    int r=0;
    double *faturado = malloc(sizeof(double));
    *faturado=0;

    printf(ESP"Insira o primeiro mês: ");
    scanf(" %d", &primeiro);
        while(!valMes(primeiro)) {
            printf(ESP"Mês inválido, insira novamente o mês: ");
            scanf("%d", &primeiro);
        }

    printf(ESP"Insira o segundo mês: ");
    scanf(" %d", &segundo);
        while(!valMes(segundo)) {
            printf(ESP"Mês inválido, insira novamente o mês: ");
            scanf("%d", &segundo);
        }


    r = auxquerie6(f, primeiro, segundo, faturado);
    printf(ESP"Total de vendas registadas no intervalo: %d\n", r);
    printf(ESP"Total faturado: %.2f\n", *faturado);
    free(faturado);

}


/** *   *   *   *   *   * __QUERI7__ *   *   *   *   *   *  **/
void imprimeQuerie7(int npag, CLIENTES a) {
    int i = npag, numClientes = getOcupadosDadosCli(a);
    npag += 20;
    
    while (i < npag && i < (numClientes)) {
        printf(ESP"%s\n", getCodCliDadosCli(a, i));
        i++;
    }
}

void querie7(CATALOGOCLI cli,MODULOFILIAL *f) {
    int pagina = 1, i = 1, numClientes;
    
    char *linha = malloc(sizeof(char) * 20);
    CLIENTES lista = iniciarDadosCli();
    clienteTodosFiliais(cli, f, lista);
    numClientes = getOcupadosDadosCli(lista);
    printf(ESP"Foram encontrados um total de %d clientes com compras em todos os filiais.", numClientes);
    
    while(i){
        printf("\n"ESP"Indique a página que deseja aceder (de 1 até %d): ", (numClientes -1) / 20 + 1);
        scanf(" %d",&pagina);
        pagina = (pagina - 1) * 20;
        
        if (pagina >= 0 && pagina <= numClientes - 1)
            imprimeQuerie7(pagina, lista);
        else
            printf(ESP"Valor inválido\n\n");
        
        printf("\n"ESP"Deseja continuar? (S/N)\n\n");
        printf(ESP);
        scanf(" %s", linha);
        if (linha[0] == 'n' || linha[0] == 'N')
            i = 0;
    }
    apagarDadosCli(lista);
}

/** *   *   *   *   *   * __QUERI8__ *   *   *   *   *   *  **/
void querie8 (MODULOFILIAL *filial,CATALOGOPROD pr) {
    CodigoProd prod = (CodigoProd)malloc(sizeof(CodigoProd));
    int fil = 0;
    int i = 0;
    CLIENTES prom = iniciarDadosCli();
    CLIENTES norm = iniciarDadosCli();
    
    printf(ESP"Insira o Código do Produto : ");
    scanf(" %s", prod);
    
    while (!prodValido(prod) || !existeProd(prod,getInfoCatProd(pr,indiceCatProd(prod)))){
        printf("\n"ESP"Código inválido! Insira um Código Válido: ");
        scanf(" %s", prod);
        while (prodValido(prod) && !existeProd(prod,getInfoCatProd(pr,indiceCatProd(prod)))) {
            printf("\n"ESP"Código inválido! Insira um Código Válido: ");
            scanf(" %s", prod);
        }
    }
    
    printf(ESP"Insira a filial: ");
    scanf(" %d",&fil);
    
    querie8aux(prod,filial,fil, prom, norm);
    
    printf(ESP"Qtd clientes - N : %d\n", getOcupadosDadosCli(norm));
    while (i<getOcupadosDadosCli(norm)) {
        printf(ESP"%s\n", getCodCliDadosCli(norm,i));
        i++;
    }
    i=0;
    printf(ESP"Qtd clientes - P : %d\n", getOcupadosDadosCli(prom));
    while (i<getOcupadosDadosCli(prom)) {
        printf(ESP"%s\n", getCodCliDadosCli(prom,i));
        i++;
    }
    
    apagarDadosCli(prom);
    apagarDadosCli(norm);
}


/** *   *   *   *   *   * __QUERI12__ *   *   *   *   *   *  **/
void querie12(CATALOGOCLI c, CATALOGOPROD p,MODULOFILIAL *f, FATURACAO fat){
    int tamC, tamP;
    CLIENTES listaC = iniciarDadosCli();
    DadosProd *listaP = malloc(sizeof(void *));
    cliSemCompras(c,f, listaC);
    queri4ProdG(fat, p,listaP);
    tamP = getOcupadosDadosProd(*listaP);
    tamC = getOcupadosDadosCli(listaC);
    printf(ESP"%d clientes sem compras.\n"ESP"%d produtos não comprados.\n", tamC, tamP);
    apagarDadosCli(listaC);
    apagarDadosProd(*listaP);
    free(listaP);
}


/** MAIN **/

int main() {
    int op;
    double f;
    char fileVendas[100] = FVENDAS;
    char fileProdutos[100] = FPRODUTOS;
    char fileClientes[100] = FCLIENTES;
    int ler = 0;
    
    CATALOGOPROD pd = iniciarCATALOGOPROD();
    CATALOGOCLI cl = iniciarCATALOGOCLI();
    FATURACAO fat = iniciarFATURACAO();
    MODULOFILIAL filial[3];
    filial[0] = iniciarModuloFilial();
    filial[1] = iniciarModuloFilial();
    filial[2] = iniciarModuloFilial();

    CLEAR_CONSOLE;
    printMenu();
    
    do {
        
        printf("\n"COLOR_GREEN"   OPÇÃO:"COLOR_RESET""STYLE_BOLD" ");
        scanf(" %d", &op);
        
        CLEAR_CONSOLE;
        printMenu();
        printf("\n"COLOR_GREEN"   OPÇÃO: "COLOR_RESET""STYLE_BOLD"%d"" \n\n",op); 
        
        switch (op) {
            case 1  :
                if (ler == 0) {
                    cl = ler_clientes(fileClientes, cl);
                    pd = ler_produtos(fileProdutos, pd);
                    f = ler_vendas(fileVendas, fat, filial, pd, cl);
                    ler = 1; }
                else {
                    apagarEstruturas(cl, pd, fat,filial);
                    cl = ler_clientes(fileClientes, cl);
                    pd = ler_produtos(fileProdutos, pd);
                    f = ler_vendas(fileVendas, fat, filial, pd, cl);
                }
                putchar('\n');
                break;
                
            case 2  :
                if (ler == 1)
                    querie2(pd);
                else
                    printf(ESP"Os ficheiros não foram lidos");
                break;

            case 3  :
                if (ler == 1)
                    querie3(fat,pd);
                else
                    printf(ESP"Os ficheiros não foram lidos");
                break;
            case 4  :
                if (ler == 1)
                    querie4(fat,filial,pd);
                else
                    printf(ESP"Os ficheiros não foram lidos");
                break;
            case 5  :
                if (ler == 1)
                    querie5(filial, cl);
                else 
                    printf(ESP"Os ficheiros não foram lidos\n");
                break;
            case 6  :
                if (ler==1)
                    querie6(fat);
                else
                    printf(ESP"Os ficheiros não foram lidos");
                break;
            case 7  :
                if (ler==1)
                    querie7(cl, filial);
                else
                    printf(ESP"Os ficheiros não foram lidos");
                break;
            case 8  :
                if (ler==1)
                    querie8(filial, pd);
                else
                    printf(ESP"Os ficheiros não foram lidos");
                break;
            case 9  :
                printf("\n"ESP"Não disponível!\n\n");
                break;
            case 10 :
                printf("\n"ESP"Não disponível!\n\n");
                break;
            case 11 :
                printf("\n"ESP"Não disponível!\n\n");
                break;
            case 12 : 
                if (ler==1)
                    querie12(cl, pd, filial, fat);
                else
                    printf(ESP"Os ficheiros não foram lidos");
                break;
                break;
            case 0  :
                printf("\n"ESP"Encerrou o programa!\n");
                if(ler == 1)
                    apagarEstruturas(cl, pd, fat, filial);

                free(filial[0]);
                free(filial[1]);
                free(filial[2]);
                free(fat);
                free(pd);
                break;
            default : printf("\n"ESP"OPÇÃO INVÁLIDA!\n\n");
        }
    } while (op);
    
    return 0;
}


