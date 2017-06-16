public class ParCodigoDouble
{
    // Variáveis de Instância
    private String cod;
    private double x;

    // Gets
    public ParCodigoDouble() {
        cod = "";
        x = 0;
    }
    public ParCodigoDouble(String codigo) {
        cod = codigo;
        x = 0;
    }
    public ParCodigoDouble(String codigo,double y) {
        cod = codigo;
        x = y;
    }
    public ParCodigoDouble(ParCodigoDouble par) {
        cod = par.getCodigo();
        x = par.getDouble();
    }
    
    // Gets
    public double getDouble() {
        return x;
    }
    public String getCodigo() {
        return cod;
    }
    
    // Sets
    public void setDouble(double y) {
        x = y;
    }
    public void setCodigo(String s) {
        cod = s;
    }
    
    // Clone
    public ParCodigoDouble clone() {
        return new ParCodigoDouble(this);
    }
    
    // toString
    public String toString(String arg1, String arg2) {
        StringBuilder sb = new StringBuilder();
        sb.append(arg1 + cod);
        sb.append(arg2 + x + "\n");
        return sb.toString();
    }
}
