package controller;

import drawing_software.controller.command.CopyCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.PasteCommand;
import drawing_software.controller.tool.PasteTool;
import drawing_software.controller.tool.SelectionTool;
import drawing_software.model.Drawable;
import drawing_software.model.DrawableRectangle;
import drawing_software.model.SelectionGrid;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.*;
import java.awt.datatransfer.DataFlavor;
import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import static org.junit.Assert.assertEquals;

public class PasteToolTest {

    private Canvas canvas;
    private Invoker invoker;
    private DataFlavor df;
    private PasteCommand pc;
    private DrawableRectangle dr;
    private SelectionGrid sg;
    private CopyCommand cc;
    private SelectionTool selectionTool;
    private PasteTool pt;

    @Before
    public void setUp() throws ClassNotFoundException {
        JFrame frame = new JFrame();
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        frame.add(canvas);
        pc = new PasteCommand(canvas, new Point2D.Double(42, 69));
        df = new DataFlavor(DataFlavor.javaJVMLocalObjectMimeType + ";class=\"" + Drawable.class.getName() + "\"");
        dr = new DrawableRectangle(Color.white, Color.cyan, 10, 10);
        dr.setFrame(10, 10, 60, 60);
        sg = new SelectionGrid(dr);
        cc = new CopyCommand(canvas);
        selectionTool = new SelectionTool(canvas, invoker);
        pt = new PasteTool(canvas, invoker);
    }

    @Test
    public void testMouseLeftPressed() {
        canvas.setSelectionGrid(new SelectionGrid(dr));
        cc.execute();

        Point2D clickPoint = new Point2D.Double(82, 88);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        pt.mouseLeftPressed(e);

        selectionTool.mouseLeftPressed(e);
        Drawable dr2 = canvas.getSelectionGrid().getSelectedShape();
        Drawable dr3 = canvas.getDrawing().getDrawable(0);
        assertEquals(dr3, dr2);
    }

    @Test
    public void testMouseDragged() {
        canvas.setSelectionGrid(new SelectionGrid(dr));
        cc.execute();

        Point2D clickPoint = new Point2D.Double(82, 88);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        pt.mouseDragged(e);

        Point2D clickPoint2 = new Point2D.Double(82, 88);
        MouseEvent e2 = new MouseEvent(canvas, MouseEvent.MOUSE_DRAGGED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint2.getX(), (int) clickPoint2.getY(), 1, false);
        selectionTool.mouseLeftPressed(e2);
        Drawable dr2 = canvas.getSelectionGrid().getSelectedShape();
        Drawable dr3 = canvas.getDrawing().getDrawable(0);
        assertEquals(dr3, dr2);
    }

}
