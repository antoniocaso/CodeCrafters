package drawing_software.model;

import drawing_software.view.Canvas;

import java.awt.*;

/**
 * Defines a grid to be applied to the canvas. The grid is also customisable by varying the cellSize paramenter
 * and thus increasing the size of the single cells.
 */
public class Grid implements Drawable {
    private int cellSize;
    private Canvas canvas;
    private int canvasHeight;
    private int canvasWidth;

    public Grid(int cellSize, Canvas canvas) {
        this.cellSize = cellSize;
        this.canvas = canvas;
    }

    public Grid(int canvasHeight, int canvasWidth, int cellSize, Canvas canvas) {
        this.cellSize = cellSize;
        this.canvas = canvas;
        this.canvasHeight = canvasHeight;
        this.canvasWidth = canvasWidth;
    }

    /**
     * Allows to draw the grid by drawing a certain number of columns and rows (based on the canvas' properties).
     * The grid is drawn always before the shapes so that it remains always in the backmost layer of the drawing.
     *
     * @param g2d is the Graphics2D object needed to draw on the canvas.
     */
    @Override
    public void draw(Graphics2D g2d) {
        g2d.setStroke(new BasicStroke(1));
        g2d.setColor(Color.LIGHT_GRAY);
        for (int i = 0; i < 1.1 * canvas.getHeight() / cellSize; i++) {
            int y = i * cellSize;
            g2d.drawLine(0, y, canvas.getWidth(), y);
        }
        for (int i = 0; i < 1.1 * canvas.getWidth() / cellSize; i++) {
            int x = i * cellSize;
            g2d.drawLine(x, 0, x, canvas.getHeight());
        }
    }

    public int getCellSize() {
        return cellSize;
    }

    public void setCellSize(int cellSize) {
        this.cellSize = cellSize;
    }

    public int getCanvasWidth() {
        return canvasWidth;
    }

    public void setCanvasWidth(int canvasWidth) {
        this.canvasWidth = canvasWidth;
    }

    public int getCanvasHeight() {
        return canvasHeight;
    }

    public void setCanvasHeight(int canvasHeight) {
        this.canvasHeight = canvasHeight;
    }

}
