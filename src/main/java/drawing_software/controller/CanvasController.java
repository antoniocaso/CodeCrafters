package drawing_software.controller;

import drawing_software.view.Canvas;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.geom.Point2D;
/**
 * Implements the business logic for the Canvas view.
 */
public class CanvasController implements MouseListener, MouseMotionListener {
    private Canvas canvas;

    /**
     * Adds the two Mouse Listeners to the canvas.
     *
     * @param canvas
     */
    public CanvasController(Canvas canvas) {
        this.canvas = canvas;
        canvas.addMouseListener(this);
        canvas.addMouseMotionListener(this);
    }

    private MouseEvent correctMouseEvent(MouseEvent mouseEvent) {
        Point2D point = canvas.getInverse().transform(mouseEvent.getPoint(), new Point2D.Double());
        return new MouseEvent(mouseEvent.getComponent(), mouseEvent.getID(), mouseEvent.getWhen(), mouseEvent.getModifiersEx(), (int) point.getX(), (int) point.getY(), mouseEvent.getClickCount(), mouseEvent.isPopupTrigger(), mouseEvent.getButton());
    }

    /**
     * Calls the correct mouse Clicked method, according to the button pressed.
     * Passes the correct mouse event, transformed for the zoom.
     *
     * @param e the event to be processed
     */
    @Override
    public void mouseClicked(MouseEvent e) {
        e = correctMouseEvent(e);
        if (e.getButton() == MouseEvent.BUTTON1) {
            canvas.getCurrentTool().mouseLeftClicked(e);
        } else if (e.getButton() == MouseEvent.BUTTON3) {
            canvas.getCurrentTool().mouseRightClicked(e);
        }
    }

    /**
     * Calls the correct mouse Pressed method, according to the button pressed.
     * Passes the correct mouse event, transformed for the zoom.
     *
     * @param e the event to be processed
     */
    @Override
    public void mousePressed(MouseEvent e) {
        e = correctMouseEvent(e);
        if (e.getButton() == MouseEvent.BUTTON1)
            canvas.getCurrentTool().mouseLeftPressed(e);
        else if (e.getButton() == MouseEvent.BUTTON3)
            canvas.getCurrentTool().mouseRightPressed(e);
    }

    /**
     * Calls the mouse Released method.
     * Passes the correct mouse event, transformed for the zoom.
     *
     * @param e the event to be processed
     */
    @Override
    public void mouseReleased(MouseEvent e) {
        e = correctMouseEvent(e);
        canvas.getCurrentTool().mouseReleased(e);
    }

    /**
     * Calls the mouse Dragged method.
     * Passes the correct mouse event, transformed for the zoom.
     *
     * @param e the event to be processed
     */
    @Override
    public void mouseDragged(MouseEvent e) {
        e = correctMouseEvent(e);
        canvas.getCurrentTool().mouseDragged(e);
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    }
}
