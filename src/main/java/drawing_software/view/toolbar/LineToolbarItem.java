package drawing_software.view.toolbar;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.LineTool;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.*;
import java.net.URL;

public class LineToolbarItem extends ToolbarItemFactory {

    public LineToolbarItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    /**
     * @return
     */
    @Override
    public JToggleButton itemCreate() {
        URL url = getClass().getResource("/line.png");
        JToggleButton lineButton = new JToggleButton(new ImageIcon(new ImageIcon(url).getImage().getScaledInstance(ICON_SIZE, ICON_SIZE, Image.SCALE_SMOOTH)));
        lineButton.addActionListener(actionEvent -> canvas.setCurrentTool(new LineTool(canvas, invoker)));
        return lineButton;
    }
}
