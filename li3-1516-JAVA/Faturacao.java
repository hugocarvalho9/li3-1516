import java.util.*;
import java.io.*;
public class Faturacao implements Serializable
{
    // Vari�veis de inst�ncia
    private int nVendas;
    private double faturado;
    private Map<String,List<FaturadoPorMes>> fat;
    // Chave -> C�digo do produto
    // Valor -> Array dividido por meses
    // FaturadoPorMes -> corresponde � quantidade faturada com cada produto em cada m�s
    
    // Construtores
    public Faturacao(){
        nVendas = 0;
        faturado = 0;
        fat = new TreeMap<>();
    }
    
    // Gets
    
    /** Devolve o n�mero de vendas. */
    public int getNumeroVendas() {
        return nVendas;
    }
    /** Devolve o valor faturado por filial. */
    public double getFaturadoPorFilial(){
        return faturado;
    }
    /** Devolve o valor faturado por m�s. */
    public double getFaturadoPorMes(int mes){
        double res = 0.0;
        for(List<FaturadoPorMes> lfm : fat.values()){
            for(FaturadoPorMes fm : lfm)
                if(fm.getMes() == mes)
                    res += fm.getFaturado();
        }
        return  res;
    }
    /** Devolve o n�mero de unidades vendidas por produto. */
    public int numUnidadesVendidasProd(String codProd){
        int res = 0;
        if(fat.containsKey(codProd)){
            for(FaturadoPorMes fm : fat.get(codProd))
                res += fm.getQuantidade();
        }
        return res;
    }
    /** Devolve a fatura��o. */
    public List<FaturadoPorMes> getFaturacao(){
        List<FaturadoPorMes> res = new ArrayList<>();
        fat.values().stream()
                                .forEach((i) -> {
                                    i.forEach((list) -> {
                                        res.add(list.clone());
                                    });
                                });
        return res;
    }
    
    // M�todos
    
    /** Adicionar uma fatura��o ao Map. */
    public void addFaturacao(Venda v){
        int mes = v.getMes();
        boolean existe = false; // Verificar se existe o faturadoPorMes
        String codProd = v.getCodigoProduto();
        faturado = v.getUnidades()*v.getPreco();
        //Se j� existe a chave codProd
        if(fat.containsKey(codProd)){
            for(FaturadoPorMes f : fat.get(codProd))   
                if(f.getMes() == mes){
                    f.addRegisto(v);
                    existe = true;
                }
            if(!existe){
                FaturadoPorMes fpp = new FaturadoPorMes(v);
                fat.get(codProd).add(fpp);
            }
        }
        //Se ainda n�o existe chave
        else{
            FaturadoPorMes fpp = new FaturadoPorMes(v);
            List<FaturadoPorMes> r = new ArrayList<>(1);
            r.add(fpp);
            fat.put(codProd,r);
        }
        nVendas++;
    }
    
    /** Verificar se existe produto na fatura��o. */
    public boolean existeCompraProduto(String prod){
        return fat.containsKey(prod);
    }
    
    /** Valor faturado num dado m�s. */
    public double faturadoProdMes(String Prod,int mes){
        double res = 0;
        for(FaturadoPorMes fm : fat.get(Prod))
            if(fm.getMes() == mes)
                res += fm.getFaturado();
        return res;
    }
    
    /** Set com os produtos mais vendidos. */
    public Set<String> produtosMaisVendidos(int x){
        Set<ParCodigoInt> aux = new TreeSet<>(new ComparatorParCodInt());
        Set<String> res = new TreeSet<>();
        int i = 0;
        fat.forEach((k,s)->{
                aux.add(new ParCodigoInt(k,numUnidadesVendidasProd(k)));
            });
		Iterator<ParCodigoInt> iterator = aux.iterator();
		while( (iterator.hasNext()) && (i < x) ) {
		    res.add(iterator.next().getCodigo());
		    i++;
		}

        return res;
    }
}
