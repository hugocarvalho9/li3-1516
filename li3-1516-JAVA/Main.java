
import java.util.*;
import java.io.*;
import static java.lang.System.out;
import java.lang.String;

public class Main {
   
   // Vari�vel de inst�ncia
   private static Hipermercado hip;
   
   private Main (){}

   public static void main (String args[]){
        hip = new Hipermercado();
        Scanner lerNome;
        Scanner lerOpcao = new Scanner(System.in);
        int opcao = -1;
        lerNome = new Scanner(System.in);
        String nome = "";
        do {
               out.println("\t\t\t----------GEREVENDAS----------\n");
               out.println("\t\t\t------------------------------");
               out.println("\t\t\t|   1)Carregar estruturas    |");
               out.println("\t\t\t|   2)Queries Estat�sticas   |");
               out.println("\t\t\t|   3)Queries Interativas    |");
               out.println("\t\t\t|   4)Guardar Hipermercado   |");
               out.println("\t\t\t|   0)Encerrar Programa      |");
               out.println("\t\t\t------------------------------");
               
               out.print("Op��o: ");
               opcao = lerOpcao.nextInt();
               switch(opcao){
                   case (1): out.print("Como deseja carregar ? \t1)Ficheiros fonte;\n\t\t\t2)ObjectStream;\n");
                             out.print("Op��o: ");
                             opcao = lerOpcao.nextInt();
                             if(opcao == 1) {
                                 out.print("Escreva o nome do ficheiro que quer ler (sem extens�o): ");
                                 nome = lerNome.nextLine();
                                 out.print("\nA carregar...\n");
                                 Crono.start();
                                 out.print(hip.carregaDados(nome));
                                 Crono.stop();
                                 out.println("Tempo " + Crono.print());
                             }
                             if(opcao == 2) {
                                 out.print("Escreva o nome do ficheiro que quer ler: ");
                                 nome = lerNome.nextLine();
                                 hip = hip.lerObjeto(nome);
                             }
                                 break;
                   case (2): menuQueriesEstatisticas();
                             break;
                   case (3): menuQueriesInterativas();
                             break;
                   case (4): out.print("Insira um nome : ");
                             nome = lerNome.nextLine();
                             out.print("A guardar, aguarde ...\n");
                             try{ hip.guardarHipermercado(nome); }
                             catch(IOException e){ System.out.println("ERRO: N�o foi possivel guardar os dados!"); }
                   default:
                             break;
                       
               }
        } while(opcao != 0);
        lerNome.close();
        out.println("\t\t\t------------------------------");
   }
   
   private static void menuQueriesEstatisticas() {
           Scanner lerOpcao = new Scanner(System.in);
           int opcao = -1;
           out.println("\t\t-----------QUERIES EST�TISTICAS-----------\n");
           do {
               out.println("\t\t------------------------------------------");
               out.println("\t\t|  1)Total de compras por m�s            |");
               out.println("\t\t|  2)Fatura��o total por m�s             |");
               out.println("\t\t|  3)Clientes que compraram em cada m�s  |");
               out.println("\t\t|  0)Voltar                              |");
               out.println("\t\t------------------------------------------");
               out.print("Op��o: ");
               opcao = lerOpcao.nextInt();
               
               switch(opcao){
                   case (1): out.print(hip.numeroComprasPorMes());
                       break;
                   case (2): out.print(hip.fatTotalMes());
                       break;
                   case (3): out.print(hip.numeroClientesMes());
                       break;
                   default:
                       break;
               }
           } while(opcao != 0);
   }
   
