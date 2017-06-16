import java.io.Serializable;
public class Ficha implements Serializable
{
    /**
     * Classe que guarda os valores de cada compra por produto;
     */
    
    // Vari�veis de inst�ncia 
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
    /** Devolve o n�mero de unidades. */
    public int getUnidades() { 
        return unidades; 
    }
    /** Devolve o n�mero de compras. */
    public int getNumeroCompras(){
        return numeroCompras;
    }
    /** Devolve o c�digo do produto. */
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
        
        sb.append("C�digo Produto : " + produto + "\n");
        sb.append("Faturado : " + faturado + "\n");
        sb.append("N�mero de unidades compradas : " + unidades + "\n");
        sb.append("N�mero de compras : " + numeroCompras + "\n");
        
        return sb.toString();
    }
    
    /** Recebe uma venda e adiciona � sua ficha. */
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
