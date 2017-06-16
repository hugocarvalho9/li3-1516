import java.util.*;
import java.io.*;
public class Filial implements Serializable
{
    /**
     * Classe que guarda os valores importantes de cada venda:
     * 1� - Lista que divide os meses;
     * 2� - Map<CodCliente,RegistoVenda>;
     * 3� - RegistoVendas � outro map organizado pelo c�digo de produto -> Map<CodProd,Ficha>;
     * 4� - Ficha representa os valores de todas as vendas pertencente a um cliente e produto.
     */

    private Set<String> clientes;
    private List<Map<String,RegistosVenda>> vendas;
    // Chave -> C�digo de cliente
    // Valor -> RegistoVendas
    // RegistoVendas -> MAP -> Chave -> C�digo de produto
    //                         Valor -> Array com as vendas
    
    // Construtores
    public Filial(){
        vendas = new ArrayList<>(12);
        clientes = new TreeSet<>();
        int i = 0;
        while(i < 12){
            vendas.add(new TreeMap<>());
            i++;
        }
    }
    
    // Gets
    
    /** Devolve um Set com clientes de um dado m�s. */
    public Set<String> getClientesMes(int mes){
        Set<String> res = new TreeSet<>();
        if(vendas.get(mes-1).size() > 0)
            vendas.get(mes-1).forEach((k,s) -> {
                                res.add(k);
            });
        return res;
    }
    /** Devolve um Set com todos os clientes. */
    public Set<String> getClientes(){
        return clientes;
    }
    
    // M�todos por meses
    
    /** Valor faturado num m�s. */
    public double faturadoMes(int mes){
        if(vendas.get(mes-1).size() > 0)
            return vendas.get(mes-1).values().stream().mapToDouble(RegistosVenda :: getFaturado).sum();
        return 0;
    }
    /** Compras feitas num m�s. */
    public int comprasMes(int mes){
        if(vendas.get(mes-1).size() > 0)
            return vendas.get(mes-1).values().stream().mapToInt(RegistosVenda :: numeroCompras).sum();
        return 0;
    }
    /** N�mero de clientes ativos num m�s. */
    public int numeroClientesMes(int mes){
        if(vendas.get(mes-1).size() > 0)
            return vendas.get(mes-1).size();
        return 0;
    }
    /** N�mero de produtos que um cliente comprou por m�s. */
    public int numeroProdutosCliMes(String codCli,int mes){
        if(vendas.get(mes-1).size() > 0)
            if(vendas.get(mes-1).containsKey(codCli))
                return vendas.get(mes-1).get(codCli).numeroProdutos();
        return 0;
    }
    /** Valor faturado por um clientes num m�s. */
    public double faturadoCliMes(String cli,int mes){
        if(vendas.get(mes-1).size() > 0)
            if(vendas.get(mes-1).containsKey(cli))
                return vendas.get(mes-1).get(cli).getFaturado();
        return 0;
    }
    /** N�mero de compras de um cliente num m�s. */
    public int numeroComprasCliMes(String cli,int mes){
        if(vendas.get(mes-1).size() > 0)
            if(vendas.get(mes-1).containsKey(cli))
                return vendas.get(mes-1).get(cli).numeroCompras();
        return 0;
    }
    /** N�mero de compras de um produto num m�s. */
    public int numeroComprasProdMes(String codProd,int mes){
        int res = 0;
        if(vendas.get(mes-1).size() > 0)
            for(RegistosVenda i: vendas.get(mes-1).values()){
                res += i.numeroComprasProduto(codProd);
            }
        return res;
    }
    /** N�mero de clientes que compraram um produto num m�s. */
    public int numeroClientesProdMes(String prod,int mes){
        int res = 0;
        if(vendas.get(mes-1).size() > 0)
            for(RegistosVenda r : vendas.get(mes-1).values()){
                if(r.existeProduto(prod))
                    res++;
                }
        return res;
    }
    /** N�mero de unidades de produto compradas num m�s. */
    public int numeroUnidadesProdMes(String prod,int mes){
        int res = 0;
        if(vendas.get(mes-1).size() > 0)
            for(RegistosVenda r : vendas.get(mes-1).values()){
                if(r.existeProduto(prod))
                    res += r.numeroUnidadesProduto(prod);
                }
        return res;
    }
    
