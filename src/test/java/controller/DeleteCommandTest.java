package controller;

import drawing_software.controller.command.DeleteCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.SelectionTool;
import drawing_software.model.DrawableEllipse;
import drawing_software.model.DrawableLine;
import drawing_software.model.DrawableRectangle;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.*;
import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class DeleteCommandTest {

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
    public void testExecuteWithLine() {
        Point2D p1 = new Point2D.Double(10, 10);
        Point2D p2 = new Point2D.Double(20, 20);
        DrawableLine shape = new DrawableLine(p1, p2);
        canvas.getDrawing().addDrawable(shape);

        Point2D clickPoint = new Point2D.Double(15, 15);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);

        assertTrue(canvas.getDrawing().containsDrawable(shape));

        new DeleteCommand(canvas).execute();

        assertFalse(canvas.getDrawing().containsDrawable(shape));
    }

    @Test
    public void testExecuteWithRectangle() {
        DrawableRectangle shape = new DrawableRectangle(10, 10);
        shape.setSize(new Dimension(10, 10));
        canvas.getDrawing().addDrawable(shape);

        Point2D clickPoint = new Point2D.Double(15, 15);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);

        assertTrue(canvas.getDrawing().containsDrawable(shape));

        new DeleteCommand(canvas).execute();

        assertFalse(canvas.getDrawing().containsDrawable(shape));
    }

    @Test
    public void testExecuteWithEllipse() {
        DrawableEllipse shape = new DrawableEllipse(10, 10);
        shape.setSize(new Dimension(10, 10));
        canvas.getDrawing().addDrawable(shape);

        Point2D clickPoint = new Point2D.Double(15, 15);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);

        assertTrue(canvas.getDrawing().containsDrawable(shape));

        new DeleteCommand(canvas).execute();

        assertFalse(canvas.getDrawing().containsDrawable(shape));
    }

    /**
     * Given a shape added to the drawing, we delete it, when we execute the
     * undo method, the shape must be back inside the drawing.
     */
    @Test
    public void testUndo() {
        DrawableEllipse shape = new DrawableEllipse(10, 10);
        shape.setSize(new Dimension(10, 10));
        canvas.getDrawing().addDrawable(shape);

        Point2D clickPoint = new Point2D.Double(15, 15);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);

        DeleteCommand deleteCommand = new DeleteCommand(canvas);
        deleteCommand.execute();

        deleteCommand.undo();

        assertTrue(canvas.getDrawing().containsDrawable(shape));
    }
}