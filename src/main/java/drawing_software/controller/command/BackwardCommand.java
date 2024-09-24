package drawing_software.controller.command;

import drawing_software.model.Drawable;
import drawing_software.view.Canvas;

/**
 * Allows to move backwards a selected shape on the Z axis. This is achieved by altering the order of the elements
 * in the lis and thus changing the shapes' drawing order.
 * The oldIndex parameter is used to aid the undo() method, so that it is possible to revert to the old position,
 * inside the list, that was previously occupied by the shape.
 */
public class BackwardCommand implements Command, Undoable {
    private Canvas canvas;
    private int oldIndex;
    private Drawable toFirst;

    public BackwardCommand(Canvas canvas) {
        this.canvas = canvas;
        this.oldIndex = canvas.getDrawing().getDrawableIndex(canvas.getSelectionGrid().getSelectedShape());
    }

    /**
     * Retrieves the selected shape and then moves it to the front of the list (so to have it drawn first and thus
     * appear in the back) after having removed it from its previous position (to avoid duplicates).
     */
    @Override
    public void execute() {
        toFirst = canvas.getSelectionGrid().getSelectedShape();
        canvas.getDrawing().removeDrawable(toFirst);
        canvas.getDrawing().addDrawableFirst(toFirst);
        canvas.repaint();
    }

    @Override
    public void undo() {
        canvas.getDrawing().removeDrawable(toFirst);
        canvas.getDrawing().addDrawableAtIndex(toFirst, oldIndex);
        canvas.repaint();
    }
}
