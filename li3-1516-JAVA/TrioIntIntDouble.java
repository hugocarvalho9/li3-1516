public class TrioIntIntDouble
{
    // Variáveis de Instância
    private int x;
    private int y;
    private double z;

    // Construtores
    public TrioIntIntDouble() {
        y = 0;
        x = 0;
        z = 0;
    }
    public TrioIntIntDouble(int x,int y,double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    public TrioIntIntDouble(TrioIntIntDouble t) {
        x = t.getPrimeiro();
        y = t.getSegundo();
        z = t.getTerceiro();
    }
    
    // Gets
    public int getPrimeiro() {
        return x;
    }
    public int getSegundo() {
        return y;
    }
    public double getTerceiro() {
        return z;
    }
    
    // toString
    public String toString(String arg1,String arg2,String arg3){
        StringBuilder sb = new StringBuilder();
        sb.append(arg1 + ": " + x + "     ");
        sb.append(arg2 + ": " + y + "     ");
        sb.append(arg3 + ": " + z + "\n");
        return sb.toString();
    }
}
