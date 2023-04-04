/* Rafał Leja
 * lista 6 zadanie 1, Serializable
 */

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class App {
  public static void main(String[] args) throws Exception {
    Lista<Integer> oryginalnaLista = new Lista<Integer>(); 
    //tworzenie listy
    oryginalnaLista.add(2);
    oryginalnaLista.add(0);
    oryginalnaLista.add(2);
    oryginalnaLista.add(3);

    // Strumień wyjściowy
    FileOutputStream fileOutputStream
      = new FileOutputStream("bufor.txt");
    ObjectOutputStream objectOutputStream
      = new ObjectOutputStream(fileOutputStream);
    objectOutputStream.writeObject(oryginalnaLista);
    objectOutputStream.flush();
    objectOutputStream.close();

    // strumień wejściowy
    FileInputStream fileInputStream
      = new FileInputStream("bufor.txt");
    ObjectInputStream objectInputStream
      = new ObjectInputStream(fileInputStream);
    // pobieranie listy z pliku
    Lista pobranaLista = (Lista) objectInputStream.readObject();
    objectInputStream.close();
    
    // porównywanie wyników
    System.out.println("oryginalna lista || pobrana lista");
    for (int i = 0; i < oryginalnaLista.size;){
      System.out.print(oryginalnaLista.pop_front());
      System.out.print(" = ");
      System.out.println(pobranaLista.pop_front());
    }
  }
}
