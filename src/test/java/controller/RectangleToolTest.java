package controller;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.RectangleTool;
import drawing_software.model.DrawableRectangle;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static org.junit.Assert.*;

public class RectangleToolTest {

    private Canvas canvas;
    private Invoker invoker;
    private RectangleTool rectangleTool;

    @Before
    public void setUp() throws Exception {
        JFrame frame = new JFrame();
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        frame.add(canvas);
        rectangleTool = new RectangleTool(canvas, invoker);
    }


    @Test
    public void testMouseDraggedTopLeft() {

        DrawableRectangle testRectangle = new DrawableRectangle(0,0);
        testRectangle.setRect(0,0,50,50);

        Point2D clickPoint = new Point2D.Double(0, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(50, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseDragged(e);
        DrawableRectangle rectangle = (DrawableRectangle) canvas.getDummyDrawable();
        assertEquals(rectangle.getX(), testRectangle.getX(), 0);
        assertEquals(rectangle.getY(), testRectangle.getY(), 0);
        assertEquals(rectangle.getWidth(), testRectangle.getWidth(), 0);
        assertEquals(rectangle.getHeight(), testRectangle.getHeight(), 0);
    }

    @Test
    public void testMouseDraggedTopRight() {

        DrawableRectangle testRectangle = new DrawableRectangle(0,0);
        testRectangle.setRect(0,0,50,50);

        Point2D clickPoint = new Point2D.Double(50, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(0, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseDragged(e);
        DrawableRectangle rectangle = (DrawableRectangle) canvas.getDummyDrawable();
        assertEquals(rectangle.getX(), testRectangle.getX(), 0);
        assertEquals(rectangle.getY(), testRectangle.getY(), 0);
        assertEquals(rectangle.getWidth(), testRectangle.getWidth(), 0);
        assertEquals(rectangle.getHeight(), testRectangle.getHeight(), 0);
    }

    @Test
    public void testMouseDraggedBottomLeft(){
        DrawableRectangle testRectangle = new DrawableRectangle(0,0);
        testRectangle.setRect(0,0,50,50);

        Point2D clickPoint = new Point2D.Double(0, 50);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(50, 0);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseDragged(e);
        DrawableRectangle rectangle = (DrawableRectangle) canvas.getDummyDrawable();
        assertEquals(rectangle.getX(), testRectangle.getX(), 0);
        assertEquals(rectangle.getY(), testRectangle.getY(), 0);
        assertEquals(rectangle.getWidth(), testRectangle.getWidth(), 0);
        assertEquals(rectangle.getHeight(), testRectangle.getHeight(), 0);
    }

    @Test
    public void testMouseDraggedBottomRight(){
        DrawableRectangle testRectangle = new DrawableRectangle(0,0);
        testRectangle.setRect(0,0,50,50);

        Point2D clickPoint = new Point2D.Double(50, 50);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(0, 0);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseDragged(e);
        DrawableRectangle rectangle = (DrawableRectangle) canvas.getDummyDrawable();
        assertEquals(rectangle.getX(), testRectangle.getX(), 0);
        assertEquals(rectangle.getY(), testRectangle.getY(), 0);
        assertEquals(rectangle.getWidth(), testRectangle.getWidth(), 0);
        assertEquals(rectangle.getHeight(), testRectangle.getHeight(), 0);
    }

    @Test
    public void testMouseReleased(){
        canvas.clearDummyDrawable();
        Point2D clickPoint = new Point2D.Double(0, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(50, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseDragged(e);

        DrawableRectangle rectangle = (DrawableRectangle) canvas.getDummyDrawable();

        e = new MouseEvent(canvas, MouseEvent.MOUSE_RELEASED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseReleased(e);

        DrawableRectangle dummy = (DrawableRectangle) canvas.getDummyDrawable();
        assertNull(dummy);

        boolean inserted = canvas.getDrawing().containsDrawable(rectangle);
        assertTrue(inserted);
    }


    @Test
    public void testMouseReleasedHorizontalBoundary(){
        Point2D clickPoint = new Point2D.Double(0, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(50, 0);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseDragged(e);
        DrawableRectangle rectangle = (DrawableRectangle) canvas.getDummyDrawable();

        e = new MouseEvent(canvas, MouseEvent.MOUSE_RELEASED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseReleased(e);

        boolean inserted = canvas.getDrawing().containsDrawable(rectangle);
        assertFalse(inserted);

    }

    @Test
    public void testMouseReleasedVerticalBoundary(){
        Point2D clickPoint = new Point2D.Double(0, 0);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseLeftPressed(e);

        clickPoint = new Point2D.Double(0, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseDragged(e);
        DrawableRectangle rectangle = (DrawableRectangle) canvas.getDummyDrawable();

        e = new MouseEvent(canvas, MouseEvent.MOUSE_RELEASED, System.currentTimeMillis(), InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        rectangleTool.mouseReleased(e);

        boolean inserted = canvas.getDrawing().containsDrawable(rectangle);
        assertFalse(inserted);

    }
}