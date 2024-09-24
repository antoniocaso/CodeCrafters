package drawing_software.model;

import java.awt.*;
import java.awt.geom.Point2D;

/**
 * A shape per-se, allows to mark the selection of the selected shape.
 */
public class SelectionGrid extends DrawableRectangle {
    private Shape selectedShape;
    private Vertex vertexes[] = new Vertex[4];
    private int selectedVertex;

    Stroke dashed = new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);

    /**
     * Allows to actually create the selection grid by calculating the dimensions of the selected shape and,
     * through them, define the width and height of the grid so that it just encompassed the selected shape.
     * When a fill color is not purposefully selected, the shape will be transparent on the inside.
     *
     * @param selectedShape is the selected shape that's intended to be highlighted.
     */
    public SelectionGrid(Shape selectedShape) {
        super(null, Color.gray, selectedShape.getBounds().getX(), selectedShape.getBounds().getY());
        this.setRect(selectedShape.getBounds().getX() - 1, selectedShape.getBounds().getY() - 1, selectedShape.getBounds().getWidth() + 2, selectedShape.getBounds().getHeight() + 2);
        this.selectedShape = selectedShape;
        this.selectedVertex = -1;

        vertexes[Vertex.UPLEFT] = new Vertex(this, Vertex.UPLEFT);
        vertexes[Vertex.UPRIGHT] = new Vertex(this, Vertex.UPRIGHT);
        vertexes[Vertex.BOTTOMLEFT] = new Vertex(this, Vertex.BOTTOMLEFT);
        vertexes[Vertex.BOTTOMRIGHT] = new Vertex(this, Vertex.BOTTOMRIGHT);
    }

    /**
     * Allows to draw the selection grid, having previously set the style of the stroke,
     * by calling the parent method and passing the Graphics2D object.
     *
     * @param g2d is the Graphics2D object that is going to be painted on the canvas.
     */
    @Override
    public void draw(Graphics2D g2d) {
        for (int i = 0; i < 4; i++) {
            vertexes[i].draw(g2d);
        }
        g2d.setStroke(dashed);
        super.draw(g2d);
    }

    public Vertex[] getVertexes() {
        return vertexes;
    }

    /**
     * Getter method for the selectedShape property.
     *
     * @return the actual selected shape.
     */

    public Shape getSelectedShape() {
        return selectedShape;
    }

    public int getSelectedVertex() {
        return selectedVertex;
    }

    public boolean isVertexClicked(Point2D point) {
        if (vertexes[0].contains(point)) {
            selectedVertex = Vertex.UPLEFT;
            return true;
        } else if (vertexes[1].contains(point)) {
            selectedVertex = Vertex.UPRIGHT;
            return true;
        } else if (vertexes[2].contains(point)) {
            selectedVertex = Vertex.BOTTOMLEFT;
            return true;
        } else if (vertexes[3].contains(point)) {
            selectedVertex = Vertex.BOTTOMRIGHT;
            return true;
        } else {
            selectedVertex = -1;
            return false;
        }
    }


    @Override
    public void setFrame(Point2D point, Dimension size) {
        super.setFrame(new Point2D.Double(point.getX() - 1, point.getY() - 1), new Dimension((int) size.getWidth() + 2, (int) size.getHeight() + 2));
        vertexes[Vertex.UPLEFT] = new Vertex(this, Vertex.UPLEFT);
        vertexes[Vertex.UPRIGHT] = new Vertex(this, Vertex.UPRIGHT);
        vertexes[Vertex.BOTTOMLEFT] = new Vertex(this, Vertex.BOTTOMLEFT);
        vertexes[Vertex.BOTTOMRIGHT] = new Vertex(this, Vertex.BOTTOMRIGHT);
    }


    public void clearSelectedVertex() {
        selectedVertex = -1;
    }
}
