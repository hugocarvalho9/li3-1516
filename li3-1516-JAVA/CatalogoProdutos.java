import java.util.*;
import java.io.*;

public class CatalogoProdutos implements Serializable {
   // Variável de instância
   private Set<String> catalogoProdutos;
   
   // Construtores
   public CatalogoProdutos() {
        catalogoProdutos = new TreeSet<>();
   }
   public CatalogoProdutos(Set<String> set) {
        catalogoProdutos = new TreeSet<>();
        set.stream().forEach((s) -> {
                     catalogoProdutos.add(s);
                    });
   }
   public CatalogoProdutos(CatalogoProdutos catProd) {
        catalogoProdutos = new TreeSet<>();
        catProd.getProdutos().stream().forEach((s) -> {
                              catalogoProdutos.add(s);
                            });
   }
   
   // Métodos
   
   /** Set com todos os produtos lidos. */
   public Set<String> getProdutos() {
        Set<String> x = new TreeSet<>();
        catalogoProdutos.stream().forEach((p) -> {
                                x.add(p);
                            });
        
        return x;
   }
   
   /** Tamanho do catálogo. */
   public int size() {
        return (catalogoProdutos.size());
    }
   
   /** Verificar se um cliente existe. */
   public boolean existeProduto(String codigo){
        return (catalogoProdutos.contains(codigo));
   }
   
   /** Verificar se o código do produto é válido. */
   public boolean codigoValido(String codigo) {
        return (codigo.length() == 6 
               && Character.isUpperCase(codigo.charAt(0)) && Character.isUpperCase(codigo.charAt(1))
               && Character.isDigit(codigo.charAt(2)) && Character.isDigit(codigo.charAt(3))
               && Character.isDigit(codigo.charAt(4)) && Character.isDigit(codigo.charAt(5)));
    }
   
   /** Ler os produtos do ficheiro de texto. */
   public void leProdutos() throws IOException { 
        String linha = "";
        StringTokenizer st ;
        String codigo;
        try (BufferedReader bin = new BufferedReader(new FileReader("Produtos.txt"))) {
           while (bin.ready())
           {
               linha = bin.readLine();
               st = new StringTokenizer(linha," ");
               codigo = st.nextToken();
               if (codigoValido(codigo))
                   catalogoProdutos.add(codigo);
               codigo = null;
           }
       }
    }
}

