package controller;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.LineTool;
import drawing_software.model.DrawableLine;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static org.junit.Assert.*;

public class LineToolTest {

    private LineTool lineTool;
    private Canvas canvas;
    private Invoker invoker;

    @Before
    public void setUp() {
        JFrame frame = new JFrame();
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        frame.add(canvas);
        lineTool = new LineTool(canvas, invoker);
    }

    @Test
    public void testMousePressed() {
        Point2D clickPoint = new Point2D.Double(10, 10);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        lineTool.mouseLeftPressed(e);
        DrawableLine line = (DrawableLine) canvas.getDummyDrawable();
        assertEquals(line.getP1(), clickPoint);
    }

    @Test
    public void testMouseDragged() {
        Point2D clickPoint = new Point2D.Double(10, 10);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        lineTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(20, 20);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        lineTool.mouseDragged(e);

        DrawableLine line = (DrawableLine) canvas.getDummyDrawable();
        assertEquals(line.getP2(), clickPoint);
    }

    @Test
    public void testMouseReleased() {
        Point2D clickPoint = new Point2D.Double(20, 20);

        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        lineTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(40, 40);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        lineTool.mouseDragged(e);

        DrawableLine line = (DrawableLine) canvas.getDummyDrawable();

        e = new MouseEvent(canvas, MouseEvent.MOUSE_RELEASED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        lineTool.mouseReleased(e);

        assertNull(canvas.getDummyDrawable());

        assertTrue(canvas.getDrawing().containsDrawable(line));
    }

}