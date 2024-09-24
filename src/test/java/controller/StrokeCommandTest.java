package controller;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.StrokeCommand;
import drawing_software.model.DrawableRectangle;
import drawing_software.model.SelectionGrid;
import drawing_software.view.Canvas;
import drawing_software.view.colors.ColorButton;
import drawing_software.view.colors.StrokePanel;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.*;

import static org.junit.Assert.assertEquals;

public class StrokeCommandTest {
    private Canvas canvas;

    private ColorButton strokeButton;
    private DrawableRectangle rectangle;

    @Before
    public void setUp() throws Exception {
        JFrame frame = new JFrame();
        Invoker invoker = new Invoker();
        canvas = new Canvas(invoker);
        frame.add(canvas);
        StrokePanel panel = new StrokePanel(canvas, invoker);
        strokeButton = panel.getButton();
        rectangle = new DrawableRectangle(0, 0);
        rectangle.setSize(new Dimension(30, 30));
        canvas.getDrawing().addDrawable(rectangle);
        canvas.setSelectionGrid(new SelectionGrid(rectangle));
    }

    @Test
    public void testExecute() {
        StrokeCommand command = new StrokeCommand(canvas, Color.blue);
        command.execute();
        assertEquals(rectangle.getStrokeColor(), Color.blue);
    }

    @Test
    public void testUndoShape() {
        rectangle = new DrawableRectangle(20, 20);
        rectangle.setSize(new Dimension(30, 30));
        canvas.getDrawing().addDrawable(rectangle);
        canvas.setSelectionGrid(new SelectionGrid(rectangle));
        StrokeCommand command = new StrokeCommand(canvas, Color.red);
        command.execute();
        command.undo();
        assertEquals(rectangle.getStrokeColor(), Color.black);
    }

    @Test
    public void testUndoColor() {
        canvas.clearSelectedDrawable();
        StrokeCommand command = new StrokeCommand(canvas, Color.blue);
        command.execute();
        command.undo();
        assertEquals(Color.black, canvas.getCurrentStrokeColor());
    }


}