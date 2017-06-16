import java.util.*;
import java.io.*;
public class Faturacao implements Serializable
{
    // Variáveis de instância
    private int nVendas;
    private double faturado;
    private Map<String,List<FaturadoPorMes>> fat;
    // Chave -> Código do produto
    // Valor -> Array dividido por meses
    // FaturadoPorMes -> corresponde à quantidade faturada com cada produto em cada mês
    
    // Construtores
    public Faturacao(){
        nVendas = 0;
        faturado = 0;
        fat = new TreeMap<>();
    }
    
    // Gets
    
    /** Devolve o número de vendas. */
    public int getNumeroVendas() {
        return nVendas;
    }
    /** Devolve o valor faturado por filial. */
    public double getFaturadoPorFilial(){
        return faturado;
    }
    /** Devolve o valor faturado por mês. */
    public double getFaturadoPorMes(int mes){
        double res = 0.0;
        for(List<FaturadoPorMes> lfm : fat.values()){
            for(FaturadoPorMes fm : lfm)
                if(fm.getMes() == mes)
                    res += fm.getFaturado();
        }
        return  res;
    }
    /** Devolve o número de unidades vendidas por produto. */
    public int numUnidadesVendidasProd(String codProd){
        int res = 0;
        if(fat.containsKey(codProd)){
            for(FaturadoPorMes fm : fat.get(codProd))
                res += fm.getQuantidade();
        }
        return res;
    }
    /** Devolve a faturação. */
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
    
    // Métodos
    
    /** Adicionar uma faturação ao Map. */
    public void addFaturacao(Venda v){
        int mes = v.getMes();
        boolean existe = false; // Verificar se existe o faturadoPorMes
        String codProd = v.getCodigoProduto();
        faturado = v.getUnidades()*v.getPreco();
        //Se já existe a chave codProd
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
        //Se ainda não existe chave
        else{
            FaturadoPorMes fpp = new FaturadoPorMes(v);
            List<FaturadoPorMes> r = new ArrayList<>(1);
            r.add(fpp);
            fat.put(codProd,r);
        }
        nVendas++;
    }
    
    /** Verificar se existe produto na faturação. */
    public boolean existeCompraProduto(String prod){
        return fat.containsKey(prod);
    }
    
    /** Valor faturado num dado mês. */
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
