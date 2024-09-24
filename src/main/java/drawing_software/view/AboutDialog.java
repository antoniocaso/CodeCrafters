package drawing_software.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;

/**
 * The about dialog with the dev names
 */
public class AboutDialog extends JDialog implements ActionListener{

    private JTextArea name = new JTextArea("                Designed with <3 by: Miriam Amendola, Valerio Battipaglia, Antonio Caso, Giuseppe Dell'Orto ");

    public AboutDialog() {
        setTitle("About");
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        add(Box.createRigidArea(new Dimension(0, 10)));

        URL url = Window.class.getResource("/icon1024.png");
        ImageIcon icon = new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(96, 96, Image.SCALE_SMOOTH));
        JLabel imageIcon = new JLabel(icon);
        imageIcon.setAlignmentX(Component.CENTER_ALIGNMENT);
        add(imageIcon);

        JLabel appTitle = new JLabel("Drawing Software");
        appTitle.setFont (appTitle.getFont ().deriveFont (Font.BOLD,18.0f));
        appTitle.setAlignmentX(Component.CENTER_ALIGNMENT);
        add(Box.createVerticalStrut(15));
        add(appTitle);
        add(Box.createVerticalStrut(10));

        JLabel description = new JLabel("<html><p align=\"center\">This software allows to create simple drawings <br>by combination of adjustable shapes.</p></html>", SwingConstants.CENTER);
        description.setBounds(100,100,100,100);
        description.setFont (description.getFont().deriveFont (14.0f));
        description.setAlignmentX(Component.CENTER_ALIGNMENT);
        add(Box.createVerticalStrut(10));
        add(description);
        add(Box.createVerticalStrut(30));

        name.setAlignmentX(Component.CENTER_ALIGNMENT);
        name.setOpaque(false);
        add(name, BorderLayout.CENTER);
        Timer t = new Timer(100, this); // set a timer
        t.start();

        setModalityType(ModalityType.APPLICATION_MODAL);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setSize(320, 320);
        setLocationRelativeTo(null);
        setResizable(false);
    }

    public void actionPerformed(ActionEvent e) {
        String oldText = name.getText();
        String newText= oldText.substring(1)+ oldText.substring(0,1);
        name.setText(newText);
    }
}