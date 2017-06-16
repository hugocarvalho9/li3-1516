import java.util.Comparator;
import java.io.Serializable;
 
public class ComparatorParCodInt implements Comparator<ParCodigoInt>, Serializable {
   public int compare(ParCodigoInt e1, ParCodigoInt e2) {
     if(e1.getInt() > e2.getInt()) 
        return -1;
     if(e1.getInt( )< e2.getInt()) 
        return 1;
     else
         return e1.getCodigo().compareTo(e2.getCodigo());
   }
}