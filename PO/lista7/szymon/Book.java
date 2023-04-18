// pobranie odpowiednich bibliotek, do obsługi 'interfejsów' graficznych
import javax.swing.*;
import java.io.Serializable;
import java.io.*;

public class Book extends JComponent implements Serializable {
    public String title; //tytuł
    public int volume; //ilość stron
    public String author; //autor
    // deklaracja konstruktora
    public Book(JFrame frame, String title, int volume, String author){
        this.title = title;
        this.volume = volume;
        this.author = author;
        // dodanie 'interfejsu' graficznego do obiektu
        createUI(frame);

    }

    // funkcja budująca 'interfejs' graficzny
    public void createUI(JFrame frame){
        // wszystko będzie w 'panelu'
        JPanel bookPanel = new JPanel();
        // dodanie tytułu do 'panelu'
        bookPanel.setBorder(BorderFactory.createTitledBorder("Class Book"));

        // zrobienie nazwy etykiet, pól które będzie można zmienić w obiektach
        JLabel titleLabel = new JLabel("Title");
        JLabel volumeLabel = new JLabel("Volume");
        JLabel authorLabel = new JLabel("Author");

        //zrobienie pola tekstowe, będzie to 'wejście' do zmian naszych klas
        JTextField titleInput = new JTextField(this.title);
        JTextField volumeInput = new JTextField(String.valueOf(this.volume));
        JTextField authorInput = new JTextField(this.author);

        // zrobienie dwóch przycisków, zapis i zamknięcie programu
        JButton updateButton = new JButton("Save");
        JButton cancelButton = new JButton("Close");

        // dodanie do naszego 'panelu' pól tekstowych i etykiet
        bookPanel.add(titleLabel);
        bookPanel.add(titleInput);
        bookPanel.add(volumeLabel);
        bookPanel.add(volumeInput);
        bookPanel.add(authorLabel);
        bookPanel.add(authorInput);
        bookPanel.add(updateButton);
        bookPanel.add(cancelButton);



        // podłączenie 'słuchacza' do utworzonych wyżej przycisków
        updateButton.addActionListener((e) -> {
            this.title = titleInput.getText();
            this.volume = Integer.parseInt(volumeInput.getText());
            this.author = authorInput.getText();
            saveDataToFile("book.ser");
        });

        cancelButton.addActionListener((e) -> {
            frame.dispose();
        });

        // ustalenie rozmiaru zawartości naszej 'ramki'
        frame.pack();
        frame.setVisible(true);

        // wrzucamy nasz panel do głównej 'ramki'
        frame.getContentPane().add(bookPanel);
    }


    // funkcja służąca do utworzenia podstawowej wersji obiektu lub pobrania wersji z pliku
    public static Book createDefaultBook
            (String filename, JFrame frame, String defaultTitle, int defaultVolume, String defaultAuthor) {
        File file = new File(filename);
        // jak plik istnieje
        if (file.exists()) {
            try {
                FileInputStream fileIn = new FileInputStream(filename);
                ObjectInputStream in = new ObjectInputStream(fileIn);

                Book loadedBook = (Book) in.readObject();
                // tworzymy 'interfejs' dla pobranego obiektu
                loadedBook.createUI(frame);
                in.close();
                fileIn.close();
                // zwracamy obiekt z 'interfejsem'
                return loadedBook;
                // błąd zapisu
            } catch (IOException i) {
                i.printStackTrace();
                // brak klasy
            } catch (ClassNotFoundException c) {
                System.out.println("Book class not found");
                c.printStackTrace();
            }
        }
        // zwrócenie obiektu z podstawowymi wartościami, jeśli plik z obiektem nie istniał
        return new Book(frame, defaultTitle, defaultVolume, defaultAuthor);
    }

    // wygenerowane przez GPT-4
    // zapis danych do plików
    // funkcja używana jako działanie przycisu 'Save'
    public void saveDataToFile(String filename) {
        try {
            // utworzenie obiektów, umożliwiających zapis do plików
            FileOutputStream fileOut = new FileOutputStream(filename);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            // zapisanie do pliku
            out.writeObject(this);
            out.close();
            fileOut.close();
            System.out.println("Serialized data is saved in " + filename);
            // błąd zapisu
        } catch (IOException i) {
            i.printStackTrace();
        }
    }

    // funkcja służąca do tekstowej reprezentacji obiektu
    public void MyToString(){
        System.out.println(this.title + " written by: " + this.author + " pages: " + this.volume);
    }

}
