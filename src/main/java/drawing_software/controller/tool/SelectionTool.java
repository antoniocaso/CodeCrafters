package drawing_software.controller.tool;

import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.MoveCommand;
import drawing_software.controller.command.ResizeCommand;
import drawing_software.controller.tool.handler.SelectionHandler;
import drawing_software.model.Shape;
import drawing_software.view.Canvas;
import drawing_software.view.menu.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public class SelectionTool implements Tool {
    private final Canvas canvas;
    private final Invoker invoker;

    private final MouseRequest request = new MouseRequest();

    private final JPopupMenu popupMenu;

    public SelectionTool(Canvas canvas, Invoker invoker) {
        this.canvas = canvas;
        this.invoker = invoker;
        request.setStartingPoint(new Point2D.Double(0, 0));
        popupMenu = createPopupMenu();
    }

    /**
     * When pressing the mouse, this method checks if the user is pressing a valid shape,
     * then saves the current shape location and the initial mouse position.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseLeftPressed(MouseEvent mouseEvent) {
        request.setMouseEvent(mouseEvent);
        new SelectionHandler(canvas).handlePressed(request);

    }

    /**
     * When dragging the mouse, this method checks if the user has pressed a valid shape,
     * then moves the shape and the selection grid according to the movement of the user.
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseDragged(MouseEvent mouseEvent) {

        if (canvas.getSelectionGrid() != null) {
            request.setMouseEvent(mouseEvent);
            new SelectionHandler(canvas).handleDragged(request);
        }
    }

    /**
     * When releasing the mouse, this method executes a concrete command
     * representing the update of the location or the size of the figure,
     * by invoking Resize Command or Move Command accordingly.
     *
     * @param mouseEvent the event to be processed
     */
    @Override
    public void mouseReleased(MouseEvent mouseEvent) {
        Shape selectedShape = request.getSelectedShape();
        if (selectedShape == null || canvas.getSelectionGrid() == null) return;

        Dimension oldShapeSize = request.getPreviousShapeSize();
        Point2D oldShapeLocation = request.getPreviousShapeLocation();
        Rectangle bounds = canvas.getSelectionGrid().getSelectedShape().getBounds();

        if (oldShapeSize != null && !bounds.getSize().equals(oldShapeSize)) {
            invoker.executeCommand(new ResizeCommand(canvas, selectedShape, oldShapeLocation, oldShapeSize));
        } else if (oldShapeLocation != null && !bounds.getLocation().equals(oldShapeLocation)) {
            invoker.executeCommand(new MoveCommand(canvas, selectedShape, oldShapeLocation));
        }

        request.setRatio(canvas.getSelectionGrid().getWidth() / canvas.getSelectionGrid().getHeight());
        canvas.getSelectionGrid().clearSelectedVertex();
    }

    /**
     * Simply shows up the PopUpMenu when mouse is right-clicked.
     *
     * @param mouseEvent
     */
    @Override
    public void mouseRightClicked(MouseEvent mouseEvent) {
        popupMenu.show(canvas, mouseEvent.getX(), mouseEvent.getY());
    }

    /**
     * Creates all the menuItem which will be added to the PopUpMenu
     * Initially sets them disabled.
     * <p>
     * Adds a PropertyChangeListener to the canvas. This is used for enabling and disabling the menuItems accordingly to
     * the current state of the program.
     * When there's no selected shape, all the menu items(except for the paste one) will be disabled; otherwise it will enable them.
     * When the clipboard is empty, the paste menu item will be disabled; otherwise it will enable it.
     *
     * @return JPopupMenu with all the menuItems
     */
    private JPopupMenu createPopupMenu() {

        JPopupMenu popupMenu = new JPopupMenu();
        JMenuItem cutMenuItem = new CutMenuItem(canvas, invoker).createMenuItem();
        cutMenuItem.setFocusable(false);
        popupMenu.add(cutMenuItem);

        JMenuItem copyMenuItem = new CopyMenuItem(canvas, invoker).createMenuItem();
        copyMenuItem.setFocusable(false);
        popupMenu.add(copyMenuItem);

        JMenuItem pasteMenuItem = new PasteMenuItem(canvas, invoker).createMenuItem();
        pasteMenuItem.setFocusable(false);
        popupMenu.add(pasteMenuItem);

        JMenuItem deleteMenuItem = new DeleteMenuItem(canvas, invoker).createMenuItem();
        deleteMenuItem.setFocusable(false);
        popupMenu.add(deleteMenuItem);

        JMenuItem bringForward = new BringForwardItem(canvas, invoker).createMenuItem();
        bringForward.setFocusable(false);
        popupMenu.add(bringForward);

        JMenuItem sendBackward = new SendBackwardItem(canvas, invoker).createMenuItem();
        sendBackward.setFocusable(false);
        popupMenu.add(sendBackward);

        cutMenuItem.setEnabled(false);
        copyMenuItem.setEnabled(false);
        pasteMenuItem.setEnabled(false);
        deleteMenuItem.setEnabled(false);
        bringForward.setEnabled(false);
        sendBackward.setEnabled(false);

        canvas.addPropertyChangeListener("SELECTION", new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent propertyChangeEvent) {
                if (propertyChangeEvent.getNewValue() != null) {
                    cutMenuItem.setEnabled(true);
                    copyMenuItem.setEnabled(true);
                    deleteMenuItem.setEnabled(true);
                    bringForward.setEnabled(true);
                    sendBackward.setEnabled(true);
                } else {
                    cutMenuItem.setEnabled(false);
                    copyMenuItem.setEnabled(false);
                    deleteMenuItem.setEnabled(false);
                    bringForward.setEnabled(false);
                    sendBackward.setEnabled(false);
                }
            }
        });

        canvas.addPropertyChangeListener("CLIPBOARD_EMPTY", new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent propertyChangeEvent) {
                pasteMenuItem.setEnabled(!(boolean) propertyChangeEvent.getNewValue());
            }
        });

        return popupMenu;
    }

}