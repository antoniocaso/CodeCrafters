package drawing_software.model;

import java.awt.*;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.util.Objects;

/**
 * Defines the actual line shape and it's properties.
 */
public class DrawableLine extends Line2D.Double implements Shape {
    private Paint strokeColor;
    private static final int HIT_BOX_SIZE = 5;

    /**
     * Creates a line object whose properties will be set the input parameters' values.
     *
     * @param strokeColor is the color of the line.
     * @param p1          is the starting point of the line.
     * @param p2          is the end point of the line.
     */
    public DrawableLine(Paint strokeColor, Point2D p1, Point2D p2) {
        super(p1, p2);
        this.strokeColor = strokeColor;
    }

    /**
     * Creates a line in which the strokeColor property will be set to default value,
     * that is the color black.
     *
     * @param p1 is the starting point of the line.
     * @param p2 is the end point of the line.
     */
    public DrawableLine(Point2D p1, Point2D p2) {
        this(Color.black, p1, p2);
    }

    /**
     * Allows to draw che input parameter object by calling the parent's draw method.
     * A BasicStroke object is also created, in the method, in order to specify the width of the line to be drawn.
     *
     * @param g2d is the Graphics2D object to be drawn.
     */
    @Override
    public void draw(Graphics2D g2d) {
        g2d.setPaint(strokeColor);
        g2d.draw(this);
    }

    /**
     * Allows to verify if an input object and a DrawableLine one are actually
     * equivalent to each other. Used in JUnit testing.
     *
     * @param o an {@code Object} to be compared with this
     *          {@code Line2D}.
     * @return whether the input object is actually equal to the DrawableLine object.
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        DrawableLine that = (DrawableLine) o;

        return Objects.equals(strokeColor, that.strokeColor) && that.getP1().equals(this.getP1()) && that.getP2().equals(this.getP2());
    }

    @Override
    public int hashCode() {
        return strokeColor != null ? strokeColor.hashCode() : 0;
    }

    /**
     * Given a clicked point on the canvas, allows to check whether the point
     * belongs to the line. This is done by gifting the line of a hitbox so that
     * the intersection between the line and the point is not unlikely and
     * painstaking to achieve.
     *
     * @param point the specified {@code Point2D} to be tested
     * @return whether the line contains the point within its hitbox or not.
     */
    @Override
    public boolean contains(Point2D point) {
        double boxX = point.getX() - HIT_BOX_SIZE / 2;
        double boxY = point.getY() - HIT_BOX_SIZE / 2;

        return this.intersects(boxX, boxY, HIT_BOX_SIZE, HIT_BOX_SIZE);
    }

    @Override
    public void setFrame(Point2D point, Dimension size) {
        super.setLine(point, new Point2D.Double(point.getX()+size.getWidth(), point.getY() + size.getHeight()));
    }

    @Override
    public void setLocation(Point2D point) {
        this.setFrame(point, new Dimension((int) (getX2()-getX1()), (int)(getY2()-getY1())));
    }

    @Override
    public void setSize(Dimension size) {
        this.setFrame(this.getP1(), size);
    }

    @Override
    public Rectangle getBounds() {
        return super.getBounds();
    }

    @Override
    public DrawableLine clone() {
        DrawableLine clone = (DrawableLine) super.clone();
        clone.setStrokeColor(this.strokeColor);
        clone.setLocation(this.getP1());
        return clone;
    }

    @Override
    public void setStrokeColor(Paint color) {
        this.strokeColor = color;
    }

    @Override
    public Paint getStrokeColor() {
        return strokeColor;
    }

}
