package controller;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.EllipseTool;
import drawing_software.model.DrawableEllipse;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static org.junit.Assert.*;

public class EllipseToolTest {

    private Canvas canvas;
    private Invoker invoker;
    private EllipseTool ellipseTool;

    @Before
    public void setUp() throws Exception {
        JFrame frame = new JFrame();
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        frame.add(canvas);
        ellipseTool = new EllipseTool(canvas, invoker);
    }


    @Test
    public void testMouseDraggedTopLeft() {

        DrawableEllipse testEllipse = new DrawableEllipse(0,0);
        testEllipse.setFrame(0,0,50,50);

        Point2D clickPoint = new Point2D.Double(0, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(50, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 2, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseDragged(e);
        DrawableEllipse ellipse = (DrawableEllipse) canvas.getDummyDrawable();
        assertEquals(ellipse.getX(), testEllipse.getX(), 0);
        assertEquals(ellipse.getY(), testEllipse.getY(), 0);
        assertEquals(ellipse.getWidth(), testEllipse.getWidth(), 0);
        assertEquals(ellipse.getHeight(), testEllipse.getHeight(), 0);
    }

    @Test
    public void testMouseDraggedTopRight() {

        DrawableEllipse drawableEllipse = new DrawableEllipse(0,0);
        drawableEllipse.setFrame(0,0,50,50);

        Point2D clickPoint = new Point2D.Double(50, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(0, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 2, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseDragged(e);
        DrawableEllipse ellipse = (DrawableEllipse) canvas.getDummyDrawable();
        assertEquals(ellipse.getX(), drawableEllipse.getX(), 0);
        assertEquals(ellipse.getY(), drawableEllipse.getY(), 0);
        assertEquals(ellipse.getWidth(), drawableEllipse.getWidth(), 0);
        assertEquals(ellipse.getHeight(), drawableEllipse.getHeight(), 0);
    }

    @Test
    public void testMouseDraggedBottomLeft(){
        DrawableEllipse testEllipse = new DrawableEllipse(0,0);
        testEllipse.setFrame(0,0,50,50);

        Point2D clickPoint = new Point2D.Double(0, 50);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(50, 0);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 2, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseDragged(e);
        DrawableEllipse ellipse = (DrawableEllipse) canvas.getDummyDrawable();
        assertEquals(ellipse.getX(), testEllipse.getX(), 0);
        assertEquals(ellipse.getY(), testEllipse.getY(), 0);
        assertEquals(ellipse.getWidth(), testEllipse.getWidth(), 0);
        assertEquals(ellipse.getHeight(), testEllipse.getHeight(), 0);
    }

    @Test
    public void testMouseDraggedBottomRight(){
        DrawableEllipse testEllipse = new DrawableEllipse(0,0);
        testEllipse.setFrame(0,0,50,50);

        Point2D clickPoint = new Point2D.Double(50, 50);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(0, 0);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 2, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseDragged(e);
        DrawableEllipse ellipse = (DrawableEllipse) canvas.getDummyDrawable();
        assertEquals(ellipse.getX(), testEllipse.getX(), 0);
        assertEquals(ellipse.getY(), testEllipse.getY(), 0);
        assertEquals(ellipse.getWidth(), testEllipse.getWidth(), 0);
        assertEquals(ellipse.getHeight(), testEllipse.getHeight(), 0);
    }

    @Test
    public void testMouseReleased(){
        canvas.clearDummyDrawable();
        Point2D clickPoint = new Point2D.Double(0, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(50, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 2, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseDragged(e);

        DrawableEllipse ellipse = (DrawableEllipse) canvas.getDummyDrawable();

        e = new MouseEvent(canvas, MouseEvent.MOUSE_RELEASED, 3, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseReleased(e);

        DrawableEllipse dummy = (DrawableEllipse) canvas.getDummyDrawable();
        assertNull(dummy);

        boolean inserted = canvas.getDrawing().containsDrawable(ellipse);
        assertTrue(inserted);
    }


    @Test
    public void testMouseReleasedHorizontalBoundary(){
        Point2D clickPoint = new Point2D.Double(0, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(50, 0);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 2, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseDragged(e);
        DrawableEllipse ellipse = (DrawableEllipse) canvas.getDummyDrawable();

        e = new MouseEvent(canvas, MouseEvent.MOUSE_RELEASED, 3, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseReleased(e);

        boolean inserted = canvas.getDrawing().containsDrawable(ellipse);
        assertFalse(inserted);

    }

    @Test
    public void testMouseReleasedVerticalBoundary(){
        Point2D clickPoint = new Point2D.Double(0, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(0, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 2, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseDragged(e);
        DrawableEllipse ellipse = (DrawableEllipse) canvas.getDummyDrawable();

        e = new MouseEvent(canvas, MouseEvent.MOUSE_RELEASED, 3, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        ellipseTool.mouseReleased(e);

        boolean inserted = canvas.getDrawing().containsDrawable(ellipse);
        assertFalse(inserted);

    }
}