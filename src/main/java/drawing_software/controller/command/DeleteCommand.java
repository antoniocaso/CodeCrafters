package drawing_software.controller.command;

import drawing_software.model.Shape;
import drawing_software.view.Canvas;

import java.util.logging.Logger;
/**
 * Implements the command to be called in order to delete a shape.
 */
public class DeleteCommand implements Command, Undoable {

    private final Canvas canvas;

    private Shape selectedShape;

    /**
     * @param canvas is the reference to the receiver which will perform the required action.
     */
    public DeleteCommand(Canvas canvas) {
        this.canvas = canvas;
    }

    /**
     * Firstly, updates the title with the "*" mark, then removes the selected drawable from the data structure.
     * Clears the selected drawable and calls the repaint method.
     */
    @Override
    public void execute() {
        updateTitle(canvas);
        try {
            selectedShape = (Shape) canvas.getSelectionGrid().getSelectedShape();
            canvas.getDrawing().removeDrawable(selectedShape);
            canvas.clearSelectedDrawable();
            canvas.repaint();
        } catch (NullPointerException e) {
            Logger.getLogger("root").warning("Delete command: no selected shape");
        }
    }

    /**
     * Readds the previously deleted shape to the data structure.
     * Clears the selected drawable and calls the repaint method.
     */
    @Override
    public void undo() {
        if (selectedShape != null) {
            canvas.getDrawing().addDrawable(selectedShape);
            canvas.clearSelectedDrawable();
            canvas.repaint();
        }
    }
}
