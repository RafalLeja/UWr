// Szymon Mazurek
// 338191
// lista 7
// Zadanie 1
//28.03.2023 wersja 1.0
//Projekt składa się z 4 plików
// Main.java - testy
// Book.java - rodzic wszystkich klas
// Magazine.java - dziecko Book, reprezentuje obiekty typu czasopismo
// Publisher.java - dziecko Book, reprezentuje obiekty typu wydawca
//KOMPILACJA
// - wszystko za pomocą kompilatora javac 11.0.18
// - udajemy się do katologu z plikami z zadania
// - wpisujeme polecenie 'javac nazwa_pliku.java' <- trzeba to wykonać dla każdego pliku
// - żeby uruchomić plik należy wpisać java Main "nazwa_klasy_z_małej_litery.ser" "Nazwa_klasy_z_dużej_litery"
// - w razie problemów, po Main należy dopisać java -cp . Main




// pobranie odpowiednich bibliotek, do obsługi 'interfejsów' graficznych
import javax.swing.*;
import java.awt.*;
import java.util.Objects;

public class Main {
    public static void main(String[] args) {

        // główna aplikacja
        // robimy obiekt JFrame, które posłuży nam jako 'ramka' do wyświetlania obiektów
        JFrame frame = new JFrame("Book Management");
        // umożliwienie zamykania
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // ustalenie rozmiaru wyświetlanej ramki
        frame.setSize(new Dimension(400, 400));

        // obsługa argumentów wywołania programu
        // uwaga plik z zapisaną klasą jest w formacie: nazwa_klasy_małą_literą.ser
        if (args.length > 2){
            // przypadek, gdy jest za dużo argumentów
            System.out.println("Too many arguments!\n");
        } else if (args.length == 2) {
            // przypadek, gdy wszystko jest dobrze
            String filename = args[0];
            String className = args[1];
            // robię podstawowe wersje obiektów
            if (Objects.equals(className, "Magazine")){
                Magazine magazine = Magazine.createDefaultMagazine(filename, frame, "Default Title", 0, "No one", 0, 0, 0);
            } else if (Objects.equals(className, "Publisher")) {
                Publisher publisher = Publisher.createDefaultPublisher(filename, frame, "Default Title", 0, "No one", 0, "No", "Something");
            }else {
                Book book = Book.createDefaultBook(filename, frame, "Default Title", 0, "No one");
            }
        } else {
            // przypadek, gdy argumentów jest za mało
            System.out.println("Too few arguments!\n");
        }



        // utworzenie siatki, na której będziemy wyświetlać nasze obiekty
        GridLayout gridLayout = new GridLayout(2, 1);
        frame.getContentPane().setLayout(gridLayout);

        // alternatywna wersja, wszystko wyświetlane na raz
//        Book book = Book.createDefaultBook("book.ser", frame, "Default Title", 0, "No one");
//        Magazine magazine = Magazine.createDefaultMagazine("magazine.ser", frame, "Default Title", 0, "No one", 0, 0, 0);
//        Publisher publisher = Publisher.createDefaultPublisher("publisher.ser", frame, "Default Title", 0, "No one", 0, "No", "Something");

        // dostosowanie 'ramki' do rozmiaru zawartości
        frame.pack();
        // optymalizacja wielkości 'ramki' i jej wyświetlenie
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}