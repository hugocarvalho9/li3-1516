import java.util.*;
import java.io.*;
import static java.lang.System.out;

public class Hipermercado implements Serializable
{
    // Variáveis de Instância
    private CatalogoProdutos catProd;
    private CatalogoClientes catCli;
    private Faturacao faturacao;
    private ArrayList<Filial> filial;
    private int numFiliais = 3;

    // Construtor
    public Hipermercado() {
        catProd = new CatalogoProdutos();
        catCli = new CatalogoClientes();
        faturacao = new Faturacao();
        filial = new ArrayList<>(3);
    }
    
    // Gets
    
    /** Devolve o catálogo de produtos. */
    public CatalogoProdutos getCatProd() {
        return catProd; 
    }
    /** Devolve o catálogo de cliente. */
    public CatalogoClientes getCatCli() { 
        return catCli;
    }
    /** Devolve a faturação. */
    public Faturacao getFaturacao() { 
        return faturacao;
    }
    /** Devolve o filial. */
    public Filial getFilial(int i) { 
        return filial.get(i-1); 
    }
    
    /** Recebe uma linha e converte para Venda. */
    public Venda passarLinhaVenda(String linha){
       String[] paramVenda = new String[7];
       paramVenda = linha.split(" ");
       Venda v = new Venda(paramVenda);
       return v;
    }
    
    /** Ler ficheiros de texto e carregar os dados. */
    public String carregaDados(String nome) {
        // Iniciar os módulos e apagar os das leituras anteriores;
        catProd = new CatalogoProdutos();
        catCli = new CatalogoClientes();
        faturacao = new Faturacao();
        filial = new ArrayList<>(numFiliais);
        int f = 0;
        while(f < numFiliais){
            filial.add(new Filial());
            f++;
        }
        
        // CLIENTES -> leitura do ficheiro
        try { catCli.leClientes(); }
        catch (IOException e) { };
        
        // PRODUTOS -> leitura do ficheiro
        try { catProd.leProdutos(); }
        catch (IOException e) { };
                
        // VENDAS
        Set<String> prods = new TreeSet<>();
        Set<String> clis = new TreeSet<>();
        
        String linha = "", txt = "";
        String codProd, codCli;
        int numVendas = 0,comprasAZero = 0;
        double fatTotal = 0;
        Venda v;
        try {BufferedReader bin = new BufferedReader (new FileReader(nome + ".txt")); 
            while (bin.ready()){
                linha = bin.readLine();
                v = new Venda(passarLinhaVenda(linha));
                if(vendaValida(v)){
                    if(!vendaPrecoZero(v)){
                        this.faturacao.addFaturacao(v.clone());
                        this.filial.get(v.getFilial()-1).addVenda(v.clone());
                        clis.add(v.getCodigoCliente());
                        prods.add(v.getCodigoProduto());
                        fatTotal += v.getPreco()*v.getUnidades();
                    }
                    else {
                        comprasAZero++;
                    }
                }
                v = null;
                numVendas++;
            }
            bin.close();
        }
        catch(FileNotFoundException e) {out.println(e.getMessage()); }
        catch(IOException e) {out.println(e.getMessage()); }
        
        // DADOS DO ÚLTIMO FICHEIRO LIDO
        StringBuilder sb = new StringBuilder();
        sb.append("\nNome do ficheiro de Compras: " + nome);
        sb.append("\nNúmero de vendas lidas: " + numVendas);
        sb.append("\nTotal de vendas erradas: " + (numVendas - faturacao.getNumeroVendas()));
        sb.append("\nTotal de produtos: " + catProd.size());
        sb.append("\nTotal de produtos diferentes comprados: " + prods.size());
        sb.append("\nTotal de produtos nunca comprados: " + (catProd.size() - prods.size()));
        sb.append("\nTotal de clientes: " + catCli.size());
        sb.append("\nTotal de clientes que realizaram compras: " + clis.size());
        sb.append("\nTotal de clientes que nada compraram: " + (catCli.size() - clis.size()));
        sb.append("\nTotal de compras de valor igual a 0: " + comprasAZero);
        sb.append("\nTotal faturado: " + fatTotal + "\n");
   
        return sb.toString();
    }
    
