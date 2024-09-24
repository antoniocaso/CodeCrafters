package view;

import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

public class FillPanelTest {
    private Invoker invoker;

    private Canvas canvas;

    @Before
    public void setUp() throws Exception {
        invoker = new Invoker();
        canvas = new Canvas(invoker);

    }

    @Test
    public void testChangeCanvasFillColor() {
    }

    @Test
    public void testChangeShapeFillColor() {
    }
}