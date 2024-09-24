package drawing_software.controller.command;

import drawing_software.model.Drawable;
import drawing_software.view.Canvas;

/**
 * Allows to move forward a selected shape on the Z axis. This is achieved by altering the order of the elements
 * in the lis and thus changing the shapes' drawing order.
 * The oldIndex parameter is used to aid the undo() method, so that it is possible to revert to the old position,
 * inside the list, that was previously occupied by the shape.
 */
public class ForwardCommand implements Command, Undoable {
    private Canvas canvas;
    private int oldIndex;
    private Drawable toLast;

    public ForwardCommand(Canvas canvas) {
        this.canvas = canvas;
        this.oldIndex = canvas.getDrawing().getDrawableIndex(canvas.getSelectionGrid().getSelectedShape());
    }

    /**
     * Retrieves the selected shape and then moves it to the back of the list (so to have it drawn last and thus
     * appear in the front of the drawing) after having removed it from its previous position (to avoid duplicates).
     */
    @Override
    public void execute() {
        toLast = canvas.getSelectionGrid().getSelectedShape();
        canvas.getDrawing().removeDrawable(toLast);
        canvas.getDrawing().addDrawable(toLast);
        canvas.repaint();
    }

    @Override
    public void undo() {
        canvas.getDrawing().removeDrawable(toLast);
        canvas.getDrawing().addDrawableAtIndex(toLast, oldIndex);
        canvas.repaint();
    }
}
