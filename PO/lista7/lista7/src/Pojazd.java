import java.io.Serializable;
import java.net.NetworkInterface;
import java.awt.*;
import javax.swing.*;
class Pojazd implements Serializable{
  private int liczbaPasazerow;
  private String marka;
  private int rokProdukcji;

  public Pojazd(int liczbaPasazerow, String marka, int rokProdukcji) {
    this.liczbaPasazerow = liczbaPasazerow;
    this.marka = marka;
    this.rokProdukcji = rokProdukcji;
  }

  @Override
  public String toString() {
    return "marka: " + marka + ", rok produkcji: " + rokProdukcji +
    ", liczba pasażerów: " + liczbaPasazerow;
  }

  public void Edycja() {
    JFrame frame = new JFrame("Edycja pojazdu");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    Container kontener = frame.getContentPane();
    GridLayout layout = new GridLayout(4, 2);
    kontener.setLayout(layout);

    JLabel liczbaPasazerowLabel = new JLabel("Liczba pasażerów");
    kontener.add(liczbaPasazerowLabel);
    JTextField liczbaPasazerow = new JTextField(Integer.toString(this.liczbaPasazerow), 10);
    kontener.add(liczbaPasazerow);

    JLabel markaLabel = new JLabel("Rok produkcji");
    kontener.add(markaLabel);
    JTextField marka = new JTextField(this.marka, 40);
    kontener.add(marka);

    JLabel rokProdukcjiLabel = new JLabel("Rok produkcji");
    kontener.add(rokProdukcjiLabel);
    JTextField rokProdukcji = new JTextField(Integer.toString(this.rokProdukcji), 4);
    kontener.add(rokProdukcji);
  }
}

class Samochod extends Pojazd {
  private int moc;
  private String model;
  private float silnik;

  public Samochod(int liczbaPasazerow, String marka, int rokProdukcji,
      int moc, float silnik, String model) {
    super(liczbaPasazerow, marka, rokProdukcji);
    this.moc = moc;
    this.silnik = silnik;
    this.model = model;
  }

  
  @Override
  public String toString() {
    return super.toString() + ", model: " + model + 
      ", pojemność Silnika: " + silnik + ", moc: " + moc;
  }
}

class Tramwaj extends Pojazd {
  private int linia;
  private String kierunek;
  private boolean niskopodlogowy;

  public Tramwaj(int liczbaPasazerow, String marka, int rokProdukcji,
      int linia, String kierunek, boolean niskopodlogowy) {
    super(liczbaPasazerow, marka, rokProdukcji);
    this.linia = linia;
    this.kierunek = kierunek;
    this.niskopodlogowy = niskopodlogowy;
  }

  
  @Override
  public String toString() {
    return super.toString() + ", numer lini: " + linia + 
      ", kierunek: " + kierunek + ", niskopodłogowy: " + niskopodlogowy;
  }
}