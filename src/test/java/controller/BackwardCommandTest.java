package controller;

import drawing_software.controller.command.BackwardCommand;
import drawing_software.controller.command.Command;
import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.SelectionTool;
import drawing_software.model.DrawableRectangle;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import java.awt.*;
import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static org.junit.Assert.assertEquals;

public class BackwardCommandTest {
    private Canvas canvas;
    private Invoker invoker;
    private SelectionTool selectionTool;
    private Command backWardCommand;

    @Before
    public void setUp() {
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        selectionTool = new SelectionTool(canvas, invoker);
    }
    @Test
    public void testExecuteBackwardCommand(){
        DrawableRectangle rectangleToTest = new DrawableRectangle(0, 20);
        rectangleToTest.setRect(0, 20, 20, 20);
        canvas.getDrawing().addDrawable(rectangleToTest);

        DrawableRectangle rectangleToTest2 = new DrawableRectangle(10, 20);
        rectangleToTest2.setRect(10, 20, 20, 20);
        canvas.getDrawing().addDrawable(rectangleToTest2);

        Point2D clickPoint = new Point2D.Double(15, 25);

        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);
        backWardCommand = new BackwardCommand(canvas);
        backWardCommand.execute();
        MouseEvent e2 = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e2);
        Shape s = (Shape) canvas.getSelectionGrid().getSelectedShape();
        assertEquals(s, rectangleToTest);
    }


}