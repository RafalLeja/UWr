import java.io.Serializable;

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
}

class Samochod extends Pojazd {
  private float silnik;

  public Samochod(int liczbaPasazerow, String marka, int rokProdukcji, float silnik) {
    super(liczbaPasazerow, marka, rokProdukcji);
    this.silnik = silnik;
  }

  
  @Override
  public String toString() {
    return super.toString() + ", pojemność Silnika: " + silnik;
  }
}

class Tramwaj extends Pojazd {
  private int linia;

  public Tramwaj(int liczbaPasazerow, String marka, int rokProdukcji, int linia) {
    super(liczbaPasazerow, marka, rokProdukcji);
    this.linia = linia;
  }

  
  @Override
  public String toString() {
    return super.toString() + ", numer lini: " + linia;
  }
}