package drawing_software.view.menu;

import drawing_software.controller.command.DeleteCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.net.URL;

public class DeleteMenuItem extends MenuItemFactory {

    public DeleteMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    @Override
    public JMenuItem createMenuItem() {
        JMenuItem deleteMenuItem = new JMenuItem("Delete");
        URL url = getClass().getResource("/delete.png");
        deleteMenuItem.setIcon(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(16, 16, Image.SCALE_SMOOTH)));
        deleteMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_DELETE, 0));
        deleteMenuItem.addActionListener(new ActionListener() {
            /**
             * When the menu item is pressed, a new file dialog will show and the file
             * selected by the user will be used to load the drawing.
             *
             * @param e the event to be processed
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                invoker.executeCommand(new DeleteCommand(canvas));
            }
        });
        return deleteMenuItem;
    }
}
