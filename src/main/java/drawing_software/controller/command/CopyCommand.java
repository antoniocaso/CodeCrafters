package drawing_software.controller.command;

import drawing_software.model.Drawable;
import drawing_software.view.Canvas;

import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.Transferable;
import java.util.logging.Logger;

/**
 * Implements a ConcreteCommand class; in this case, the Command is the Copy command.
 */
public class CopyCommand implements Command, ClipboardOwner {

    private final Canvas canvas;

    /**
     * @param canvas is the reference to the receiver which will perform the required action.
     */

    public CopyCommand(Canvas canvas) {
        this.canvas = canvas;
    }

    /**
     * First,it takes the selected figure to copy, and then it creates a clipboard where save the figure.
     * The operation is completed by adding the shapes in the canvas and repaint the canvas in order to can paste easily .
     */
    @Override
    public void execute() {
        try {
            Drawable selectedShape = canvas.getSelectionGrid().getSelectedShape();
            Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
            TrasferableWrapper tr = new TrasferableWrapper(selectedShape);
            clipboard.setContents(tr, canvas);
            canvas.firePropertyChange("CLIPBOARD_EMPTY", true, false);
        } catch (NullPointerException e) {
            Logger.getLogger("root").warning("Copy command: no selected shape");
        }

    }

    /**
     * This method is necessary for use a clipboard
     */
    @Override
    public void lostOwnership(Clipboard clipboard, Transferable contents) {
        Logger.getLogger("root").info("ClipboardTest: Lost ownership");
        canvas.firePropertyChange("CLIPBOARD_EMPTY", false, true);
    }
}
