import java.awt.*;

import javax.swing.*;

public class App {
  public static void main(String[] args) throws Exception {

    JFrame frame = new JFrame("Edycja książki");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    Container kontener = frame.getContentPane();
    GridLayout layout = new GridLayout(4, 2);
    kontener.setLayout(layout);

    JLabel autor_etykieta = new JLabel("Autor");
    kontener.add(autor_etykieta);
    JTextField autor = new JTextField(this.autor, 40);
    kontener.add(autor);
  }
}
