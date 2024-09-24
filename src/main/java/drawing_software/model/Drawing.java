package drawing_software.model;

import java.io.Serializable;
import java.util.Iterator;
import java.util.LinkedList;

/**
 * Implements the structure containing the instantiated shapes, as in actually drawn on
 * the canvas and thus having each one their own properties.
 */
public class Drawing implements Serializable, Iterable<Drawable> {
    private LinkedList<Drawable> listDrawables;

    /**
     * Allows to create the data structure used to hold the drawn shapes, be they
     * rectangles, lines or ellipses.
     */
    public Drawing() {
        this.listDrawables = new LinkedList<>();
    }

    /**
     * Allows to add a Drawable object to the data structure.
     * @param drawable is drawn (on the canvas) the shape to be added.
     */
    public void addDrawable(Drawable drawable) {
        this.listDrawables.add(drawable);
    }

    /**
     * Allows to retrieve a Drawable object previously added to the data structure.
     * This does NOT remove the Drawable shape from the structure.
     * @param index is the index at which the Drawable shape is located.
     */
    public Drawable getDrawable(int index) {
        return this.listDrawables.get(index);
    }

    /**
     * Allows to retrieve (and the remove) a Drawable object previously added to the data structure.
     * This DOES remove the Drawable shape from the structure.
     *
     * @param d is the Drawable to remove.
     */
    public boolean removeDrawable(Drawable d) {
        return this.listDrawables.remove(d);
    }

    /**
     * Allows to retrieve (and the remove) a Drawable object previously added to the data structure.
     * This DOES remove the Drawable shape from the structure.
     *
     * @param index is the index at which remove the drawable.
     */
    public Drawable removeDrawable(int index) {
        return this.listDrawables.remove(index);
    }

    /**
     * Allows to verify whether a Drawable shape is present inside the data structure
     * representing the drawing.
     *
     * @param drawable is the shape which presence in the data structure is to be verified.
     */
    public boolean containsDrawable(Drawable drawable) {
        return this.listDrawables.contains(drawable);
    }

    /**
     * Allows to cycle on every shape inside the data structure.
     * @return the iterator object.
     */
    @Override
    public Iterator<Drawable> iterator() {
        return listDrawables.iterator();
    }

    /**
     * Allows to cycle BACKWARDS on every shape inside the data structure.
     * This means that the shapes will be cycled going from the last added to first
     * added one. This is useful when selecting overlapping shapes.
     *
     * @return the iterator object.
     */
    public Iterator<Drawable> descendingIterator() {
        return listDrawables.descendingIterator();
    }

    /**
     * Allows to obtain the index at which the drawable is located inside the structure (list).
     *
     * @param drawable is the drawable of which we want to find the position inside the list.
     * @return the index.
     */
    public int getDrawableIndex(Drawable drawable) {
        int i = 0;
        for (Drawable d : this.listDrawables) {
            if (d.equals(drawable)) {
                return i;
            }
            i++;
        }
        return -1;
    }

    /**
     * Allows to add a Drawable to the first position of the list; other shapes will be shifted accordingly.
     *
     * @param d is the drawable to be placed first.
     */
    public void addDrawableFirst(Drawable d) {
        listDrawables.addFirst(d);
    }

    public void addDrawableAtIndex(Drawable d, int index) {
        listDrawables.add(index, d);
    }
}
