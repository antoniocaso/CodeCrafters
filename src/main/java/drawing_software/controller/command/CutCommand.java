package drawing_software.controller.command;

import drawing_software.model.Drawable;
import drawing_software.view.Canvas;

import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.util.logging.Logger;

/**
 * Defines the Cut Command, which will first store the selected Drawable in the clipboard and then will ask the
 * receiver (canvas) to remove it in order to avoid duplicates, being this a CUT command.
 */
public class CutCommand implements Command, Undoable {
    private Canvas canvas;

    private Drawable selectedShape;

    public CutCommand(Canvas canvas) {
        this.canvas = canvas;
    }

    /**
     * Allows to ask for the execution of the Cut Command: the selected Drawable is wrapped in a specific class
     * and then stored in the clipboard. Subsequently, the canvas is asked to REMOVE the Drawable from the drawing.
     */
    @Override
    public void execute() {
        updateTitle(canvas);
        try {
            selectedShape = canvas.getSelectionGrid().getSelectedShape();
            Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
            TrasferableWrapper tr = new TrasferableWrapper(selectedShape);
            canvas.getDrawing().removeDrawable(selectedShape);
            clipboard.setContents(tr, canvas);
            canvas.clearSelectedDrawable();
            canvas.repaint();
        } catch (NullPointerException e) {
            Logger.getLogger("root").warning("Cut command: no selected shape");
        }
    }

    @Override
    public void undo() {
        if (selectedShape != null) {
            canvas.getDrawing().addDrawable(selectedShape);
            canvas.clearSelectedDrawable();
            canvas.repaint();
        }
    }

}