package drawing_software.controller.tool;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.ShapeCommand;
import drawing_software.model.DrawableEllipse;
import drawing_software.view.Canvas;

import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static java.lang.Math.abs;
import static java.lang.Math.min;

/**
 * Defines the behaviour of the canvas when the Ellipse Tool is selected.
 * When this state is selected, the user can draw an ellipse on the canvas by dragging the mouse.
 */
public class EllipseTool implements Tool {

    private DrawableEllipse ellipse;

    private final Canvas canvas;

    private final Invoker invoker;

    private Point2D startingPoint;

    public EllipseTool(Canvas canvas, Invoker invoker) {
        this.canvas = canvas;
        this.invoker = invoker;
        canvas.clearSelectedDrawable();
        canvas.repaint();
    }

    /**
     * Defines how the canvas reacts when holding the mouse button down.
     * It creates the Ellipse according to the mouse coordinates and the current colors.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseLeftPressed(MouseEvent mouseEvent) {
        this.startingPoint = mouseEvent.getPoint();
        ellipse = new DrawableEllipse(canvas.getCurrentFillColor(), canvas.getCurrentStrokeColor(), mouseEvent.getX(), mouseEvent.getY());
    }

    /**
     * Defines how the canvas reacts to dragging the mouse.
     * The ellipse is rendered according to the direction of the dragging.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseDragged(MouseEvent mouseEvent) {
        if (ellipse == null) return;
        double x = min(startingPoint.getX(), mouseEvent.getX());
        double y = min(startingPoint.getY(), mouseEvent.getY());
        double width = abs(startingPoint.getX() - mouseEvent.getX());
        double height = abs(startingPoint.getY() - mouseEvent.getY());

        ellipse.setFrame(x, y, width, height);
        canvas.setDummyDrawable(ellipse);
        canvas.repaint();
    }

    /**
     * Defines how the canvas reacts when releasing the mouse button.
     * Prevents creating a new ellipse when the shape has a dimension equal to zero.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseReleased(MouseEvent mouseEvent) {
        if (ellipse == null) return;
        if (ellipse.getWidth() > 0 && ellipse.getHeight() > 0) {
            invoker.executeCommand(new ShapeCommand(canvas, ellipse));
        }

        canvas.clearDummyDrawable();
        ellipse = null;
    }

}
