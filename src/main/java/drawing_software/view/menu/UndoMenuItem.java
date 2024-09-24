package drawing_software.view.menu;

import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.net.URL;

public class UndoMenuItem extends MenuItemFactory {

    public UndoMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    @Override
    public JMenuItem createMenuItem() {
        JMenuItem undoMenuItem = new JMenuItem("Undo");
        URL url = getClass().getResource("/undo.png");
        undoMenuItem.setIcon(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(16, 16, Image.SCALE_SMOOTH)));
        undoMenuItem.setAccelerator(KeyStroke.getKeyStroke('Z', InputEvent.CTRL_DOWN_MASK));

        undoMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                invoker.undoLastCommand();
            }
        });
        return undoMenuItem;
    }
}
