import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class Magazine extends Book {

    private int price; //cena
    private int series; // który numer
    private int quota; // jaki nakład

    // deklaracja konstruktora
    public Magazine(JFrame frame, String title, int volume, String author, int price, int series, int quota) {
        super(frame, title, volume, author);
        this.price = price;
        this.series = series;
        this.quota = quota;

        createUI(frame);

    }

    // funkcja służąca do utworzenia 'interfejsu' graficznego
    public void createUI(JFrame frame){
        // tworzę panel na obiekt Magazine
        JPanel magazinePanel = new JPanel();
        // dodanie tytułu do 'panelu'
        magazinePanel.setBorder(BorderFactory.createTitledBorder("Class Magazine"));


        // deklaracja etykiet
        JLabel titleLabel = new JLabel("Title");
        JLabel volumeLabel = new JLabel("Volume");
        JLabel authorLabel = new JLabel("Author");
        JLabel quotaLabel = new JLabel("Quota");
        JLabel seriesLabel = new JLabel("Series");
        JLabel priceLabel = new JLabel("Price");


        // deklaracja pól tekstowych
        JTextField titleInput = new JTextField(this.title);
        JTextField volumeInput = new JTextField(String.valueOf(this.volume));
        JTextField authorInput = new JTextField(this.author);

        JTextField quotaInput = new JTextField(String.valueOf(this.quota));
        JTextField seriesInput = new JTextField(String.valueOf(this.series));
        JTextField priceInput = new JTextField(String.valueOf(this.price));

        // utworzenie przycisków
        JButton updateButton = new JButton("Update");
        JButton cancelButton = new JButton("Close");


        // dodanie pól tekstowych, etykiet i przycisków do 'interfejsu'
        magazinePanel.add(titleLabel);
        magazinePanel.add(titleInput);

        magazinePanel.add(quotaLabel);
        magazinePanel.add(quotaInput);

        magazinePanel.add(seriesLabel);
        magazinePanel.add(seriesInput);

        magazinePanel.add(priceLabel);
        magazinePanel.add(priceInput);

        magazinePanel.add(volumeLabel);
        magazinePanel.add(volumeInput);

        magazinePanel.add(authorLabel);
        magazinePanel.add(authorInput);

        magazinePanel.add(updateButton);
        magazinePanel.add(cancelButton);

        // podłączenie 'słuchacza' do przycisów, umożliwi to zapis lub zamknięcie
        updateButton.addActionListener((e) -> {
            this.title = titleInput.getText();
            this.volume = Integer.parseInt(volumeInput.getText());
            this.author = authorInput.getText();
            this.price = Integer.parseInt(priceInput.getText());
            this.series = Integer.parseInt(seriesInput.getText());
            this.quota = Integer.parseInt(quotaInput.getText());
            // funkcja do zapisywania, pochodząca z rodzica
            saveDataToFile("magazine.ser");
        });

        cancelButton.addActionListener((e) -> {
            frame.dispose();
        });

        frame.getContentPane().add(magazinePanel);


    }

    // funkcja służąca do utworzenia podstawowej wersji obiektu lub pobrania wersji z pliku
    public static Magazine createDefaultMagazine(String filename,
                                                 JFrame frame,
                                                 String defaultTitle,
                                                 int defaultVolume,
                                                 String defaultAuthor,
                                                 int price, int series, int quota
                                                 )
    {
        // jak plik istnieje
        File file = new File(filename);
        if (file.exists()) {
            try {
                FileInputStream fileIn = new FileInputStream(filename);
                ObjectInputStream in = new ObjectInputStream(fileIn);

                Magazine loadedMagazine = (Magazine) in.readObject();
                // tworzymy 'interfejs' dla pobranego obiektu
                loadedMagazine.createUI(frame);
                in.close();
                fileIn.close();
                // zwracamy obiekt z 'interfejsem'
                return loadedMagazine;
            } catch (IOException i) {
                // błąd zapisu
                i.printStackTrace();
            } catch (ClassNotFoundException c) {
                // brak klasy
                System.out.println("Book class not found");
                c.printStackTrace();
            }
        }
        return new Magazine(frame,
                defaultTitle,
        defaultVolume,
        defaultAuthor,
        price, series, quota);
    }

    // funkcja służąca do tekstowej reprezentacji obiektu
    @Override
    public void MyToString(){
        System.out.println(this.title + "written by" + this.author + "pages: "
                + this.volume + "quota: " + this.quota);
    }


}
