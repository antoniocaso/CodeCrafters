package drawing_software.view;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.tool.SelectionTool;
import drawing_software.controller.tool.Tool;
import drawing_software.model.Drawable;
import drawing_software.model.Drawing;
import drawing_software.model.Grid;
import drawing_software.model.SelectionGrid;

import javax.swing.*;
import java.awt.*;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.Transferable;

import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.geom.Point2D;
import java.util.logging.Logger;

public class Canvas extends JPanel implements ClipboardOwner {

    private Grid grid;

    private Drawing drawing;

    private Drawable dummyDrawable;

    private Tool currentTool;

    private Color currentFillColor;

    private Color currentStrokeColor = Color.black;

    private SelectionGrid selectionGrid;

    private Drawable copiedShape;

    private boolean fixedResize;

    private AffineTransform inverse;

    public Canvas(Invoker invoker) {
        this.drawing = new Drawing();
        this.grid = new Grid(999999999, this);
        currentTool = new SelectionTool(this, invoker);
        this.setBackground(Color.lightGray);
        this.setOpaque(true);
       /* this.addMouseWheelListener(this);*/
    }
    @Override
    public Dimension getPreferredSize() {
        return new Dimension(1280, 720);
    }

    public Drawing getDrawing() {
        return drawing;
    }

    public void setDrawing(Drawing drawing) {
        this.drawing = drawing;
    }

    public Drawable getDummyDrawable() {
        return dummyDrawable;
    }

    public void setDummyDrawable(Drawable drawable) {
        this.dummyDrawable = drawable;
    }

    public void clearDummyDrawable() {
        this.dummyDrawable = null;
    }

    public void setCurrentTool(Tool currentTool) {
        Tool oldTool = this.currentTool;
        this.currentTool = currentTool;
        firePropertyChange("CURRENT_TOOL", oldTool, currentTool);
    }

    public SelectionGrid getSelectionGrid() {
        return selectionGrid;
    }

    public void setSelectionGrid(SelectionGrid selectionGrid) {
        firePropertyChange("SELECTION", this.selectionGrid, selectionGrid);
        this.selectionGrid = selectionGrid;
    }

    public void clearSelectedDrawable() {
        firePropertyChange("SELECTION", this.selectionGrid, null);
        this.selectionGrid = null;
    }

    public void clearCopiedShape() {
        this.copiedShape = null;
    }

    public Tool getCurrentTool() {
        return currentTool;
    }

    public Color getCurrentFillColor() {
        return currentFillColor;
    }

    public void setCurrentFillColor(Color currentFillColor) {
        this.currentFillColor = currentFillColor;
    }

    public Color getCurrentStrokeColor() {
        return currentStrokeColor;
    }

    public void setCurrentStrokeColor(Color currentStrokeColor) {
        this.currentStrokeColor = currentStrokeColor;
    }


    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        at = new AffineTransform();

        RenderingHints rh = new RenderingHints(
                RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.setRenderingHints(rh);

        g2d.clearRect(0, 0, this.getWidth(), this.getHeight());

        this.grid.draw(g2d);

        g2d.setStroke(new BasicStroke(1));

        at.translate(scalePoint.getX(), scalePoint.getY());
        at.scale(scaleFactor * 0.2, scaleFactor * 0.2);
        at.translate(-scalePoint.getX(), -scalePoint.getY());
        g2d.transform(at);

        for (Drawable d : this.drawing) {
            d.draw(g2d);
        }

        if (dummyDrawable != null) {
            dummyDrawable.draw(g2d);
        }

        if (selectionGrid != null) {
            selectionGrid.draw((Graphics2D) g);
        }
        try {
            inverse = at.createInverse();
        } catch (NoninvertibleTransformException e) {
            throw new RuntimeException(e);
        }
    }

    public Drawable getCopiedShape() {
        return copiedShape;
    }

    public void setCopiedShape(Drawable copiedShape) {
        this.copiedShape = copiedShape;
    }

    @Override
    public void lostOwnership(Clipboard clipboard, Transferable contents) {
        Logger.getLogger("root").info("ClipboardTest: Lost ownership");
        firePropertyChange("CLIPBOARD_EMPTY", false, true);
    }

    public boolean isFixedResize() {
        return fixedResize;
    }

    public void setFixedResize(boolean fixedResize) {
        this.fixedResize = fixedResize;
    }

    public Grid getGrid() {
        return grid;
    }

    public void setGrid(Grid grid) {
        this.grid = grid;
    }


    public AffineTransform getAt() {
        return at;
    }

    public void setAt(AffineTransform at) {
        this.at = at;
    }

    private AffineTransform at = new AffineTransform();
    private int scaleFactor = 5;

    public int getScaleFactor() {
        return scaleFactor;
    }

    public void setScaleFactor(int scaleFactor) {
        this.scaleFactor = scaleFactor;
    }
    private Point2D scalePoint = new Point(0,0);
    public void setScalePoint(Point2D scalePoint) {
        this.scalePoint = scalePoint;
    }

    public Point2D getScalePoint() {
        return scalePoint;
    }

    public AffineTransform getInverse() {
        return inverse;
    }


}
