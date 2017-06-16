import java.util.Comparator;
import java.io.Serializable;
 
public class ComparatorParCodDouble implements Comparator<ParCodigoDouble>, Serializable {
   public int compare(ParCodigoDouble e1, ParCodigoDouble e2) {
     if(e1.getDouble() > e2.getDouble()) 
        return -1;
     if(e1.getDouble() < e2.getDouble()) 
        return 1;
     else
         return e1.getCodigo().compareTo(e2.getCodigo());
   }
}