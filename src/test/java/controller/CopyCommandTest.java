package controller;

import drawing_software.controller.command.Command;
import drawing_software.controller.command.CopyCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.SelectionTool;
import drawing_software.model.Drawable;
import drawing_software.model.DrawableEllipse;
import drawing_software.model.DrawableLine;
import drawing_software.model.DrawableRectangle;
import drawing_software.view.Canvas;
import org.junit.Before;
import org.junit.Test;

import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.event.InputEvent;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;
import java.io.IOException;

import static org.junit.Assert.assertEquals;

public class CopyCommandTest {
    private Canvas canvas;
    private Invoker invoker;
    private SelectionTool selectionTool;
    private Command copyCommand;

    @Before
    public void setUp() {
        invoker = new Invoker();
        canvas = new Canvas(invoker);
        selectionTool = new SelectionTool(canvas, invoker);
        copyCommand = new CopyCommand(canvas);

    }

    @Test
    public void testExecuteCopyLine() throws ClassNotFoundException, IOException, UnsupportedFlavorException {
        //create a line to test
        Point2D start = new Point(0, 0);
        Point2D end = new Point(0, 20);
        DrawableLine lineToTest = new DrawableLine(start, end);
        lineToTest.setStrokeColor(Color.black);
        canvas.getDrawing().addDrawable(lineToTest);
        //simulate click on figure
        Point2D clickPoint = new Point2D.Double(0, 10);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);
        //execute copy
        copyCommand.execute();
        //take clipboard contents
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        DataFlavor dataFlavor = new DataFlavor(DataFlavor.javaJVMLocalObjectMimeType + ";class=\"" + Drawable.class.getName() + "\"");
        Transferable taken = clipboard.getContents(this);
        DrawableLine copiedShape = (DrawableLine) taken.getTransferData(dataFlavor);
        //assert on figure and color
        assertEquals(lineToTest, copiedShape);
        assertEquals(lineToTest.getStrokeColor(), copiedShape.getStrokeColor());
    }


    @Test
    public void testExecuteCopyRectangle() throws ClassNotFoundException, IOException, UnsupportedFlavorException {
        //create a rectangle to test
        DrawableRectangle rectangleToTest = new DrawableRectangle(50, 50);
        rectangleToTest.setRect(50, 50, 50, 50);
        rectangleToTest.setFillColor(Color.white);
        rectangleToTest.setStrokeColor(Color.black);
        canvas.getDrawing().addDrawable(rectangleToTest);
        //simulate click on figure
        Point2D clickPoint = new Point2D.Double(50, 50);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);
        //execute copy
        copyCommand.execute();
        //take clipboard contents
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        DataFlavor dataFlavor = new DataFlavor(DataFlavor.javaJVMLocalObjectMimeType + ";class=\"" + Drawable.class.getName() + "\"");
        Transferable taken = clipboard.getContents(this);
        DrawableRectangle copiedShape = (DrawableRectangle) taken.getTransferData(dataFlavor);
        //assert on figure and color
        assertEquals(rectangleToTest, copiedShape);
        assertEquals(rectangleToTest.getStrokeColor(), copiedShape.getStrokeColor());
        assertEquals(rectangleToTest.getFillColor(), copiedShape.getFillColor());
    }

    @Test
    public void testExecuteCopyELlipse() throws ClassNotFoundException, IOException, UnsupportedFlavorException {
        //create a ellipse to test
        DrawableEllipse ellipseToTest = new DrawableEllipse(0, 0);
        ellipseToTest.setFrame(0, 0, 10, 10);
        ellipseToTest.setFillColor(Color.white);
        ellipseToTest.setStrokeColor(Color.black);
        canvas.getDrawing().addDrawable(ellipseToTest);
        //simulate click on figure
        Point2D clickPoint = new Point2D.Double(5, 5);
        MouseEvent e = new MouseEvent(canvas, MouseEvent.MOUSE_PRESSED, 1, InputEvent.BUTTON1_DOWN_MASK, (int) clickPoint.getX(), (int) clickPoint.getY(), 1, false);
        selectionTool.mouseLeftPressed(e);
        //execute copy
        copyCommand.execute();
        //take clipboard contents
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        DataFlavor dataFlavor = new DataFlavor(DataFlavor.javaJVMLocalObjectMimeType + ";class=\"" + Drawable.class.getName() + "\"");
        Transferable taken = clipboard.getContents(this);
        DrawableEllipse copiedShape = (DrawableEllipse) taken.getTransferData(dataFlavor);
        //assert on figure and color
        assertEquals(ellipseToTest, copiedShape);
        assertEquals(ellipseToTest.getStrokeColor(), copiedShape.getStrokeColor());
        assertEquals(ellipseToTest.getFillColor(), copiedShape.getFillColor());

    }

}