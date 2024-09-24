package drawing_software.view.menu;

import drawing_software.Main;
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

public class SaveAsMenuItem extends MenuItemFactory {

    private Window window;

    public SaveAsMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    public SaveAsMenuItem(Window window, Invoker invoker) {
        super(window.getCanvas(), invoker);
        this.window = window;
    }

    @Override
    public JMenuItem createMenuItem() {
        JMenuItem saveAsMenuItem = new JMenuItem("Save as...");
        URL url = getClass().getResource("/saveAs.png");
        saveAsMenuItem.setIcon(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(16, 16, Image.SCALE_SMOOTH)));

        saveAsMenuItem.setAccelerator(KeyStroke.getKeyStroke('S', InputEvent.CTRL_DOWN_MASK | InputEvent.SHIFT_DOWN_MASK));
        saveAsMenuItem.addActionListener(new ActionListener() {
            /**
             * When the menu item is pressed, a new file dialog will show and the file
             * selected by the user will be used to save the drawing.
             * If the selected file already exists, the user will be prompted with
             * a dialog asking to confirm overwriting the file.
             *
             * @param e the event to be processed
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                FileDialog fileDialog = new FileDialog();
                File selectedFile;

                try {
                    selectedFile = fileDialog.show(canvas, FileDialog.SAVE_DIALOG);
                    if (selectedFile.exists()) {
                        String message = "Are you sure you want to overwrite " + selectedFile.getName() + " ? ";

                        int confirmed = JOptionPane.showConfirmDialog(null, message, Main.appTitle, JOptionPane.YES_NO_OPTION);

                        if (confirmed == JOptionPane.YES_OPTION) {
                            invoker.executeCommand(new SaveCommand(window, selectedFile));
                        }
                    }else{
                        invoker.executeCommand(new SaveCommand(window, selectedFile));
                    }
                } catch (FileNotFoundException ex) {
                    Logger.getLogger("root").info("No such file selected");
                }


            }
        });
        return saveAsMenuItem;
    }
}
