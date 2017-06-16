import java.util.Comparator;
import java.io.Serializable;
 
public class ComparatorTrioCodigoIntDouble implements Comparator<TrioCodigoIntDouble>, Serializable {
   public int compare(TrioCodigoIntDouble e1, TrioCodigoIntDouble e2) {
     if(e1.getInt() > e2.getInt()) 
        return -1;
     if(e1.getInt() < e2.getInt()) 
        return 1;
     else
         if(e1.getCodigo().compareTo(e2.getCodigo()) != 0)
             return e1.getCodigo().compareTo(e2.getCodigo());
         else
              if(e1.getDouble() > e2.getDouble())
                  return -1;
              else 
                  return 1;
   }
}