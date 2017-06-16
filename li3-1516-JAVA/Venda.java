import java.lang.String;
import java.io.Serializable;
public class Venda implements Serializable
{
    // Variáveis de Instância
    private String codigoProduto;
    private String codigoCliente;
    private double preco;
    private int unidades;
    private int mes;
    private int filial;
    
    // Construtores
    public Venda(){};
    public Venda (String codP, double pr, int unid, String codC, int m, int f) {
        codigoProduto = codP;
        preco = pr;
        unidades = unid;
        codigoCliente = codC;
        mes = m;
        filial = f;
    }
    public Venda(Venda v) {
        this.codigoProduto = v.getCodigoProduto();
        this.preco = v.getPreco();
        this.unidades = v.getUnidades();
        this.codigoCliente = v.getCodigoCliente();
        this.mes = v.getMes();
        this.filial = v.getFilial();
    }
    public Venda(String[] v){
        this(v[0],Double.parseDouble(v[1]),
             Integer.parseInt(v[2]),v[4],
             Integer.parseInt(v[5]),Integer.parseInt(v[6]));
    }
    
    // Gets
    
    /** Devolve o código do produto. */
    public String getCodigoProduto () { 
        return codigoProduto; 
    }
    /** Devolve o preço do produto. */
    public double getPreco() { 
        return preco; 
    }
    /** Devolve as unidades de produto vendidas. */
    public int getUnidades() { 
        return unidades; 
    }
    /** Devolve o código do cliente. */
    public String getCodigoCliente() { 
        return codigoCliente; 
    }
    /** Devolve o mês da venda. */
    public int getMes() { 
        return mes; 
    }
    /** Devolve o filial da venda. */
    public int getFilial() { 
        return filial; 
    }
    
    /** Faz um clone de venda. */
    public Venda clone() {
        return new Venda(this);
    }

    /** Verifica se duas vendas são iguais. */
    public boolean equals(Object o) {
        if (o == this) { return true; }
        if (o == null || o.getClass() != this.getClass()) { return false; }
        Venda v = (Venda) o;
        return (v.getCodigoProduto() == codigoProduto &&
                v.getPreco() == preco && 
                v.getUnidades() == unidades &&
                v.getCodigoCliente() == codigoCliente &&
                v.getMes() == mes &&
                v.getFilial() == filial);
    }

    /** Converter Venda em string. */
    public String toString () {
        StringBuilder s;
        s = new StringBuilder();
        s.append("Código de Produto: "); s.append(codigoProduto);
        s.append("\nPreco: "); s.append(preco);
        s.append("\nUnidades: "); s.append(unidades);
        s.append("\nCódigo de Cliente: "); s.append(codigoCliente);
        s.append("\nMês: "); s.append(mes);
        s.append("\nFilial: "); s.append(filial);
        return s.toString();
    }
}
