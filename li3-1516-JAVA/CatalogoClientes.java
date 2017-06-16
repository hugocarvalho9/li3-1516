import java.util.*;
import java.io.*;
import java.lang.String;
import java.lang.Character;
import java.util.Iterator;

public class CatalogoClientes implements Serializable
{
    // Variável de Instância
    private Set<String> catalogoClientes;

    // Construtores
    public CatalogoClientes(){ 
        catalogoClientes = new TreeSet<>();
    }
    public CatalogoClientes(Set<String> set) {
        catalogoClientes = new TreeSet<>();
        set.stream().forEach((s) -> {
            catalogoClientes.add(s);
        });
    }
    public CatalogoClientes(CatalogoClientes catCli){
        catalogoClientes = new TreeSet<>();
        catCli.getClientes().stream().forEach((s) -> {
            catalogoClientes.add(s);
        });
    }
    
    // Métodos
    
    /** Set com todos os clientes lidos. */
    public Set<String> getClientes() {
        Set<String> catCli = new TreeSet<>();
        catalogoClientes.stream().forEach((cliente) -> {
            catCli.add(cliente);
        });
        return catCli;
    }
    
    /** Tamanho do catálogo. */
    public int size() {
        return (catalogoClientes.size());
    }
    
    /** Verificar se um cliente existe. */
    public boolean existeCliente (String codigo) {
        return catalogoClientes.contains(codigo);
    }
    
    /** Verificar se o código do cliente é válido. */
    public boolean codigoValido(String codigo) {
        return (codigo.length() == 5 && Character.isUpperCase(codigo.charAt(0)) 
               && Character.isDigit(codigo.charAt(1)) && Character.isDigit(codigo.charAt(2))
               && Character.isDigit(codigo.charAt(3)) && Character.isDigit(codigo.charAt(4)));
    }
    
    /** Número de clientes duplicados. */
    public int clientesNaoDuplicados(Set<String> duplicados) {
        Set<String> copia = new HashSet<>();
        duplicados.stream().forEach((s) -> {
            copia.add(s);
        });
        return (duplicados.size() - copia.size());
    }
    
    /** Ler os clientes do ficheiro de texto. */
    public void leClientes () 
            throws IOException { 
        String linha = "";
        StringTokenizer token ; //extração das palavras separadas entre si por \b,\t ou \n.
        String codigo;
        try (BufferedReader bin = new BufferedReader(new FileReader("Clientes.txt"))) {
            while (bin.ready())
            {
                linha = bin.readLine();
                token = new StringTokenizer(linha," ");
                codigo = token.nextToken();
                if(codigoValido(codigo))
                    catalogoClientes.add(codigo);
                codigo = null;
            }
        }
    }
    
}
