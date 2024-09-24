package drawing_software.controller.command;

import drawing_software.model.Shape;
import drawing_software.view.Canvas;

import java.awt.*;
/**
 * Implements a ConcreteCommand class; in this case, the Command is the Stroke command.
 */
public class StrokeCommand implements Command, Undoable {

    private final Canvas canvas;

    private final Color color;

    private Color previousStrokeColor;

    private Shape modifiedShape;

    public StrokeCommand(Canvas canvas, Color color) {
        this.canvas = canvas;
        this.color = color;
    }

    /**
     * Updates the title of the window. Then, if the user has selected a shape, changes the shape color
     * its color accordingly to the color chosen. If no shape is selected, it changes the
     * canvas stroke color for new shapes.
     */
    @Override
    public void execute() {
        updateTitle(canvas);
        if (canvas.getSelectionGrid() != null) {
            modifiedShape = canvas.getSelectionGrid().getSelectedShape();
            previousStrokeColor = (Color) modifiedShape.getStrokeColor();
            modifiedShape.setStrokeColor(color);
            canvas.repaint();
        } else {
            previousStrokeColor = canvas.getCurrentStrokeColor();
            canvas.setCurrentStrokeColor(color);
        }
    }

    /**
     * Restores the previous stroke color of the canvas or of the shape, based on the data
     * stored by this concrete command.
     */
    @Override
    public void undo() {
        if (modifiedShape == null) {
            canvas.setCurrentStrokeColor(previousStrokeColor);
        } else {
            modifiedShape.setStrokeColor(previousStrokeColor);
        }

        canvas.repaint();
    }
}

