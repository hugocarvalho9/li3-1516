import java.util.*;
import java.io.*;
public class RegistosVenda implements Serializable
{
    /**
     * Classe que representa as vendas de um cliente;
     * Ficha contém as informações das vendas de um produto;
     */
    // Variáveis de instância
    private String codigo;
    private double faturado;
    private Map<String,Ficha> vendas;
    // Chave -> Código de produto
    // Valor -> Ficha
    
    // Construtores
    public RegistosVenda () {
        codigo = "";
        faturado = 0;
        vendas = new TreeMap<>();
    }
    public RegistosVenda (String cod) {
        codigo = cod;
        faturado = 0;
        vendas = new TreeMap<>();
    }
    
    // Gets
    
    /** Devolve o código de produto. */
    public String getCodigo() {
        return codigo;
    }
    /** Devolve o valor faturado. */
    public double getFaturado() {
        return faturado;
    }
    /** Devolve o número de compras. */
    public int numeroCompras() {
        return vendas.values().stream().mapToInt(Ficha :: getNumeroCompras).sum();
    }
    /** Devolve o número de produtos. */
    public int numeroProdutos() {
        return vendas.size();
    }
    /** Devolve o número de vezes que um produto foi comprado. */
    public int numeroComprasProduto(String prod) {
        if(vendas.containsKey(prod))
            return vendas.get(prod).getNumeroCompras();
        return 0;
    }
    /** Devolve o valor faturado com um dado produto. */
    public double faturaPorProd(String codProd) {
        if(vendas.containsKey(codProd))
            return vendas.get(codProd).getFaturado();
        return 0;
    }
    /** Devolve o número de unidades de um produto. */
    public int numeroUnidadesProduto(String prod) {
        if(vendas.containsKey(prod))
            return vendas.get(prod).getUnidades();
        return 0;
    }
    /** Devolve um Map de Registos. */
    public Map<String,Ficha> getRegistos() {
        Map<String,Ficha> r = new TreeMap<>();
        vendas.values().stream()
                       .forEach((i) -> {
                           r.put(i.getCodProduto(),i.clone());
                        });
        return r;
    }
    
    /** Converte RegistosVendas para string. */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        sb.append("Código Cliente : " + codigo + "\n");
        sb.append("Faturação total do Cliente : " + faturado + "\n");
        sb.append("\n");
        vendas.values().stream().forEach((i) -> {
                                sb.append(i.toString());
        });
        return sb.toString();
    }
    
    /** Faz um clone de RegistosVendas. */
    public RegistosVenda clone() {
        RegistosVenda r = new RegistosVenda(codigo);
        vendas.values().stream()
                       .forEach((i) -> {
                           r.addFicha(i);
                        });
        return r;
    }
    
    // Métodos
    
    /** Adicionar uma venda ao Map de vendas. */
    public void addVenda (Venda v) {
        String codProd = v.getCodigoProduto();
        double p = v.getPreco();
        int u = v.getUnidades(); 
        faturado += p * u;
        if(vendas.containsKey(codProd)){
            vendas.get(codProd).addVenda(v);
        }
        else{
            Ficha f = new Ficha(v);
            vendas.put(codProd,f);
        }
    }
    
    /** Adiciona uma ficha ao Map de vendas. */
    public void addFicha (Ficha ficha) {
        String codProd = ficha.getCodProduto();
        if(vendas.containsKey(codProd)){
            vendas.get(codProd).add(ficha);
        }
        else{
            vendas.put(codProd,ficha.clone());
        }
    }
    
    /** Verificar se um produto existe no Map vendas. */
    public boolean existeProduto(String prod) {
       return vendas.containsKey(prod);
    }
    
    /** Devolve um par (Produto, NumeroCompras). */
    public Map<String,ParCodigoInt> mapParesCodigoInt() {
       String prod = null;
       Map<String,ParCodigoInt> res = new TreeMap<>();
       for(Ficha f : vendas.values()){
           prod = f.getCodProduto();
           res.put(prod, new ParCodigoInt(prod,f.getNumeroCompras()));
       }
       return res;
    }
    
    /** Adicionar todo o RegistoVenda. */
    public void addAll(RegistosVenda v){
        faturado += v.getFaturado();
        Map<String,Ficha> r = v.getRegistos();
        r.values().stream().forEach((i)-> {
                                addFicha(i.clone());
                            });
    }
}
