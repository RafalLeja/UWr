/*
 * Rafał Leja
 * PO lista 7
 * >java App NazwaPliku NazwaKlasy
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.ObjectInputStream;

public class App {
  public static void main(String[] args) throws Exception {
    if (args.length < 2) {
      throw new Error("Brak argumetów\n" +
      "Poprawne użycie to >java App nazwaPliku nazwaKlasy", null);
    }
    String fileName = args[0];
    String className = args[1];

    File plik = new File(fileName);
    if (plik.exists()) {
      FileInputStream fileInputStream
        = new FileInputStream(fileName);
      ObjectInputStream objectInputStream
        = new ObjectInputStream(fileInputStream);

      Pojazd objekt = (Pojazd) objectInputStream.readObject();
      objectInputStream.close();

      objekt.Edycja(fileName);
    } else {
      Pojazd obiekt;
      if (className.toLowerCase().trim().equals("pojazd")) {
        
        obiekt = 
        new Pojazd(0, "marka", 0);
        
      } else if (className.toLowerCase().trim().equals("tramwaj")) {
        
        obiekt = new Tramwaj(0, "marka", 
        0, 0, "kierunek", false);     
        
      } else {

        obiekt = new Samochod(0, "marka",
            0, 0, 0, "model");
      }

      obiekt.Edycja(fileName);
    }
  }
}
