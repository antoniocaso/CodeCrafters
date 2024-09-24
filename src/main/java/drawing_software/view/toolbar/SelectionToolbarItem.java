package drawing_software.view.toolbar;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.SelectionTool;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.*;
import java.net.URL;

public class SelectionToolbarItem extends ToolbarItemFactory {

    public SelectionToolbarItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    /**
     * @return
     */
    @Override
    public JToggleButton itemCreate() {
        URL url = getClass().getResource("/cursor.png");
        JToggleButton selectionButton = new JToggleButton(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(ICON_SIZE, ICON_SIZE, Image.SCALE_SMOOTH)));
        selectionButton.addActionListener(actionEvent -> {
            canvas.setCurrentTool(new SelectionTool(canvas, invoker));
        });
        return selectionButton;
    }
}
