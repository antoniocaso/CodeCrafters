package drawing_software.model;

import java.awt.*;

/**
 * Interface to be implemented by all the shapes belonging to the hierarchy.
 */
public interface Drawable {
    /**
     * Allows to draw the Graphics2D object that is received as an input parameter.
     * All the shapes in the hierarchy will have to implement the method.
     *
     * @param g2d is the Graphics2D object to be drawn.
     */
    void draw(Graphics2D g2d);
}
