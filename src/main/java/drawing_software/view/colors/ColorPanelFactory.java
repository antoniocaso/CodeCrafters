package drawing_software.view.colors;

import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;

import javax.swing.*;

public abstract class ColorPanelFactory extends JPanel {

    protected final Invoker invoker;

    protected final Canvas canvas;
    protected ColorButton button;

    protected ColorPanelFactory(Canvas canvas, Invoker invoker) {
        this.canvas = canvas;
        this.invoker = invoker;
    }

    public ColorButton getButton() {
        return button;
    }
}
