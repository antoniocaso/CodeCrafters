package drawing_software.controller.tool;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.PasteCommand;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static java.lang.Thread.sleep;

/**
 * Defines the behaviour of the canvas when the Paste Tool is selected, and further implements the State pattern.
 * When this state is selected, the user can either click and thus paste a previously cut or copied shape, or
 * click and paste while moving the mouse around the canvas.
 * <p>
 * The invoker, as a parameter, is necessary for the Tool to request the execution of the corresponding
 * command to the Canvas (alias the Receiver).
 */
public class PasteTool extends JPanel implements Tool {
    private final Canvas canvas;
    private final Invoker invoker;


    public PasteTool(Canvas canvas, Invoker invoker) {
        this.canvas = canvas;
        this.invoker = invoker;
    }

    /**
     * After the PasteTool is selected, this method allows to actually paste the shape when the Left Click
     * happens in a certain point of the canvas.
     *
     * @param mouseEvent is the event from which the point of click is extracted.
     */
    @Override
    public void mouseLeftPressed(MouseEvent mouseEvent) {
        Point2D p = mouseEvent.getPoint();
        invoker.executeCommand(new PasteCommand(canvas, p));
    }

    /**
     * After the PasteTool is selected, this method allows to actually paste the shape when the mouse is moved
     * around the canvas, together with the use of the left click.
     *
     * @param mouseEvent is the event from which the point of click is extracted.
     */
    public void mouseDragged(MouseEvent mouseEvent) {
        Point2D p = mouseEvent.getPoint();
        invoker.executeCommand(new PasteCommand(canvas, p));
        try {
            sleep(100);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}

