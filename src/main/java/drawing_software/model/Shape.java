package drawing_software.model;

import java.awt.*;
import java.awt.geom.Point2D;

/**
 * Provides a common interface to all the concrete Drawables.
 */
public interface Shape extends Drawable {

    /**
     * Checks if input Point is inside the shape.
     *
     * @param point the point to test for inclusion
     * @return True if point is inside the Shape, False otherwise
     */
    boolean contains(Point2D point);

    /**
     * Changes the shape location and dimension by modifying the rectangular frame the shape's
     * inscribed in.
     *
     * @param point the new location of the shape
     * @param size  the new size of the shape
     */
    void setFrame(Point2D point, Dimension size);

    /**
     * Changes the location of the shape, meaning the point at the top left of the shape.
     *
     * @param point the new location of the shape
     */
    void setLocation(Point2D point);

    default void setLocation(double x, double y) {
        this.setLocation(new Point2D.Double(x, y));
    }

    /**
     * Changes the size of the shape, meaning the width and the height of the
     * bounding rectangle.
     *
     * @param size the new size of the shape
     */
    void setSize(Dimension size);

    /**
     * @return the bounding rectangle of the shape
     */
    Rectangle getBounds();

    Shape clone();

    void setStrokeColor(Paint color);

    Paint getStrokeColor();

    default void setFillColor(Paint color) {
    }

    default Paint getFillColor() {
        return null;
    }
}
