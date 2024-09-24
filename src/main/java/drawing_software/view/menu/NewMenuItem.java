package drawing_software.view.menu;

import drawing_software.Main;
import drawing_software.controller.command.Invoker;
import drawing_software.model.Drawing;
import drawing_software.view.Canvas;
import drawing_software.view.Window;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.net.URL;

public class NewMenuItem extends MenuItemFactory {

    private Window window;

    public NewMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    public NewMenuItem(Window window, Invoker invoker) {
        super(window.getCanvas(), invoker);
        this.window = window;
    }

    @Override
    public JMenuItem createMenuItem() {
        JMenuItem newMenuItem = new JMenuItem("New");

        newMenuItem.setAccelerator(KeyStroke.getKeyStroke('N', InputEvent.CTRL_DOWN_MASK));

        URL url = getClass().getResource("/new.png");
        newMenuItem.setIcon(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(16, 16, Image.SCALE_SMOOTH)));
        newMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
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
                window.setCurrentFile(null);
                canvas.setDrawing(new Drawing());
                canvas.firePropertyChange("MODIFIED", true, false);
                canvas.repaint();
            }
        });
        return newMenuItem;
    }
}
