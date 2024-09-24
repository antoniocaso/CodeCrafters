package drawing_software.view.toolbar;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.EllipseTool;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.*;
import java.net.URL;

public class EllipseToolbarItem extends ToolbarItemFactory {

    public EllipseToolbarItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    /**
     * @return
     */
    @Override
    public JToggleButton itemCreate() {
        URL url = getClass().getResource("/ellipse.png");
        JToggleButton cursorButton = new JToggleButton(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(ICON_SIZE, ICON_SIZE, Image.SCALE_SMOOTH)));
        cursorButton.addActionListener(actionEvent -> canvas.setCurrentTool(new EllipseTool(canvas, invoker)));
        return cursorButton;
    }
}
