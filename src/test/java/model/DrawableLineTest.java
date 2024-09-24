package model;

import drawing_software.model.DrawableLine;
import org.junit.Before;
import org.junit.Test;

import java.awt.geom.Point2D;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

public class DrawableLineTest {
    private DrawableLine line;

    @Before
    public void setUp() throws Exception {
        Point2D start = new Point2D.Double(50, 0);
        Point2D end = new Point2D.Double(50, 50);
        line = new DrawableLine(start, end);
    }

    @Test
    public void testContains() {
        Point2D click = new Point2D.Double(52, 5);
        assertTrue(line.contains(click));
    }

    @Test
    public void testDoNotContains() {
        Point2D click = new Point2D.Double(0, 5);
        assertFalse(line.contains(click));
    }
}