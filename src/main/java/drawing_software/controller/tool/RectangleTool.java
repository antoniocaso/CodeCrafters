package drawing_software.controller.tool;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.ShapeCommand;
import drawing_software.model.DrawableRectangle;
import drawing_software.view.Canvas;

import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static java.lang.Math.abs;
import static java.lang.Math.min;
/**
 * Defines the behaviour of the canvas when the Rectangle Tool is selected.
 * When this state is selected, the user can draw a rectangle on the canvas by dragging the mouse.
 */
public class RectangleTool implements Tool {

    private DrawableRectangle rect;

    private final Canvas canvas;

    private final Invoker invoker;

    private Point2D startingPoint;

    public RectangleTool(Canvas canvas, Invoker invoker) {
        this.canvas = canvas;
        this.invoker = invoker;
        canvas.clearSelectedDrawable();
        canvas.repaint();
    }

    /**
     * Defines how the canvas reacts when holding the mouse button down.
     * It creates the Rectangle according to the mouse coordinates and the current colors.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseLeftPressed(MouseEvent mouseEvent) {
        this.rect = new DrawableRectangle(canvas.getCurrentFillColor(), canvas.getCurrentStrokeColor(), mouseEvent.getX(), mouseEvent.getY());
        this.startingPoint = mouseEvent.getPoint();
    }

    /**
     * Defines how the canvas reacts to dragging the mouse.
     * The rectangle is rendered according to the direction of the dragging.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseDragged(MouseEvent mouseEvent) {
        if (rect == null) return;
        double x = min(startingPoint.getX(), mouseEvent.getX());
        double y = min(startingPoint.getY(), mouseEvent.getY());
        double width = abs(startingPoint.getX() - mouseEvent.getX());
        double height = abs(startingPoint.getY() - mouseEvent.getY());

        rect.setRect(x, y, width, height);
        canvas.setDummyDrawable(rect);
        canvas.repaint();
    }

    /**
     * Defines how the canvas reacts when releasing the mouse button.
     * Prevents creating a new rectangle when the shape has a dimension equal to zero.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseReleased(MouseEvent mouseEvent) {
        if (rect == null) return;
        if (rect.getWidth() > 0 && rect.getHeight() > 0) {
            invoker.executeCommand(new ShapeCommand(canvas, rect));
        }
        canvas.clearDummyDrawable();
        rect = null;
    }

    /**
     * @return top left corner Point of the rectangle
     */
    public Point2D getStartingPoint() {
        return startingPoint;
    }
}
