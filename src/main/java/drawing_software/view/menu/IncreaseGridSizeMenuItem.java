package drawing_software.view.menu;

import drawing_software.controller.command.GridCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Implements the "Increase grid size" menu item.
 */
public class IncreaseGridSizeMenuItem extends MenuItemFactory {

    public IncreaseGridSizeMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    /**
     * Allows to create the "Increase grid size" menu Item.
     *
     * @return the item.
     */
    @Override
    public JMenuItem createMenuItem() {
        JMenuItem IncreaseGridSizeMenuItem = new JMenuItem("Increase grid size");
        IncreaseGridSizeMenuItem.addActionListener(new ActionListener() {
            /**
             * By changing the cellSize, the method allows to alter the size of the grid.
             * @param e the event to be processed
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                int newCellSize = canvas.getGrid().getCellSize();
                if (newCellSize <= 100) {
                    newCellSize += 10;
                    invoker.executeCommand(new GridCommand(canvas, newCellSize));
                }

            }
        });
        return IncreaseGridSizeMenuItem;
    }
}