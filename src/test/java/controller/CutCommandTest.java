package controller;

import drawing_software.controller.command.CutCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.SelectionTool;
import drawing_software.model.Drawable;
import drawing_software.model.DrawableEllipse;
import drawing_software.model.SelectionGrid;
import drawing_software.model.Shape;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import javax.swing.*;
import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;

import static org.junit.Assert.*;


public class CutCommandTest {
    private Canvas canvas;
    private SelectionTool st;
    private Invoker invoker;
    private CutCommand ct;
    private DrawableEllipse dr;

    @Before
    public void setUp() throws Exception {
        JFrame frame = new JFrame();
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        frame.add(canvas);
        st = new SelectionTool(canvas, invoker);
        ct = new CutCommand(canvas);
        dr = new DrawableEllipse(Color.cyan, Color.gray, 40, 40);
    }

    @Test
    public void testExecute() throws IOException, UnsupportedFlavorException, ClassNotFoundException {
        canvas.setSelectionGrid(new SelectionGrid(dr));
        ct.execute();
        DataFlavor dataFlavor = new DataFlavor(DataFlavor.javaJVMLocalObjectMimeType + ";class=\"" + Drawable.class.getName() + "\"");
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        Transferable tr = clipboard.getContents(this);
        drawing_software.model.Shape copiedShape = (Shape) tr.getTransferData(dataFlavor);
        assertFalse(canvas.getDrawing().removeDrawable(dr));
        assertEquals(dr, copiedShape);
    }

    /**
     * Given a shape, we execute the cut command on it. When we execute the undo method,
     * the shape must go back inside the drawing.
     */
    @Test
    public void testUndo() {
        canvas.getDrawing().addDrawable(dr);
        canvas.setSelectionGrid(new SelectionGrid(dr));
        ct.execute();
        ct.undo();
        assertTrue(canvas.getDrawing().containsDrawable(dr));
    }
}
