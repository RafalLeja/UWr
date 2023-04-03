import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class App {
  public static void main(String[] args) throws Exception {
    Lista<Integer> oryginalnaLista = new Lista<Integer>();
    oryginalnaLista.add(2);
    oryginalnaLista.add(0);
    oryginalnaLista.add(2);
    oryginalnaLista.add(3);

    FileOutputStream fileOutputStream
      = new FileOutputStream("bufor.txt");
    ObjectOutputStream objectOutputStream
      = new ObjectOutputStream(fileOutputStream);
    objectOutputStream.writeObject(oryginalnaLista);
    objectOutputStream.flush();
    objectOutputStream.close();

    FileInputStream fileInputStream
      = new FileInputStream("bufor.txt");
    ObjectInputStream objectInputStream
      = new ObjectInputStream(fileInputStream);
    Lista pobranaLista = (Lista) objectInputStream.readObject();
    objectInputStream.close();
    
    System.out.println("oryginalna lista || pobrana lista");
    for (int i = 0; i < oryginalnaLista.size;){
      System.out.print(oryginalnaLista.pop_front());
      System.out.print(" = ");
      System.out.println(pobranaLista.pop_front());
    }
  }
}
