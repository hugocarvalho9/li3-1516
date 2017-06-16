import java.util.*;
public class ProdutoNaoExiste extends Exception{
    public ProdutoNaoExiste() {
        super();
    }
    public ProdutoNaoExiste(String mensagem) {
        super(mensagem);
    }
}