public class ParCodigoInt
{
    // Variáveis de Instância
    private String cod;
    private int x;

    // Construtores
    public ParCodigoInt() {
        cod = "";
        x = 0;
    }
    public ParCodigoInt(String codigo) {
        cod = codigo;
        x = 0;
    }
    public ParCodigoInt(String codigo,int n) {
        cod = codigo;
        x = n;
    }
    public ParCodigoInt(ParCodigoInt i) {
        cod = i.getCodigo();
        x = i.getInt();
    }
    
    // Gets
    public int getInt() {
        return x;
    }
    public String getCodigo() {
        return cod;
    }
    
    // Sets
    public void setInt(int y){
        x = y;
    }
    public void setCodigo(String s){
        cod = s;
    }
    public void addInt(int z){
        x += z;
    }
    
    // toString
    public String toString(String arg1, String arg2){
        StringBuilder sb = new StringBuilder();
        sb.append(arg1 + ": " + cod + "     ");
        sb.append(arg2 + ": " + x);
        return sb.toString();
    }
}
