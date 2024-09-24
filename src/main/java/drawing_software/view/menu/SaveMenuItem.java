package drawing_software.view.menu;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.SaveCommand;
import drawing_software.view.Canvas;
import drawing_software.view.FileDialog;
import drawing_software.view.Window;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.io.File;
import java.io.FileNotFoundException;
import java.net.URL;
import java.util.logging.Logger;

public class SaveMenuItem extends MenuItemFactory implements ActionListener {

    private Window window;

    public SaveMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    public SaveMenuItem(Window window, Invoker invoker) {
        super(window.getCanvas(), invoker);
        this.window = window;
    }

    @Override
    public JMenuItem createMenuItem() {
        JMenuItem saveMenuItem = new JMenuItem("Save");
        URL url = getClass().getResource("/save.png");
        saveMenuItem.setIcon(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(16, 16, Image.SCALE_SMOOTH)));
        saveMenuItem.setAccelerator(KeyStroke.getKeyStroke('S', InputEvent.CTRL_DOWN_MASK));
        saveMenuItem.addActionListener(this);
        return saveMenuItem;
    }

    /**
     * When the menu item is pressed, if the user is working on a new drawing,
     * a new file dialog will show and the file selected by the user will be used to save the drawing,
     * otherwise the drawing will be saved on the previous selected file.
     *
     * @param e the event to be processed
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        File selectedFile = window.getCurrentFile();
        if (selectedFile == null) {
            FileDialog fileDialog = new FileDialog();
            try {
                selectedFile = fileDialog.show(canvas, FileDialog.SAVE_DIALOG);

            } catch (FileNotFoundException ex) {
                Logger.getLogger("root").info("No such file selected");
            }
        }
        invoker.executeCommand(new SaveCommand(window, selectedFile));

    }
}
