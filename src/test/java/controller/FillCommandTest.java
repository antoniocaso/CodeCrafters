package controller;

import drawing_software.controller.command.Command;
import drawing_software.controller.command.FillCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.model.DrawableRectangle;
import drawing_software.model.SelectionGrid;
import drawing_software.view.Canvas;
import drawing_software.view.colors.ColorButton;
import drawing_software.view.colors.FillPanel;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.*;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

public class FillCommandTest {

    private Canvas canvas;

    private ColorButton fillButton;
    private DrawableRectangle rectangle;

    @Before
    public void setUp() throws Exception {
        JFrame frame = new JFrame();
        Invoker invoker = new Invoker();
        canvas = new Canvas(invoker);
        frame.add(canvas);
        FillPanel panel = (FillPanel) new FillPanel(canvas, invoker);
        fillButton = panel.getButton();

    }

    @Test
    public void testExecute() {
        rectangle = new DrawableRectangle(0, 0);
        rectangle.setSize(new Dimension(30, 30));
        canvas.getDrawing().addDrawable(rectangle);
        canvas.setSelectionGrid(new SelectionGrid(rectangle));
        Command command = new FillCommand(canvas, Color.red);
        command.execute();
        assertEquals(rectangle.getFillColor(), Color.red);
    }

    @Test
    public void testExecuteCanvasColor() {
        canvas.clearSelectedDrawable();
        Command command = new FillCommand(canvas, Color.blue);
        command.execute();
        assertEquals(canvas.getCurrentFillColor(), Color.blue);
    }

    @Test
    public void testUndoShape() {
        rectangle = new DrawableRectangle(20, 20);
        rectangle.setSize(new Dimension(30, 30));
        canvas.getDrawing().addDrawable(rectangle);
        canvas.setSelectionGrid(new SelectionGrid(rectangle));
        FillCommand command = new FillCommand(canvas, Color.red);
        command.execute();
        command.undo();
        assertNull(rectangle.getFillColor());
    }

    @Test
    public void testUndoColor() {
        canvas.clearSelectedDrawable();
        FillCommand command = new FillCommand(canvas, Color.blue);
        command.execute();
        command.undo();
        assertNull(canvas.getCurrentFillColor());
    }
}