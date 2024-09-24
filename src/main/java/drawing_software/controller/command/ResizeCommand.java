package drawing_software.controller.command;

import drawing_software.model.Shape;
import drawing_software.view.Canvas;

import java.awt.*;
import java.awt.geom.Point2D;
/**
 * Implements the command to be called in order to resize a shape.
 */
public class ResizeCommand implements Command, Undoable {

    private final Canvas canvas;
    private final Point2D oldShapeLocation;
    private final Dimension oldShapeSize;

    private final Shape selectedShape;

    public ResizeCommand(Canvas canvas, Shape selectedShape, Point2D oldShapeLocation, Dimension oldShapeSize) {
        this.canvas = canvas;
        this.selectedShape = selectedShape;
        this.oldShapeLocation = oldShapeLocation;
        this.oldShapeSize = oldShapeSize;
    }


    @Override
    public void execute() {
        updateTitle(canvas);
    }

    /**
     * Reverts the resize by changing back the old shape location and the old shape size.
     */
    @Override
    public void undo() {
        if (selectedShape != null) {
            selectedShape.setFrame(oldShapeLocation, oldShapeSize);
            canvas.clearSelectedDrawable();
            canvas.repaint();
        }
    }
}
