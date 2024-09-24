package controller;

import drawing_software.controller.command.GridCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;

public class GridCommandTest {

    private Canvas canvas;
    private Invoker invoker;
    private GridCommand gc;

    @Before
    public void setUp() {
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        gc = new GridCommand(canvas, 30);
    }

    @Test
    public void testExecute() {
        gc.execute();
        assertNotNull(canvas.getGrid());
        assertEquals(30, canvas.getGrid().getCellSize());
    }
}
