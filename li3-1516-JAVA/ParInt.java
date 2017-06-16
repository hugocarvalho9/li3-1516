public class ParInt
{
    // Variáveis de Instância
    private int y;
    private int x;
    
    // Construtores
    public ParInt() {
        y = 0;
        x = 0;
    }
    public ParInt(int x,int y) {
        this.x = x;
        this.y = y;
    }
    
    // Gets
    public int getPrimeiro(){
        return x;
    }
    public int getSegundo(){
        return y;
    }
    
    // toString
    public String toString(String arg1,String arg2){
        StringBuilder sb = new StringBuilder();
        sb.append(arg1 + ": " + x + "     ");
        sb.append(arg2 + ": " + y + "\n");
        return sb.toString();
    }
}
