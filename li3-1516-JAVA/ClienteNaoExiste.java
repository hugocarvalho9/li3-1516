import java.util.*;
public class ClienteNaoExiste extends Exception{
    public ClienteNaoExiste(){
        super();
    }
    public ClienteNaoExiste(String mensagem){
        super(mensagem);
    }
}