public class TrioCodigoIntDouble
{
    // Variáveis de Instância
    private String cod;
    private int y;
    private double z;

    // Construtores
    public TrioCodigoIntDouble() {
        cod = "";
        y = 0;
        z = 0;
    }
    public TrioCodigoIntDouble(String s,int x,double z) {
        this.cod = s;
        this.y = x;
        this.z = z;
    }
    public TrioCodigoIntDouble(TrioCodigoIntDouble t) {
        cod = t.getCodigo();
        y = t.getInt();
        z = t.getDouble();
    }
    
    // Gets
    public String getCodigo() {
        return cod;
    }
    public int getInt() {
        return y;
    }
    public double getDouble() {
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
    
    // Métodos para adicionar
    public void add(int y,double z) {
        this.y += y;
        this.z += z;
    }
    public void add(TrioCodigoIntDouble t) {
        this.y += t.getInt();
        this.z += t.getDouble();
    }
    
    // Clone
    public TrioCodigoIntDouble clone() {
        return new TrioCodigoIntDouble(this);
    }
}
