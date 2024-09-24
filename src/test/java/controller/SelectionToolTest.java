package controller;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.SelectionTool;
import drawing_software.model.DrawableLine;
import drawing_software.model.DrawableRectangle;
import drawing_software.model.SelectionGrid;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.*;
import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

public class SelectionToolTest {
    private Canvas canvas;
    private SelectionTool selectionTool;
    private Invoker invoker;

    @Before
    public void setUp() throws Exception {
        JFrame frame = new JFrame();
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        frame.add(canvas);
        selectionTool = new SelectionTool(canvas, invoker);

    }
    @Test
    public void testMouseClickOnFigure() {
        Point2D start = new Point(0, 0);
        Point2D end = new Point(0, 20);
        DrawableLine lineToTest = new DrawableLine(start, end);       //create line to test
        canvas.getDrawing().addDrawable(lineToTest);
        Point2D clickPoint = new Point2D.Double(0, 10);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);
        DrawableLine s = (DrawableLine) canvas.getSelectionGrid().getSelectedShape();
        assertEquals(s, lineToTest);
    }

    @Test
    public void testPressingMouseOutOfShape() {
        DrawableRectangle testRectangle = new DrawableRectangle(0, 0);
        testRectangle.setSize(new Dimension(50, 50));
        canvas.getDrawing().addDrawable(testRectangle);
        Point2D clickPoint = new Point2D.Double(60, 60);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);
        SelectionGrid s = canvas.getSelectionGrid();
        assertNull(s);
    }

    /**
     * The main logic of the class is handled by private variables of the class. Consequently,
     * this feature will be tested using black-box testing, and the test will be a focused on simulating user
     * interaction with the drawing.
     */
    @Test
    public void testMovingShape() {
        DrawableRectangle testRectangle = new DrawableRectangle(0, 0);
        testRectangle.setSize(new Dimension(50, 50));
        canvas.getDrawing().addDrawable(testRectangle);
        // Pressing inside the shape
        Point2D clickPoint = new Point2D.Double(20, 20);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);
        // Dragging the shape (20,0) to the right
        Point2D draggingPoint = new Point2D.Double(40, 20);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) draggingPoint.getX(), (int) draggingPoint.getY(), 1, false);
        selectionTool.mouseDragged(e);
        Point2D rectLocation = new Point2D.Double(testRectangle.getBounds().getLocation().getX(), testRectangle.getBounds().getLocation().getY());
        assertEquals(new Point2D.Double(20, 0), rectLocation);
    }

    @Test
    public void testStretchingShape() {
        DrawableRectangle testRectangle = new DrawableRectangle(0, 0);
        testRectangle.setSize(new Dimension(50, 50));
        canvas.getDrawing().addDrawable(testRectangle);
        // Pressing inside the shape
        Point2D clickPoint = new Point2D.Double(20, 20);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);

        // Pressing in the vertex
        clickPoint = new Point2D.Double(50, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);
        // Dragging the shape (20,20) to the right
        Point2D draggingPoint = new Point2D.Double(60, 60);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) draggingPoint.getX(), (int) draggingPoint.getY(), 1, false);
        selectionTool.mouseDragged(e);
        Dimension rectSize = testRectangle.getBounds().getSize();
        assertEquals(new Dimension(60, 60), rectSize);
    }

    @Test
    public void testResizingShape() {
        canvas.setFixedResize(true);
        DrawableRectangle testRectangle = new DrawableRectangle(0, 0);
        testRectangle.setSize(new Dimension(30, 50));
        canvas.getDrawing().addDrawable(testRectangle);
        // Pressing inside the shape
        Point2D clickPoint = new Point2D.Double(20, 20);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);


        // Pressing in the vertex
        clickPoint = new Point2D.Double(30, 50);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);
        // Dragging the shape (20,0) to the right
        Point2D draggingPoint = new Point2D.Double(60, 60);
        e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) draggingPoint.getX(), (int) draggingPoint.getY(), 1, false);
        selectionTool.mouseDragged(e);

        Dimension rectSize = testRectangle.getBounds().getSize();
        assertEquals(new Dimension(36, 60), rectSize);
    }

}