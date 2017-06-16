import java.io.Serializable;
public class Ficha implements Serializable
{
    /**
     * Classe que guarda os valores de cada compra por produto;
     */
    
    // Variáveis de instância 
    private String produto;
    private int numeroCompras;
    private int unidades;
    private double faturado;
   
    // Construtores
    public Ficha (String p) {
        produto = p;
        numeroCompras = 0;
        unidades = 0;
        faturado = 0;
    }
    public Ficha (Ficha f) {
        produto = f.getCodProduto();
        unidades = f.getUnidades();
        faturado = f.getFaturado();
        numeroCompras = f.getNumeroCompras();
    }
    public Ficha (Venda v) {
        int und = v.getUnidades();
        numeroCompras = 1;
        unidades = und;
        faturado = und * v.getPreco();
        produto = v.getCodigoProduto();
    }
    
    // Gets
    
    /** Devolve o valor faturado. */
    public double getFaturado() { 
        return faturado; 
    }
    /** Devolve o número de unidades. */
    public int getUnidades() { 
        return unidades; 
    }
    /** Devolve o número de compras. */
    public int getNumeroCompras(){
        return numeroCompras;
    }
    /** Devolve o código do produto. */
    public String getCodProduto(){
        return produto;
    }
    
    /** Faz um clone de Ficha. */
    public Ficha clone(){
        return new Ficha(this);
    }
    
    /** Converte Ficha para string. */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        
        sb.append("Código Produto : " + produto + "\n");
        sb.append("Faturado : " + faturado + "\n");
        sb.append("Número de unidades compradas : " + unidades + "\n");
        sb.append("Número de compras : " + numeroCompras + "\n");
        
        return sb.toString();
    }
    
    /** Recebe uma venda e adiciona à sua ficha. */
    public void addVenda(Venda v){
        int und = v.getUnidades();
        numeroCompras++;
        unidades += und;
        faturado = v.getPreco() * und;
    }
    
    /** Recebe um ficha e adiciona-a. */
    public void add(Ficha f){
        unidades += f.getUnidades();
        faturado += f.getFaturado();
        numeroCompras += f.getNumeroCompras();
    }
}