    // Queries estátisticas
    
    /** Número de compras para cada mês. */
    public String numeroComprasPorMes() {
        StringBuilder sb = new StringBuilder();
        int compMes = 0;
        int fil = 0,mes =1;
        while(mes <= 12){
            while (fil < numFiliais){
                compMes += filial.get(fil).comprasMes(mes);
                fil ++;
            }
            sb.append("\nNúmero de Compras no mês " + (mes) + ":   " + compMes);
            compMes=0;
            fil = 0;
            mes ++;
        }
        sb.append("\n\n");
        return sb.toString();
    }
    /** Faturado em cada mês e faturado total. */
    public String fatTotalMes() {
        StringBuilder sb = new StringBuilder();
        double fatMes = 0.0,fatTotal = 0;
        for (int i = 1; i <= 12; i++) {
                fatMes = faturacao.getFaturadoPorMes(i);
                sb.append("\nFaturado no mês " + (i) + ":   " + fatMes);
                fatTotal += fatMes;
                fatMes = 0.0;
         }
        sb.append("\nFaturação total:   " + fatTotal);
        sb.append("\n\n");
        return sb.toString();
    }
    /** Número de clientes ativos em cada mês. */
    public String numeroClientesMes() {
        StringBuilder sb = new StringBuilder();
        Set<String> res = new TreeSet<>();
        Set<String> aux = null;
        int numC = 0,mes = 1,fil = 0;
        while(mes <= 12){
            while(fil < numFiliais){
                aux = filial.get(fil).getClientesMes(mes);
                for(String s: aux)
                res.add(s);
                fil ++;
            }
            sb.append("\nNúmero de Clientes no mês " + (mes) + ":   " + res.size());
            fil = 0;
            mes ++;
        }
        sb.append("\n\n");
        return sb.toString();
    }
    
    // Queries interativas
    
