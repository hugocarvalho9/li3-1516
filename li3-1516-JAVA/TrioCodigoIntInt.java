public class TrioCodigoIntInt
{
    // Variáveis de Instância
    private String cod;
    private int y;
    private int z;

    // Construtores
    public TrioCodigoIntInt() {
        cod = "";
        y = 0;
        z = 0;
    }
    public TrioCodigoIntInt(String s,int x,int z) {
        this.cod = s;
        this.y = x;
        this.z = z;
    }
    public TrioCodigoIntInt(TrioCodigoIntInt t) {
        cod = t.getCodigo();
        y = t.getPrimeiro();
        z = t.getSegundo();
    }
    
    // Gets
    public String getCodigo() {
        return cod;
    }
    public int getPrimeiro() {
        return y;
    }
    public int getSegundo() {
        return z;
    }
    
    // toString
    public String toString(String arg1,String arg2,String arg3) {
        StringBuilder sb = new StringBuilder();
        sb.append(arg1 + ": " + cod + "     ");
        sb.append(arg2 + ": " + y + "     ");
        sb.append(arg3 + ": " + z + "\n");
        return sb.toString();
    }
    
    // Clone
    public TrioCodigoIntInt clone() {
        return new TrioCodigoIntInt(this);
    }
}
