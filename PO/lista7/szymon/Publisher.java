import javax.swing.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class Publisher extends Book {

    private int budget; // jaki budżet
    private String name; // jaka jest nazwa wydawnictwa
    private String upcomming; //najnowsza premiera
    // deklaracja konstruktora
    public Publisher(JFrame frame, String title, int volume, String author, int budget, String name, String upcomming) {
        super(frame, title, volume, author);
        this.budget = budget;
        this.name = name;
        this.upcomming = upcomming;

        // dodanie 'interfejsu' graficznego
        createUI(frame);

    }

    // funkcja budująca 'interfejs' graficzny
    public void createUI(JFrame frame){
        // tworzę panel dla całego wydawcy
        JPanel publisherPanel = new JPanel();
        // dodanie tytułu do 'panelu'
        publisherPanel.setBorder(BorderFactory.createTitledBorder("Class Publisher"));


        // deklaracja etykiet
        JLabel titleLabel = new JLabel("Title");
        JLabel volumeLabel = new JLabel("Volume");
        JLabel authorLabel = new JLabel("Author");

        JLabel budgetLabel = new JLabel("Budget");
        JLabel nameLabel = new JLabel("Name");
        JLabel upcommingLabel = new JLabel("Upcomming");

        // deklaracja pól tekstowych
        JTextField titleInput = new JTextField(this.title);
        JTextField volumeInput = new JTextField(String.valueOf(this.volume));
        JTextField authorInput = new JTextField(this.author);

        JTextField budgetInput = new JTextField(String.valueOf(this.budget));
        JTextField nameInput = new JTextField(this.name);
        JTextField upcommingInput = new JTextField(this.upcomming);

        // deklaracja przycisków
        JButton updateButton = new JButton("Update");
        JButton cancelButton = new JButton("Close");


        // dodanie utworzonych elementów do naszego 'panelu'
        publisherPanel.add(titleLabel);
        publisherPanel.add(titleInput);

        publisherPanel.add(volumeLabel);
        publisherPanel.add(volumeInput);

        publisherPanel.add(authorLabel);
        publisherPanel.add(authorInput);


        publisherPanel.add(budgetLabel);
        publisherPanel.add(budgetInput);


        publisherPanel.add(nameLabel);
        publisherPanel.add(nameInput);

        publisherPanel.add(upcommingLabel);
        publisherPanel.add(upcommingInput);

        publisherPanel.add(updateButton);
        publisherPanel.add(cancelButton);

        // podłączenie słuchaczy do przycisków zapisu i wyłączenia programu
        updateButton.addActionListener((e) -> {
            this.title = titleInput.getText();
            this.volume = Integer.parseInt(volumeInput.getText());
            this.author = authorInput.getText();
            this.budget = Integer.parseInt(budgetInput.getText());
            this.name = nameInput.getText();
            this.upcomming = nameInput.getText();
            saveDataToFile("publisher.ser");
        });

        cancelButton.addActionListener((e) -> {
            frame.dispose();
        });

        frame.getContentPane().add(publisherPanel);

    }

    // funkcja służąca do utworzenia podstawowej wersji obiektu lub pobrania wersji z pliku
    public static Publisher createDefaultPublisher(String filename,
                                                 JFrame frame,
                                                 String defaultTitle,
                                                 int defaultVolume,
                                                 String defaultAuthor,
                                                   int budget, String name, String upcomming)
    {
        File file = new File(filename);
        // jak plik istnieje
        if (file.exists()) {
            try {
                FileInputStream fileIn = new FileInputStream(filename);
                ObjectInputStream in = new ObjectInputStream(fileIn);

                Publisher loadedPublisher = (Publisher) in.readObject();
                // tworzymy 'interfejs' dla pobranego obiektu
                loadedPublisher.createUI(frame);
                in.close();
                fileIn.close();
                // zwracamy obiekt z 'interfejsem'
                return loadedPublisher;
            } catch (IOException i) {
                // błąd zapisu
                i.printStackTrace();
            } catch (ClassNotFoundException c) {
                // brak klasy
                System.out.println("Book class not found");
                c.printStackTrace();
            }
        } // zwrócenie obiektu z podstawowymi wartościami, jeśli plik z obiektem nie istniał
        return new Publisher(frame,
                defaultTitle,
                defaultVolume,
                defaultAuthor,
                budget, name, upcomming);

    }

    // funkcja służąca do tekstowej reprezentacji obiektu
    @Override
    public void MyToString(){
        System.out.println(this.name + " is the main publisher of" + this.author + ". Upcomming book is: "
                + this.upcomming + " with the budget of: " + this.budget);
    }

}
