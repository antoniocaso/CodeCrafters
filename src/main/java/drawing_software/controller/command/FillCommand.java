package drawing_software.controller.command;

import drawing_software.model.Shape;
import drawing_software.view.Canvas;

import java.awt.*;

/**
 * Implements a ConcreteCommand class; in this case, the Command is the Fill command.
 */
public class FillCommand implements Command, Undoable {
    private final Canvas canvas;
    private final Color color;

    private Color previousColor;

    private Shape modifiedShape;


    public FillCommand(Canvas canvas, Color color) {
        this.canvas = canvas;
        this.color = color;
    }

    /**
     * Updates the title of the window. Then, if the user has selected a shape, changes the shape color
     * its color accordingly to the color chosen. If no shape is selected, it changes the
     * canvas color for filling new shapes.
     */
    @Override
    public void execute() {
        updateTitle(canvas);

        if (canvas.getSelectionGrid() != null) {
            modifiedShape = canvas.getSelectionGrid().getSelectedShape();
            previousColor = (Color) modifiedShape.getFillColor();
            modifiedShape.setFillColor(color);
            canvas.repaint();
        } else {
            previousColor = canvas.getCurrentFillColor();
            canvas.setCurrentFillColor(color);
        }
    }

    /**
     * Restores the previous fill color of the canvas or of the shape, based on the data
     * stored by this concrete command.
     */
    @Override
    public void undo() {
        if (modifiedShape == null) {
            canvas.setCurrentFillColor(previousColor);
        } else {
            modifiedShape.setFillColor(previousColor);
        }
        canvas.repaint();
    }
}
