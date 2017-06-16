import java.io.*;
import java.util.*;
public class FaturadoPorMes implements Serializable
{
    // Variáveis de Instãncia
    private String codigoProd;
    private int mes;
    private int quantidade;
    private double faturado;
    
    // Construtores
    public FaturadoPorMes (String cod,int mes) {
        this.mes = mes;
        codigoProd = cod;
        quantidade = 0;
        faturado = 0.0;
    }
    public FaturadoPorMes (String codProd,int mes,int quant,double fat) {
        this.mes = mes;
        quantidade = quant;
        faturado = fat;
        codigoProd = codProd;
    }
    public FaturadoPorMes (FaturadoPorMes fat) {
        codigoProd = fat.getCodigo();
        quantidade = fat.getQuantidade();
        faturado = fat.getFaturado();
    }
    public FaturadoPorMes (Venda v) {
        codigoProd = v.getCodigoProduto();
        mes = v.getMes();
        quantidade = v.getUnidades();
        faturado = v.getUnidades() * v.getPreco();
    }
    
    //Gets
    
    /** Devolve o código do produto. */
    public String getCodigo(){
        return codigoProd;
    }
    /** Devolve a quantidade de produtos. */
    public int getQuantidade(){
        return quantidade;
    }
    /** Devolve o valor faturado. */
    public double getFaturado(){
        return faturado;
    }
    /** Devolve o mês. */
    public int getMes() {
        return mes;
    }
    
    /** Faz um clone de FaturadoPorMes. */
    public FaturadoPorMes clone(){
        return new FaturadoPorMes(this);
    }
    
    /** Dada uma venda adicioná-la ao registo. */
    public void addRegisto(Venda v){
        int q = v.getUnidades();
        double fat = v.getPreco() * q;
        quantidade += q;
        faturado += fat;
    }
    
    /** Representar os dados como string. */
    public String toString(){
        StringBuilder sb = new StringBuilder();

        sb.append("\nCódigo produto: " + codigoProd);
        sb.append("\nMês: " + mes);
        sb.append("\nQuantidade: " + quantidade);
        sb.append("\nFaturado: " + faturado);
        return sb.toString();
    }
}