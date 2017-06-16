import java.util.*;
import java.util.Collections;
import java.io.*;
import java.lang.Object;
public class ApresentacaoPorPaginas
{
    // Variáveis de Instância
    private List<String> lista;
    private int numLinhas;
    private int pagina;

    // Construtores
    public ApresentacaoPorPaginas(List<String> list) {
        lista = new ArrayList<>();
        for(String s : list)
            lista.add(s);
        numLinhas = 20;
        pagina = 0;
    }
    public ApresentacaoPorPaginas(List<TrioIntIntDouble> t,String arg1,String arg2,String arg3) {
        lista = new ArrayList<>();
        for(TrioIntIntDouble trio : t)
            lista.add(trio.toString(arg1,arg2,arg3));
        numLinhas = 20;
        pagina = 0;
    }
    public ApresentacaoPorPaginas(Set<TrioCodigoIntDouble> list, String arg1, String arg2, String arg3) {
        lista = new ArrayList<>();
        for(TrioCodigoIntDouble trio : list)
            lista.add(trio.toString(arg1,arg2,arg3));
        numLinhas = 20;
        pagina = 0;
    }
    public ApresentacaoPorPaginas(Set<ParCodigoInt> list, String arg1, String arg2) {
        lista = new ArrayList<>();
        for(ParCodigoInt p : list)
            lista.add(p.toString(arg1, arg2));
        numLinhas = 20;
        pagina = 0;
    }
    
    // Métodos
    
    /** Mostrar menu. */
    public void printLista() {
        for (int i = 0; i < numLinhas && (i + pagina*numLinhas) < lista.size(); i++) {
            System.out.println(this.lista.get(i + pagina*numLinhas));
        }
    }
    
    /** Ler uma opção válida. */
    public int lerPagina() {
        int opcao;
        int numPaginas = (lista.size()/numLinhas) + 1, limite;
        if(numPaginas-1 <= 0) limite = 1;
        else limite = numPaginas;
        Scanner is = new Scanner(System.in);
        System.out.println("Lista com " + numPaginas + " (de 1 a " + limite + ")" + " páginas:");
        System.out.println("Lista com um total de " + lista.size() + " elementos.");
        System.out.print("Pagina: ");
        try{
            pagina = is.nextInt() - 1;
        }
        catch (InputMismatchException e) {
            pagina = 0;
        }
        if ( (pagina < 0) || (pagina > this.lista.size()) ) {
            System.out.println("Opção Inválida!");
            pagina = 0;
        }
        return pagina;
    }
    
    /** Recebe a última opção lida. */
    public int getPagina() {
        return this.pagina;
    }
}
