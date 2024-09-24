package drawing_software.controller.command;

import drawing_software.model.Shape;
import drawing_software.view.Canvas;

import java.awt.geom.Point2D;

/**
 * Memorize the modified shape and the previous location, modified in Selection tool.
 */
public class MoveCommand implements Command, Undoable {

    private final Canvas canvas;
    private final Point2D oldShapeLocation;

    private final Shape modifiedShape;

    public MoveCommand(Canvas canvas, Shape selectedShape, Point2D oldShapeLocation) {
        this.canvas = canvas;
        this.modifiedShape = selectedShape;
        this.oldShapeLocation = oldShapeLocation;
    }

    @Override
    public void execute() {
        updateTitle(canvas);
    }

    /**
     * With the data saved while executing the command, the undo function restores
     * the previous position of the figure.
     */
    @Override
    public void undo() {
        if (modifiedShape != null) {
            modifiedShape.setLocation(oldShapeLocation);
            canvas.clearSelectedDrawable();
            canvas.repaint();
        }
    }
}
