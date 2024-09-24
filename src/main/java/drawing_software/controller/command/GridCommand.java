package drawing_software.controller.command;

import drawing_software.view.Canvas;

/**
 * Implements the command to be called in order to have the grid drawn.
 */
public class GridCommand implements Command {
    private final Canvas canvas;
    private int cellSize;

    public GridCommand(Canvas canvas, int cellSize) {
        this.canvas = canvas;
        this.cellSize = cellSize;
    }

    /**
     * Firstly, the cellSize is set to the preferred size desired and received through the constructor,
     * and then the repaint() method on the canvas is called so that the canvas will call the draw() method on
     * the Grid object.
     */
    @Override
    public void execute() {
        canvas.getGrid().setCellSize(cellSize);
        //canvas.getGrid().setCanvasHeight(canvas.getHeight());
        //canvas.getGrid().setCanvasWidth(canvas.getWidth());
        canvas.repaint();
    }

}
