package drawing_software.view.menu;

import drawing_software.Main;
import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.LoadCommand;
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

public class LoadMenuItem extends MenuItemFactory {

    private Window window;

    public LoadMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    public LoadMenuItem(Window window, Invoker invoker) {
        super(window.getCanvas(), invoker);
        this.window = window;
    }

    @Override
    public JMenuItem createMenuItem() {
        JMenuItem loadMenuItem = new JMenuItem("Open...");
        URL url = getClass().getResource("/open.png");
        loadMenuItem.setIcon(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(16, 16, Image.SCALE_SMOOTH)));
        loadMenuItem.setAccelerator(KeyStroke.getKeyStroke('O', InputEvent.CTRL_DOWN_MASK));
        loadMenuItem.addActionListener(new ActionListener() {
            /**
             * When the menu item is pressed, a new file dialog will show and the file
             * selected by the user will be used to load the drawing.
             *
             * @param e the event to be processed
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                FileDialog fileDialog = new FileDialog();
                File selectedFile = null;

                try {
                    selectedFile = fileDialog.show(canvas, FileDialog.OPEN_DIALOG);
                } catch (FileNotFoundException ex) {
                    Logger.getLogger("root").info("No such file selected");
                }

                if (window.isModified()) {
                    String title;
                    if (window.getCurrentFile() == null) {
                        title = "untitled";
                    } else {
                        title = window.getCurrentFile().getName();
                    }
                    String message = "Do you want to save changes to " + title + " ? ";

                    int confirmed = JOptionPane.showConfirmDialog(null,
                            message, Main.appTitle,
                            JOptionPane.YES_NO_CANCEL_OPTION);

                    if (confirmed == JOptionPane.YES_OPTION)
                        new SaveMenuItem(window, window.getInvoker()).actionPerformed(null);
                }

                invoker.executeCommand(new LoadCommand(window, selectedFile));
            }
        });
        return loadMenuItem;
    }
}
