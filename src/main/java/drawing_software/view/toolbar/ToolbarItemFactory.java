package drawing_software.view.toolbar;

import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;

import javax.swing.*;

/**
 * The concrete classes of this class are factory classes of the JButtons
 * placed inside the toolbar.
 */
public abstract class ToolbarItemFactory {

    protected final static int ICON_SIZE = 32;

    protected final Canvas canvas;
    protected final Invoker invoker;

    public ToolbarItemFactory(Canvas canvas, Invoker invoker) {
        this.canvas = canvas;
        this.invoker = invoker;
    }

    public abstract JToggleButton itemCreate();
}
