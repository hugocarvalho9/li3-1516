import java.util.Comparator;
import java.io.Serializable;
 
public class ComparatorTrioCodigoIntInt implements Comparator<TrioCodigoIntInt>, Serializable {
   public int compare(TrioCodigoIntInt e1, TrioCodigoIntInt e2) {
     if(e1.getPrimeiro() > e2.getPrimeiro()) 
        return -1;
     if(e1.getPrimeiro() < e2.getPrimeiro()) 
        return 1;
     else
         if(e1.getCodigo().compareTo(e2.getCodigo()) != 0)
             return e1.getCodigo().compareTo(e2.getCodigo());
         else
              if(e1.getSegundo() > e2.getSegundo())
                  return -1;
              else 
                  return 1;
   }
}