    //M�todos globais
    
    /** Valor faturado por um cliente. */
    public double faturadoCli(String cli){
        double fat = 0;
        int mes = 1;
        while(mes <= 12){
            fat += faturadoCliMes(cli,mes);
            mes++;
        }
        return fat;
    }
    /** N�mero de produtos que um cliente comprou. */
    public int numeroProdutosCli(String cli){
        int res = 0, mes = 1;
        while(mes <= 12){
            res += numeroProdutosCliMes(cli,mes);
            mes++;
        }
        return res;
    }
    /** N�mero de clientes que compraram um produto. */
    public int numeroClientesProd(String prod){
        int res = 0, mes = 1;
        while(mes <= 12){
            res += numeroClientesProdMes(prod,mes);
            mes++;
        }
        return res;
    }
    /** N�mero de unidades de produto compradas. */
    public int numeroUnidadesProd(String prod){
        int res = 0, mes = 1;
        while(mes <= 12){
            res += numeroUnidadesProdMes(prod,mes);
            mes++;
        }
        return res;
    }
    
    /** Adicionar uma venda ao filial. */
    public void addVenda(Venda v){
        String codCli = v.getCodigoCliente();
        int mes = v.getMes() - 1;
        clientes.add(v.getCodigoCliente());
        if(vendas.get(mes).containsKey(codCli)){
            vendas.get(mes).get(codCli).addVenda(v);
        }
        else{
            RegistosVenda r = new RegistosVenda(v.getCodigoCliente());
            r.addVenda(v);
            vendas.get(mes).put(codCli,r);
        }
    }
    
    /** Devolve um RegistoVenda com os produtos mais comprados. */
    public RegistosVenda produtosComprados(String cli){
        RegistosVenda res = new RegistosVenda();
        int mes = 0;
        while(mes < 12){
            if(vendas.get(mes).containsKey(cli))
                res.addAll(vendas.get(mes).get(cli));
            mes++;
        }
        return res;
     }
    
    /** Devolve uma lista com os tr�s melhores compradores, num par(Cliente, Valor). */
    public List<ParCodigoDouble> maioresCompradoresFat(){
        List<ParCodigoDouble> res = new ArrayList<>(3);
        Set<ParCodigoDouble> aux = new TreeSet<>(new ComparatorParCodDouble());
        ParCodigoDouble par = null;
        int i = 0;
        double fat = 0;
        for(String codCli : clientes){
            fat = faturadoCli(codCli);
            par = new ParCodigoDouble(codCli,fat);
            aux.add(par);
        }
        Iterator<ParCodigoDouble> iterator = aux.iterator();
        while( (iterator.hasNext()) && (i < 3) ) {
            res.add(iterator.next());
            i++;
        }
        return res;
    }
    
    /** Devolve um Map com a maior quantidade comprada de produtos diferentes. */
    public Map<String,ParCodigoInt> maiorQuantidadeCompradaProdDif(){
        Map<String,ParCodigoInt> res = new TreeMap<>();
        ParCodigoInt par = null;
        for(String codCli : clientes){
            par = new ParCodigoInt(codCli,numeroProdutosCli(codCli));
            res.put(codCli,par);
        }
        return res;
    }
    
    /** Devolve um Map com os cliente que compraram produtos. */
    public Map<String,TrioCodigoIntDouble> clientesQueCompraramProd(String prod){
        Map<String,TrioCodigoIntDouble> res = new TreeMap<>();
        int mes = 0;
        while(mes < 12){
            vendas.get(mes).values().stream().forEach((i) -> {
                                                if(i.existeProduto(prod))
                                                    if(res.containsKey(i.getCodigo()))
                                                        res.get(i.getCodigo()).add(i.numeroUnidadesProduto(prod),i.faturaPorProd(prod));
                                                    else
                                                        res.put(i.getCodigo(),new TrioCodigoIntDouble(i.getCodigo(),i.numeroUnidadesProduto(prod),i.faturaPorProd(prod)));
                                              });
            mes++;
        }
        return res;
    }
}