   private static void menuQueriesInterativas() {
           Scanner lerOpcao = new Scanner(System.in);
           Scanner lerCodigo = new Scanner(System.in);
           int opcao = -1, opcao2 = -1, mes = 1, num = 0;
           String codigo = "";
           boolean sair = false;
           ApresentacaoPorPaginas pag = null;
           
           do {
               out.println("\n\t\t\t\t-----------QUERIES INTERATIVAS-----------");
               out.println("------------------------------------------------------------------------------------------------------------");
               out.println("| 1) Produtos nunca comprados e respectivo total                                                           |");
               out.println("| 2) Total de vendas realizadas e n� de clientes diferentes que as fizeram                                 |");
               out.println("| 3) N� de compras, produtos distintos comprados e total gasto para cada cliente                           |");
               out.println("| 4) N� de vezes que um produto foi comprado, n� de clientes diferentes que o compraram e total faturado   |");
               out.println("| 5) C�digos e n� de produtos que um cliente mais comprou                                                  |");
               out.println("| 6) N� de produtos mais vendidos em todo o ano e n� total de clientes diferentes que o compraram          |");
               out.println("| 7) Tr�s maiores compradores em dinheiro facturado para cada filial                                       |");
               out.println("| 8) C�digos e n� de clientes que compraram mais produtos diferentes                                       |");
               out.println("| 9) N� de clientes que mais compraram um produto e valor gasto                                            |");
               out.println("| 0) Voltar                                                                                                |");
               out.println("------------------------------------------------------------------------------------------------------------");
               out.print("\nOp��o: ");
               opcao = lerOpcao.nextInt();
               
               switch(opcao){
                   case (1): Crono.start();
                             List<String> querie1List = hip.querie1();
                             Crono.stop();
                             pag = new ApresentacaoPorPaginas(querie1List);
                             out.println("Tempo: " + Crono.print());
                             while(!sair){
                                 pag.lerPagina();
                                 pag.printLista();
                                 out.print("\t0)Sair \n \t1)Continuar.\n");
                                 out.print("Op��o: ");
                                 opcao2 = lerOpcao.nextInt();
                                 if(opcao2 == 0) sair = true;
                             }
                             sair = false;
                             querie1List = null;
                             pag = null;
                       break;
                   case (2): out.print("\nInsira um m�s v�lido: ");
                             mes = lerOpcao.nextInt();
                             Crono.start();
                             out.print(hip.querie2(mes).toString("N�mero Total de vendas", "N�mero de Clientes"));
                             Crono.stop();
                             out.println("Tempo " + Crono.print());
                       break;
                   case (3): 
                             out.print("\nInsira um c�digo de Cliente v�lido: ");
                             codigo = lerCodigo.nextLine();
                             Crono.start();
                             try 
                             { 
                                    Crono.start();
                                    List<TrioIntIntDouble> querie3List = hip.querie3(codigo);
                                    Crono.stop();
                                    mes = 1;
                                    for(TrioIntIntDouble t : querie3List){
                                        out.print("M�s "+ mes + ": " + t.toString("N�mero de compras","Produtos distintos comprados","Gasto no total"));
                                        mes++;
                                    }
                                    out.println("Tempo: " + Crono.print());
                                    querie3List = null;
                             }
                             catch(ClienteNaoExiste e) { out.println("O cliente que voc� escolheu n�o existe.\n"); }
                       break;
                   case (4): out.print("\nInsira um c�digo de Produto v�lido: ");
                             codigo = lerCodigo.nextLine();
                             try { 
                                    Crono.start();
                                    List<TrioIntIntDouble> querie4List = hip.querie4(codigo);
                                    Crono.stop();
                                    mes = 1;
                                    for(TrioIntIntDouble t : querie4List){
                                        out.print("M�s " + mes + ": " + t.toString("N�mero de vezes comprado","Clientes diferentes que compraram","Total faturado"));
                                        mes++;
                                    }
                                    out.println("Tempo: " + Crono.print());
                                    querie4List = null;
                                 }
                             catch(ProdutoNaoExiste e) {out.println("O produto que voc� escolheu n�o existe.\n"); }
                       break;
                   case (5): out.print("\nInsira um c�digo de Cliente v�lido: ");
                             codigo = lerCodigo.nextLine();
                             try {
                                     Crono.start();
                                     Set<ParCodigoInt> querie5set = hip.querie5(codigo);
                                     Crono.stop();
                                     pag = new ApresentacaoPorPaginas(querie5set,"C�digo de produto", "Quantidade comprada");
                                     out.println("Tempo: " + Crono.print());
                                     while(!sair){
                                         pag.lerPagina();
                                         pag.printLista();
                                         out.print("\t0)Sair \n \t1)Continuar.\n");
                                         out.print("Op��o: ");
                                         opcao2 = lerOpcao.nextInt();
                                         if(opcao2 == 0) sair = true;
                                        }
                                     sair = false;
                                     querie5set = null;
                                     pag = null;
                                 }
                                 catch(ClienteNaoExiste e) { out.println("O cliente que voc� escolheu n�o existe.\n"); }
                       break;
                   case (6): out.print("\nInsira o n� de produtos que deseja apresentar: ");
                             num = lerOpcao.nextInt();
                             Crono.start();
                             Set<TrioCodigoIntInt> querie6set = hip.querie6(num);
                             Crono.stop();
                             for(TrioCodigoIntInt t : querie6set){
                                        out.print(t.toString("C�digo de produto: ","Quantidade comprada: ","Clientes diferentes que compraram: "));
                             }
                             out.println("Tempo: " + Crono.print());
                             querie6set = null;
                             pag = null;
                       break;
                   case (7): num = 1;
                             Crono.start();
                             List<List<ParCodigoDouble>> querie7listList = hip.querie7();
                             Crono.stop();
                             for (List<ParCodigoDouble> filiais : querie7listList) {
                                 out.println("FILIAL " + num + ":");
                                 for(ParCodigoDouble s : filiais)
                                    out.print(s.toString(""," - "));
                                 num++;
                                 out.print("\n");
                             }
                             out.println("Tempo: " + Crono.print());
                             querie7listList=null;
                       break;
                   case (8): out.print("\nInsira o n� de clientes que deseja apresentar: ");
                             num = lerOpcao.nextInt();
                             Crono.start();
                             Set<ParCodigoInt> querie8set = hip.querie8(num);
                             Crono.stop();
                             pag = new ApresentacaoPorPaginas(querie8set,"Cliente" , "Produtos diferentes comprados");
                             out.println("Tempo: " + Crono.print());
                             while(!sair){
                                 pag.lerPagina();
                                 pag.printLista();
                                 out.print("\n\t0)Sair \n \t1)Continuar.\n");
                                 out.print("Op��o: ");
                                 opcao2 = lerOpcao.nextInt();
                                 if(opcao2 == 0) sair = true;
                             }
                             sair = false;
                             querie8set = null;
                             pag = null;
                             break;
                   case (9): out.print("\nInsira um c�digo de Produto v�lido: ");
                             codigo = lerCodigo.nextLine();
                             out.print("Insira o limite de clientes que deseja ver: ");
                             num = lerOpcao.nextInt();
                             try {
                                    Crono.start();
                                    Set<TrioCodigoIntDouble> querie9set = hip.querie9(codigo,num);
                                    Crono.stop();
                                    pag = new ApresentacaoPorPaginas(querie9set,"Cliente", "Quantidade comprada","Total gasto");
                                    out.println("Tempo: " + Crono.print());
                                    while(!sair){
                                        pag.lerPagina();
                                        pag.printLista();
                                        out.print("\n\t0)Sair \n \t1)Continuar.\n");
                                        out.print("Op��o: ");
                                        opcao2 = lerOpcao.nextInt();
                                        if(opcao2 == 0) sair = true;
                                    }
                                    sair = false;
                                    querie9set = null;
                                    pag = null;
                                 }
                             catch(ProdutoNaoExiste e) {out.println("O produto que voc� escolheu n�o existe.\n"); }
                       break;
                   default:
                       break;
               }
           } while(opcao != 0);
   }
}
