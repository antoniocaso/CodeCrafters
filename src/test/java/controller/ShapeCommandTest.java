package controller;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.ShapeCommand;
import drawing_software.model.Drawable;
import drawing_software.model.DrawableEllipse;
import drawing_software.model.DrawableLine;
import drawing_software.model.DrawableRectangle;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.geom.Point2D;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class ShapeCommandTest {

    private Drawable shape;
    private Canvas canvas;

    private Invoker invoker;

    @Before
    public void setUp() {
        JFrame frame = new JFrame();
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        frame.add(canvas);
    }

    @Test
    public void testExecuteWithLine() {
        Point2D p1 = new Point2D.Double(10, 10);
        Point2D p2 = new Point2D.Double(20, 20);
        shape = new DrawableLine(p1, p2);
        new ShapeCommand(canvas, shape).execute();
        assertTrue(canvas.getDrawing().containsDrawable(shape));
    }

    @Test
    public void testExecuteWithRectangle() {
        shape = new DrawableRectangle(10, 10);
        new ShapeCommand(canvas, shape).execute();
        assertTrue(canvas.getDrawing().containsDrawable(shape));
    }

    @Test
    public void testExecuteWithEllipse() {
        shape = new DrawableEllipse(10, 10);
        new ShapeCommand(canvas, shape).execute();
        assertTrue(canvas.getDrawing().containsDrawable(shape));
    }

    @Test
    public void testUndo() {
        shape = new DrawableEllipse(10, 10);
        ShapeCommand shapeCommand = new ShapeCommand(canvas, shape);
        shapeCommand.execute();
        shapeCommand.undo();
        assertFalse(canvas.getDrawing().containsDrawable(shape));
    }


}