package drawing_software.view.menu;

import drawing_software.controller.command.GridCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;

/**
 * Implements the "Show Grid" menu item and its properties.
 */
public class ShowGridMenuItem extends MenuItemFactory {

    public ShowGridMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    /**
     * Allows to create the Show Grid menu Item.
     *
     * @return the item.
     */
    @Override
    public JMenuItem createMenuItem() {
        JCheckBoxMenuItem showGridMenuItem = new JCheckBoxMenuItem("Show Grid");
        showGridMenuItem.setState(false);
        showGridMenuItem.setAccelerator(KeyStroke.getKeyStroke('G', InputEvent.CTRL_DOWN_MASK));

        showGridMenuItem.addActionListener(new ActionListener() {
            /**
             * When the menu item is pressed, the grid will switch from on and off and viceversa. Since a cellSize
             * of 999999999 is very large, the expression "1.1*canvas.getHeight()/cellSize" found in the method draw()
             * will have value "1.1*630/9999999999", which -when speaking in integer terms- is zero, and thus allowing
             * to have actually NO GRID drawn when the item is pressed coming from an "On" state of the grid.
             * @param e the event to be processed
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                int newCellSize = canvas.getGrid().getCellSize();
                if (canvas.getGrid().getCellSize() != 999999999)
                    newCellSize = 999999999;
                else newCellSize = 20;
                invoker.executeCommand(new GridCommand(canvas, newCellSize));
            }
        });
        return showGridMenuItem;
    }
}