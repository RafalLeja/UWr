import java.io.File;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.NetworkInterface;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
class Pojazd extends JComponent implements Serializable{
  public int liczbaPasazerow;
  public String marka;
  public int rokProdukcji;

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

  public void Edycja(String fileName) {
    JFrame frame = new JFrame("Edycja pojazdu");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    Container kontener = frame.getContentPane();
    GridLayout layout = new GridLayout(4, 2);
    kontener.setLayout(layout);

    JLabel liczbaPasazerowLabel = new JLabel("Liczba pasażerów");
    kontener.add(liczbaPasazerowLabel);
    JTextField liczbaPasazerow = new JTextField(Integer.toString(this.liczbaPasazerow), 10);
    kontener.add(liczbaPasazerow);

    JLabel markaLabel = new JLabel("Marka");
    kontener.add(markaLabel);
    JTextField marka = new JTextField(this.marka, 40);
    kontener.add(marka);

    JLabel rokProdukcjiLabel = new JLabel("Rok produkcji");
    kontener.add(rokProdukcjiLabel);
    JTextField rokProdukcji = new JTextField(Integer.toString(this.rokProdukcji), 4);
    kontener.add(rokProdukcji);

    JButton b = new JButton("Zapisz");
      b.addActionListener((evt) -> {
        this.liczbaPasazerow = Integer.parseInt(liczbaPasazerow.getText().trim());
        this.marka = marka.getText();
        this.rokProdukcji = Integer.parseInt(rokProdukcji.getText().trim());
    
        //File plik = new File(fileName);
        try {
          FileOutputStream fileOutputStream
            = new FileOutputStream(fileName);
          ObjectOutputStream objectOutputStream
            = new ObjectOutputStream(fileOutputStream);
  
          objectOutputStream.writeObject(this);
          objectOutputStream.flush();
          objectOutputStream.close();
        } catch (Exception e) {
          throw new Error("błąd otwarcia pliku" + fileName, e);
        }
      });
    kontener.add(b);

    frame.pack();
    frame.setVisible(true);
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

  public void Edycja(String fileName) {
    JFrame frame = new JFrame("Edycja pojazdu");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    Container kontener = frame.getContentPane();
    GridLayout layout = new GridLayout(4, 2);
    kontener.setLayout(layout);

    JLabel liczbaPasazerowLabel = new JLabel("Liczba pasażerów");
    kontener.add(liczbaPasazerowLabel);
    JTextField liczbaPasazerow = new JTextField(Integer.toString(this.liczbaPasazerow), 10);
    kontener.add(liczbaPasazerow);

    JLabel markaLabel = new JLabel("Marka");
    kontener.add(markaLabel);
    JTextField marka = new JTextField(this.marka, 40);
    kontener.add(marka);

    JLabel rokProdukcjiLabel = new JLabel("Rok produkcji");
    kontener.add(rokProdukcjiLabel);
    JTextField rokProdukcji = new JTextField(Integer.toString(this.rokProdukcji), 4);
    kontener.add(rokProdukcji);

    JLabel mocLabel = new JLabel("Moc");
    kontener.add(mocLabel);
    JTextField moc = new JTextField(Integer.toString(this.moc), 4);
    kontener.add(moc);

    JLabel modelLabel = new JLabel("Model");
    kontener.add(modelLabel);
    JTextField model = new JTextField(this.model, 4);
    kontener.add(model);

    JLabel silnikLabel = new JLabel("Silnik");
    kontener.add(silnikLabel);
    JTextField silnik = new JTextField(Float.toString(this.silnik), 4);
    kontener.add(silnik);

    JButton b = new JButton("Zapisz");
      b.addActionListener((evt) -> {
        this.liczbaPasazerow = Integer.parseInt(liczbaPasazerow.getText().trim());
        this.marka = marka.getText();
        this.rokProdukcji = Integer.parseInt(rokProdukcji.getText().trim());
        this.moc = Integer.parseInt(moc.getText().trim());
        this.model = model.getText().trim();
        this.silnik = Float.parseFloat(silnik.getText().trim());
    
        //File plik = new File(fileName);
        try {
          FileOutputStream fileOutputStream
            = new FileOutputStream(fileName);
          ObjectOutputStream objectOutputStream
            = new ObjectOutputStream(fileOutputStream);
  
          objectOutputStream.writeObject(this);
          objectOutputStream.flush();
          objectOutputStream.close();
        } catch (Exception e) {
          throw new Error("błąd otwarcia pliku" + fileName, e);
        }
      });
    kontener.add(b);

    frame.pack();
    frame.setVisible(true);
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

  public void Edycja(String fileName) {
    JFrame frame = new JFrame("Edycja pojazdu");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    Container kontener = frame.getContentPane();
    GridLayout layout = new GridLayout(4, 2);
    kontener.setLayout(layout);

    JLabel liczbaPasazerowLabel = new JLabel("Liczba pasażerów");
    kontener.add(liczbaPasazerowLabel);
    JTextField liczbaPasazerow = new JTextField(Integer.toString(this.liczbaPasazerow), 10);
    kontener.add(liczbaPasazerow);

    JLabel markaLabel = new JLabel("Marka");
    kontener.add(markaLabel);
    JTextField marka = new JTextField(this.marka, 40);
    kontener.add(marka);

    JLabel rokProdukcjiLabel = new JLabel("Rok produkcji");
    kontener.add(rokProdukcjiLabel);
    JTextField rokProdukcji = new JTextField(Integer.toString(this.rokProdukcji), 4);
    kontener.add(rokProdukcji);

    JLabel liniaLabel = new JLabel("Linia");
    kontener.add(liniaLabel);
    JTextField linia = new JTextField(Integer.toString(this.linia), 4);
    kontener.add(linia);

    JLabel kierunekLabel = new JLabel("Kierunek");
    kontener.add(kierunekLabel);
    JTextField kierunek = new JTextField(this.kierunek, 4);
    kontener.add(kierunek);

    JLabel niskopodlogowyLabel = new JLabel("Niskopodłogowy?");
    kontener.add(niskopodlogowyLabel);
    JCheckBox niskopodlogowy = new JCheckBox("Niskopodłogowy", this.niskopodlogowy);
    kontener.add(niskopodlogowy);

    JButton b = new JButton("Zapisz");
      b.addActionListener((evt) -> {
        this.liczbaPasazerow = Integer.parseInt(liczbaPasazerow.getText().trim());
        this.marka = marka.getText();
        this.rokProdukcji = Integer.parseInt(rokProdukcji.getText().trim());
        this.linia = Integer.parseInt(linia.getText().trim());
        this.kierunek = kierunek.getText().trim();
        this.niskopodlogowy = niskopodlogowy.isSelected();
    
        //File plik = new File(fileName);
        try {
          FileOutputStream fileOutputStream
            = new FileOutputStream(fileName);
          ObjectOutputStream objectOutputStream
            = new ObjectOutputStream(fileOutputStream);
  
          objectOutputStream.writeObject(this);
          objectOutputStream.flush();
          objectOutputStream.close();
        } catch (Exception e) {
          throw new Error("błąd otwarcia pliku" + fileName, e);
        }
      });
    kontener.add(b);

    frame.pack();
    frame.setVisible(true);
  }
  
  @Override
  public String toString() {
    return super.toString() + ", numer lini: " + linia + 
      ", kierunek: " + kierunek + ", niskopodłogowy: " + niskopodlogowy;
  }
}