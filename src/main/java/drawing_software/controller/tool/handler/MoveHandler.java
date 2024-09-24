package drawing_software.controller.tool.handler;

import drawing_software.controller.tool.MouseRequest;
import drawing_software.model.SelectionGrid;
import drawing_software.model.Shape;
import drawing_software.view.Canvas;

import java.awt.event.MouseEvent;

public class MoveHandler extends Handler {

    public MoveHandler(Canvas canvas) {
        super(canvas);
    }

    @Override
    void handlePressed(MouseRequest request) {

    }

    /**
     * When dragging a selected shape, this function moves the shape recalculating the location.
     * new position of the figure is given translating the location of the figure by a
     * vector (delta_x, delta_y), which components are given by the difference between the
     * coordinates between the current mouse position and the previous mouse position, stored inside
     * the MouseRequest instance.
     *
     * @param request the request to be processed
     */
    @Override
    void handleDragged(MouseRequest request) {
        MouseEvent mouseEvent = request.getMouseEvent();

        int delta_x = (int) (mouseEvent.getX() - request.getPreviousMousePoint().getX());
        int delta_y = (int) (mouseEvent.getY() - request.getPreviousMousePoint().getY());

        Shape selectedShape = request.getSelectedShape();

        selectedShape.setLocation(selectedShape.getBounds().getX() + delta_x, selectedShape.getBounds().getY() + delta_y);
        canvas.clearSelectedDrawable();
        canvas.setSelectionGrid(new SelectionGrid(selectedShape));
        request.setPreviousMousePoint(mouseEvent.getPoint());
        canvas.repaint();
    }

}