    // Querie 1
    /** Lista ordenada alfabeticamente com os códigos dos produtos nunca comprados. */
    public List<String> querie1 () {
        Set<String> prod = catProd.getProdutos();
        List<String> res = new ArrayList<>();
        prod.stream().forEach((i) -> {
                                        if(!faturacao.existeCompraProduto(i))
                                            res.add(i); 
                                    });
        return res;
    }
    // Querie 2
    /** Dado um mês válido, determinar o número total global de vendas realizadas e o número total de clientes distintos que as fizeram. */
    public ParInt querie2(int mes) {
        Set<String> res = new TreeSet<>();
        Set<String> aux = null;
        int comprasMes = 0, clientes = 0, fil = 0;
        while(fil < numFiliais){
            comprasMes += filial.get(fil).comprasMes(mes);
            fil++;
        }
        fil = 1;
        res = filial.get(0).getClientesMes(mes);
        while(fil < numFiliais){
            aux = filial.get(fil).getClientesMes(mes);
            for(String s: aux)
                res.add(s);
            fil ++;
        }
        clientes = res.size();
        return new ParInt(comprasMes,clientes);
    }
    // Querie 3
    /** Dado um código de cliente, determinar, para cada mês, quantas compras fez, 
     *  quantos produtos distintos comprou e quanto gastou no total. */
    public List<TrioIntIntDouble> querie3(String codCli)throws ClienteNaoExiste {
        if(!catCli.existeCliente(codCli))
            new ClienteNaoExiste(codCli);
        int nCompras = 0, nProd = 0, fil = 0, mes = 1;
        double fat = 0;
        List<TrioIntIntDouble> res = new ArrayList<>(12);
        while(mes <= 12){
            while(fil < numFiliais){
                nCompras+=filial.get(fil).numeroComprasCliMes(codCli,mes);
                fat+=filial.get(fil).faturadoCliMes(codCli,mes);
                nProd+=filial.get(fil).numeroProdutosCliMes(codCli,mes);
                fil++;
            }
            res.add(new TrioIntIntDouble(nCompras,nProd,fat));
            mes++;
            fil = 0;
            nCompras = 0;
            fat = 0;
            nProd = 0;
        }
        return res;
    }
    // Querie 4
    /** Dado o código de um produto existente, determinar, mês a mês, quantas vezes foi comprado, 
     *  por quantos clientes diferentes e o total facturado. */
    public List<TrioIntIntDouble> querie4(String codProd)throws ProdutoNaoExiste {
        if(!catProd.existeProduto(codProd))
            new ProdutoNaoExiste(codProd);
        int nCompras = 0, nCli = 0, fil = 0, mes = 1;
        double fat = 0;
        List<TrioIntIntDouble> res = new ArrayList<>(12);
        while(mes <= 12){
            while(fil < numFiliais){
                nCompras+=filial.get(fil).numeroComprasProdMes(codProd,mes);
                nCli+=filial.get(fil).numeroClientesProdMes(codProd,mes);
                fil++;
            }
            fat=faturacao.faturadoProdMes(codProd,mes);
            res.add(new TrioIntIntDouble(nCompras,nCli,fat));
            fil = 0;
            mes ++;
            nCompras = 0;
            fat = 0;
            nCli = 0;
        }
        return res;
    }
    // Querie 5
    /** Dado o código de um cliente determinar a lista de códigos de produtos que mais comprou (e quantos), 
     *  ordenada por ordem decrescente de quantidade e, para quantidades iguais, por ordem alfabética dos código. */
    public Set<ParCodigoInt> querie5(String cli)throws ClienteNaoExiste {
        if(!catCli.existeCliente(cli))
            new ClienteNaoExiste(cli);
        Map<String,Ficha> ts = new TreeMap<>();
        Set<ParCodigoInt> res = new TreeSet<>(new ComparatorParCodInt());
        RegistosVenda reg = new RegistosVenda(cli);
        int f = 0;
        while(f<numFiliais){
            reg.addAll(filial.get(f).produtosComprados(cli));
            f++;
        }
        ts = reg.getRegistos();
        for(Ficha ficha : ts.values()){
            res.add(new ParCodigoInt(ficha.getCodProduto(),ficha.getUnidades()));
        }
        return res;
    }
    // Querie 6
    /** Determinar o conjunto dos X produtos mais vendidos em todo o ano (em número de unidades vendidas),
     *  indicando o número total de distintos clientes que o compraram (X é um inteiro dado pelo utilizador). */
    public Set<TrioCodigoIntInt> querie6(int x) {
        Set<TrioCodigoIntInt> res = new TreeSet<>(new ComparatorTrioCodigoIntInt());
        Set<String> prodMaisVend = faturacao.produtosMaisVendidos(x);
        Iterator<String> iterator = prodMaisVend.iterator();
        String cod = null;
        int numCli = 0,numUnidVend = 0, fil = 0;
        while(iterator.hasNext()) {
            cod = iterator.next();
            while(fil < numFiliais){
                numCli += filial.get(fil).numeroClientesProd(cod);
                numUnidVend += filial.get(fil).numeroUnidadesProd(cod);
                fil++;
            }
            res.add(new TrioCodigoIntInt(cod,numUnidVend,numCli));
            numCli = 0;
            numUnidVend = 0;
            fil = 0;
        }
        return res;
    }
    // Querie 7
    /** Determinar, para cada filial, a lista dos três maiores compradores em termos de dinheiro facturado. */
    public List<List<ParCodigoDouble>> querie7() {
        List<List<ParCodigoDouble>> res = new ArrayList<>();
        int i = 0;
        while(i < numFiliais){
            res.add(filial.get(i).maioresCompradoresFat());
            i++;
        }
        return res;
    }
    // Querie 8
    /** Determinar os códigos dos X clientes (sendo X dado pelo utilizador) que compraram mais produtos diferentes 
     *  (não interessa a quantidade nem o valor), indicando quantos, 
     *  sendo o critério de ordenação a ordem decrescente do número de produtos. */
    public Set<ParCodigoInt> querie8(int x) {
        Map<String,ParCodigoInt> pares = new TreeMap<>();
        Map<String,ParCodigoInt> aux = new TreeMap<>();
        Set<ParCodigoInt> aux2 = new TreeSet<>(new ComparatorParCodInt());
        Set<ParCodigoInt> res = new TreeSet<>(new ComparatorParCodInt());
        int i = 0;
        while(i < numFiliais){
            aux = filial.get(i).maiorQuantidadeCompradaProdDif();
            aux.values().stream().forEach((n)-> {
                                    if(pares.containsKey(n.getCodigo())){
                                        pares.get(n.getCodigo()).addInt(n.getInt());
                                    }
                                    else
                                        pares.put(n.getCodigo(),n);
                                  });
           i++;
        }
        pares.values().stream().forEach((f) -> {
                                    aux2.add(f);
                                });
        i = 0;
        Iterator<ParCodigoInt> iterator = aux2.iterator();
        while( (iterator.hasNext()) && (i < x) ) {
            res.add(iterator.next());
            i++;
        }                     
        return res;
    }
    // Querie 9
    /** Dado o código de um produto que deve existir, determinar o conjunto dos X clientes 
     *  que mais o compraram e, para cada um, qual o valor gasto. */
    public Set<TrioCodigoIntDouble> querie9(String codProd,int x)throws ProdutoNaoExiste {
        if(!catProd.existeProduto(codProd))
            new ProdutoNaoExiste(codProd);
        Set<TrioCodigoIntDouble> set = new TreeSet<>(new ComparatorTrioCodigoIntDouble());
        Set<TrioCodigoIntDouble> res = new TreeSet<>(new ComparatorTrioCodigoIntDouble());
        Map<String,TrioCodigoIntDouble> aux = filial.get(0).clientesQueCompraramProd(codProd);
        Map<String,TrioCodigoIntDouble> aux2 = null;
        int fil = 1, num = 0;
        while(fil < numFiliais){
            aux2 = filial.get(fil).clientesQueCompraramProd(codProd);
            aux2.values().stream().forEach((i) -> {
                                        if(aux.containsKey(i.getCodigo()))
                                            aux.get(i.getCodigo()).add(i.clone());
                                        else
                                            aux.put(i.getCodigo(),i.clone());
                                   });
            fil++;
        }
        Iterator<Map.Entry<String, TrioCodigoIntDouble>> it = aux.entrySet().iterator();
        while (it.hasNext()) {
            set.add(it.next().getValue());
        }
        Iterator<TrioCodigoIntDouble> iter = set.iterator();
        num = 0;
        while(iter.hasNext() && num<x){
            res.add(iter.next());
            num++;
        }
        return res;
    }
    
