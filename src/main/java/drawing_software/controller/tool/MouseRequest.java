package drawing_software.controller.tool;

import drawing_software.model.Shape;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

/**
 * Represents the action performed by an user while using selection tool.
 * This class needs to store:
 * <ul>
 *     <li>
 *         mouseEvent: the MouseEvent instance called by the selection tool.
 *     </li>
 *     <li>
 *         selectedShape: the shape currently selected in the canvas.
 *     </li>
 *     <li>
 *          previousShapeLocation: the location of the shape before the user interaction.
 *     </li>
 *     <li>
 *          previousShapeSize: the size of the shape before the user interaction.
 *     </li>
 *     <li>
 *         previousMousePoint: the location of the mouse during the previous request.
 *     </li>
 *     <li>
 *         startingPoint: the top left point of the shape that needs to be modified.
 *     </li>
 *     <li>
 *         ratio: the ratio between the width and the height of the shape, used by the resize functionality.
 *     </li>
 * </ul>
 */
public class MouseRequest {

    private MouseEvent mouseEvent;

    private Shape selectedShape;
    private Point2D previousShapeLocation;
    private Dimension previousShapeSize;
    private Point2D previousMousePoint;
    private Point2D startingPoint;
    private double ratio;

    public MouseEvent getMouseEvent() {
        return mouseEvent;
    }

    public void setMouseEvent(MouseEvent mouseEvent) {
        this.mouseEvent = mouseEvent;
    }

    public Shape getSelectedShape() {
        return selectedShape;
    }

    public void setSelectedShape(Shape selectedShape) {
        this.selectedShape = selectedShape;
    }

    public Point2D getPreviousShapeLocation() {
        return previousShapeLocation;
    }

    public void setPreviousShapeLocation(Point2D previousShapeLocation) {
        this.previousShapeLocation = previousShapeLocation;
    }

    public Dimension getPreviousShapeSize() {
        return previousShapeSize;
    }

    public void setPreviousShapeSize(Dimension previousShapeSize) {
        this.previousShapeSize = previousShapeSize;
    }

    public Point2D getPreviousMousePoint() {
        return previousMousePoint;
    }

    public void setPreviousMousePoint(Point2D previousMousePoint) {
        this.previousMousePoint = previousMousePoint;
    }

    public Point2D getStartingPoint() {
        return startingPoint;
    }

    public void setStartingPoint(Point2D startingPoint) {
        this.startingPoint = startingPoint;
    }

    public double getRatio() {
        return ratio;
    }

    public void setRatio(double ratio) {
        this.ratio = ratio;
    }
}
