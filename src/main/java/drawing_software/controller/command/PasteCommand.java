package drawing_software.controller.command;

import drawing_software.model.Drawable;
import drawing_software.model.Shape;
import drawing_software.view.Canvas;

import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.geom.Point2D;
import java.io.IOException;
import java.util.logging.Logger;

/**
 * Defines the Paste Command, which will ask the receiver (canvas) to paste the clipboard's Drawable at a point
 * on the canvas defined by left click of the mouse (received as a parameter from the tool class).
 */
public class PasteCommand implements Command, Undoable {
    private Canvas canvas;
    private Point2D point;

    private Shape pastedShape;

    public PasteCommand(Canvas canvas, Point2D point) {
        this.canvas = canvas;
        this.point = point;
    }

    /**
     * Allows to ask for the execution of the Paste Command: that means that the Drawable stored in the clipboard
     * is obtained through the use of a new DataFlavor defined ON the Drawable class, then a copy of the Drawable is
     * made so that the original Drawable is not moved from its position, and the copy is then asked to be drawn by the
     * Canvas in a certain location received as a parameter.
     */
    @Override
    public void execute() {
        updateTitle(canvas);
        try {
            DataFlavor dataFlavor = new DataFlavor(DataFlavor.javaJVMLocalObjectMimeType + ";class=\"" + Drawable.class.getName() + "\"");
            Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
            Transferable tr = clipboard.getContents(this);
            Shape copiedShape = (Shape) tr.getTransferData(dataFlavor);
            pastedShape = copiedShape.clone();
            canvas.getDrawing().addDrawable(pastedShape);
            pastedShape.setLocation(point);
            canvas.clearSelectedDrawable();
            canvas.repaint();

        } catch (ClassNotFoundException | IOException | UnsupportedFlavorException e) {
            Logger.getLogger("root").warning("Clipboard error");
            throw new RuntimeException(e);
        } catch (NullPointerException e) {
            Logger.getLogger("root").warning("Paste command: no selected shape");
        }

    }

    /**
     * Deletes from the drawing the shape created by the command.
     */
    @Override
    public void undo() {
        if (pastedShape != null) {
            canvas.getDrawing().removeDrawable(pastedShape);
            canvas.clearSelectedDrawable();
            canvas.repaint();
        }

    }
}