    /** Verificar se uma venda é válida. */
    public boolean vendaValida(Venda v) {
        String codP = v.getCodigoProduto();
        String codC = v.getCodigoCliente();
        if(v.getPreco() < 0) 
            return false; 
        if(v.getMes() < 1 && v.getMes() > 12) 
            return false; 
        if(v.getFilial() < 1 && v.getFilial() > 3) 
            return false;
        if(v.getUnidades() < 0) 
            return false;
        if((!catProd.codigoValido(codP)) || (!catCli.codigoValido(codC)))
            return false;
        return (catProd.existeProduto(codP) && catCli.existeCliente(codC));
    }
    
    /** Verificar se uma venda tem preço ou uninades nulas. */
    public boolean vendaPrecoZero(Venda v) {
        if(v.getPreco() == 0 || v.getUnidades() == 0)
            return true;
        return false;
    }
    
    /** Guardar em ObjectStream. */
    public void guardarHipermercado(String nome) throws IOException {
        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(nome)); 
        oos.writeObject(this); 
        oos.flush(); 
        oos.close(); 
    }
    
    /** Ler um ObjectStream. */
    public Hipermercado lerObjeto(String nome) {
        Hipermercado hiper = new Hipermercado();
        try{
            FileInputStream file = new FileInputStream(nome);
            ObjectInputStream ler = new ObjectInputStream(file);
            hiper = (Hipermercado) ler.readObject();
            ler.close();
            file.close();
        }catch(FileNotFoundException e){
            System.out.println("Ficheiro não encontrado!");
        }catch(IOException e){
            System.out.println("Não foi possivel criar o ficheiro!");
            System.out.println(e.getMessage());
            System.out.println(e.getCause());
        }catch(ClassNotFoundException e){
            System.out.println("Classe não encontrada!");
        }
        return hiper;
    }
}
