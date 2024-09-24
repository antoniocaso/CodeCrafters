package drawing_software.view.menu;

import drawing_software.controller.command.GridCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Implements the "Decrease grid size" menu item.
 */
public class DecreaseGridSizeMenuItem extends MenuItemFactory {

    public DecreaseGridSizeMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    /**
     * Allows to create the "Decrease grid size" menu Item.
     *
     * @return the item.
     */
    @Override
    public JMenuItem createMenuItem() {
        JMenuItem decreaseGridSizeMenuItem = new JMenuItem("Decrease grid size");
        decreaseGridSizeMenuItem.addActionListener(new ActionListener() {
            /**
             * By changing the cellSize, the method allows to alter the size of the grid.
             * Since a grid with cellSize 0 will cause the whole interface to break down (since an "infinite" amount
             * of columns and rows will be drawn), it is important to strictly and forcibly FORBID the choice of
             * having a cellSize of 0.
             * @param e the event to be processed
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                int newCellSize = canvas.getGrid().getCellSize();
                if (newCellSize > 10) {
                    newCellSize -= 10;
                    invoker.executeCommand(new GridCommand(canvas, newCellSize));
                }

            }
        });
        return decreaseGridSizeMenuItem;
    }
}