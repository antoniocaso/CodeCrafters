package drawing_software.model;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;
import java.util.Objects;

/**
 * Defines the actual ellipse shape and it's properties.
 */
public class DrawableEllipse extends Ellipse2D.Double implements Shape {
    private Paint fillColor;
    private Paint strokeColor;

    /**
     * Creates an ellipse in which the properties will be set to the input parameters' values.
     *
     * @param fillColor   is the internal color of the shape.
     * @param strokeColor is the outline color of the shape.
     * @param x           is the first coordinate used to determine the position on the canvas.
     * @param y           is the second coordinate used to determine the position on the canvas.
     */
    public DrawableEllipse(Paint fillColor, Paint strokeColor, double x, double y) {
        super(x, y, 0, 0);
        this.fillColor = fillColor;
        this.strokeColor = strokeColor;
    }

    /**
     * Creates an ellipse in which the fillColor and strokeColor properties will be set to default values,
     * which are TRANSPARENT for the fill and black for the stroke.
     *
     * @param x is the first coordinate used to determine the position on the canvas.
     * @param y is the second coordinate used to determine the position on the canvas.
     */
    public DrawableEllipse(double x, double y) {
        this(null, Color.black, x, y);
    }

    /**
     * Allows to draw che input parameter object by calling the parent's draw method.
     * If the default constructor is used, and the fill is to be transparent, then there is no need
     * to call the fill() method at all.
     *
     * @param g2d is the Graphics2D object to be drawn.
     */
    @Override
    public void draw(Graphics2D g2d) {
        if (fillColor != null) {
            g2d.setPaint(fillColor);
            g2d.fill(this);
        }
        g2d.setPaint(strokeColor);
        g2d.draw(this);
    }

    /**
     * Allows to verify if an input object and a DrawableEllipse one are actually
     * equivalent to each other. Used in JUnit testing.
     *
     * @param o an {@code Object} to be compared with this
     *          {@code Ellipse2D}.
     * @return whether the input object is actually equal to the DrawableEllipse object.
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;

        DrawableEllipse that = (DrawableEllipse) o;

        if (!Objects.equals(fillColor, that.fillColor)) return false;
        return Objects.equals(strokeColor, that.strokeColor);
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (fillColor != null ? fillColor.hashCode() : 0);
        result = 31 * result + (strokeColor != null ? strokeColor.hashCode() : 0);
        return result;
    }

    @Override
    public boolean contains(Point2D point) {
        return super.contains(point);
    }

    @Override
    public void setFrame(Point2D point, Dimension size) {
        super.setFrame(point, size);
    }

    @Override
    public void setLocation(Point2D point) {
        this.setFrame(point, new Dimension((int) this.getWidth(), (int) this.getHeight()));
    }

    @Override
    public void setSize(Dimension size) {
        this.setFrame(new Point2D.Double(this.getX(), this.getY()), size);
    }

    @Override
    public Rectangle getBounds() {
        return super.getBounds();
    }

    @Override
    public void setStrokeColor(Paint color) {
        this.strokeColor = color;
    }

    @Override
    public Paint getStrokeColor() {
        return strokeColor;
    }


    @Override
    public void setFillColor(Paint color) {
        this.fillColor = color;
    }

    @Override
    public Paint getFillColor() {
        return fillColor;
    }

    @Override
    public DrawableEllipse clone() {
        DrawableEllipse clone = (DrawableEllipse) super.clone();
        clone.setFillColor(this.fillColor);
        clone.setStrokeColor(this.strokeColor);
        clone.setFrame(this.getFrame());
        return clone;
    }
}
