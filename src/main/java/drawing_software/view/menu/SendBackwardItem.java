package drawing_software.view.menu;

import drawing_software.controller.command.BackwardCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;

/**
 * Allows to create the apposite item in the "Edit" menu.
 */
public class SendBackwardItem extends MenuItemFactory {


    public SendBackwardItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    /**
     * Used to create the menu item to be pressed.
     */
    @Override
    public JMenuItem createMenuItem() {
        JMenuItem sendBackwardMenuItem = new JMenuItem("Send Backward");
        URL url = getClass().getResource("/sendBackward.png");
        sendBackwardMenuItem.setIcon(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(16, 16, Image.SCALE_SMOOTH)));
        sendBackwardMenuItem.addActionListener(new ActionListener() {
            /**
             * When the menu item is pressed, the BringForward Command will be called and its actions
             * will be executed.
             *
             * @param e the event to be processed.
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                invoker.executeCommand(new BackwardCommand(canvas));
            }
        });
        return sendBackwardMenuItem;
    }
}