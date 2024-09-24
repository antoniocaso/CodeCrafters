package drawing_software.controller.tool;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.ShapeCommand;
import drawing_software.model.DrawableLine;
import drawing_software.view.Canvas;

import java.awt.event.MouseEvent;
/**
 * Defines the behaviour of the canvas when the Line Tool is selected.
 * When this state is selected, the user can draw a line on the canvas by dragging the mouse.
 */
public class LineTool implements Tool {

    private DrawableLine line;

    private final Canvas canvas;

    private final Invoker invoker;

    public LineTool(Canvas canvas, Invoker invoker) {
        this.canvas = canvas;
        this.invoker = invoker;
        canvas.clearSelectedDrawable();
        canvas.repaint();
    }

    /**
     * Defines how the canvas reacts when holding the mouse button down.
     * It creates the line according to the mouse coordinates and the current color.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseLeftPressed(MouseEvent mouseEvent) {
        line = new DrawableLine(canvas.getCurrentStrokeColor(), mouseEvent.getPoint(), mouseEvent.getPoint());
        canvas.setDummyDrawable(line);
    }
    /**
     * Defines how the canvas reacts to dragging the mouse.
     * The line is rendered according to the direction of the dragging.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseDragged(MouseEvent mouseEvent) {
        if (line == null) return;

        line.setLine(line.getP1(), mouseEvent.getPoint());
        canvas.repaint();
    }

    /**
     * Defines how the canvas reacts when releasing the mouse button.
     * Prevents creating a new line when it has zero length.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseReleased(MouseEvent mouseEvent) {
        if (line == null) return;
        if (!line.getP1().equals(line.getP2())) {
            invoker.executeCommand(new ShapeCommand(canvas, line));
        }
        canvas.clearDummyDrawable();
        line = null;
    }

}
