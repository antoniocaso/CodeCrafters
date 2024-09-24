package model;

import drawing_software.model.DrawableRectangle;
import drawing_software.model.Drawing;
import org.junit.Before;
import org.junit.Test;

import java.awt.*;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class DrawingTest {
    private Drawing d;
    private DrawableRectangle dr;

    @Before
    public void setUp() {
        d = new Drawing();
        dr = new DrawableRectangle(33, 33);
    }

    @Test
    public void testAddDrawable() {
        d.addDrawable(dr);
        DrawableRectangle d2 = (DrawableRectangle) d.getDrawable(0);
        assertEquals(d2, dr);
    }

    @Test
    public void testGetDrawable() {
        d.addDrawable(dr);
        DrawableRectangle d3 = (DrawableRectangle) d.getDrawable(0);
        assertEquals(d3, dr);
    }

    @Test
    public void testRemoveDrawable() {
        d.addDrawable(dr);
        //DrawableLine dl = new DrawableLine(Color.black, new Point2D.Double(0,0), new Point2D.Double(30, 30));
        assertTrue(d.removeDrawable(dr));
    }

    @Test
    public void testContainsDrawable() {
        d.addDrawable(dr);
        assertTrue(d.containsDrawable(dr));
    }

    @Test
    public void testGetDrawableIndex() {
        DrawableRectangle dr2 = new DrawableRectangle(Color.cyan, Color.black, 30, 30);
        DrawableRectangle dr3 = new DrawableRectangle(Color.cyan, Color.black, 30, 30);
        d.addDrawable(dr);
        d.addDrawable(dr2);
        d.addDrawable(dr3);
        assertEquals(1, d.getDrawableIndex(dr2)); //Should return index = 1
    }

    @Test
    public void testAddDrawableFirst() {
        DrawableRectangle dr2 = new DrawableRectangle(Color.cyan, Color.black, 30, 30);
        DrawableRectangle dr3 = new DrawableRectangle(Color.cyan, Color.black, 40, 30);
        d.addDrawable(dr2);
        d.addDrawable(dr);
        d.addDrawableFirst(dr3);
        assertEquals(dr3, d.getDrawable(0));
    }
}
