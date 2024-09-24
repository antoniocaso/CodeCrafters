package drawing_software.controller;

import drawing_software.Main;
import drawing_software.controller.tool.LineTool;
import drawing_software.controller.tool.SelectionTool;
import drawing_software.model.SelectionGrid;
import drawing_software.model.Shape;
import drawing_software.view.Window;
import drawing_software.view.menu.SaveMenuItem;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.logging.Logger;

/**
 * Implements the business logic for the Window view.
 */
public class WindowController {
    private final Window window;

    /**
     * Creates the window and sets all its properties.
     * Adds a window listener for the WindowClosing event. Thanks to this, it will prevent an unsaved exit.
     * <p>
     * Adds a new Property Change Listener to the invoker for the undo logic.
     * <p>
     * Adds a new PropertyChangeListener to the canvas. This is used for enabling and disabling the menuItems accordingly to
     * the current state of the program.
     * When there's no selected shape, all the menu items(except for the paste one) will be disabled; otherwise it will enable them.
     * When the clipboard is empty, the paste menu item will be disabled; otherwise it will enable it.
     * <p>
     * Adds a new PropertyChangeListener to the canvas. This is used for enabling and disabling
     * the CheckBox (used for the Fixed Resize) and the FillColor button.
     * When the current tool is SelectionTool, it enables the checkbox; otherwise it will disable it.
     * When the current tool is LineTool, it enables the FillColor button; otherwise it will disable it.
     * <p>
     * Adds a new PropertyChangeListener to the canvas. This is used for updating the title with the "*" mark
     * in case of modifies.
     *
     * @param appTitle title of the application
     */
    public WindowController(String appTitle) {
        window = new Window(appTitle);
        window.setSize(1280, 720);
        window.setLocationRelativeTo(null);
        window.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent windowEvent) {
                //check if modified
                Logger.getLogger("root").info("Closing...");
                if (window.isModified()) {
                    String title;
                    if (window.getCurrentFile() == null) {
                        title = "untitled";
                    } else {
                        title = window.getCurrentFile().getName();
                    }
                    String message = "Do you want to save changes to " + title + " ? ";

                    int confirmed = JOptionPane.showConfirmDialog(null,
                            message, Main.appTitle,
                            JOptionPane.YES_NO_CANCEL_OPTION);

                    if (confirmed == JOptionPane.YES_OPTION) {
                        new SaveMenuItem(window, window.getInvoker()).actionPerformed(null);
                    }
                    if (confirmed == JOptionPane.CANCEL_OPTION) {
                        return;
                    }
                }
                window.dispose();
            }
        });

        window.setFocusable(false);
        window.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        window.setVisible(true);


        setCheckBoxScaleVisible(false);
        setCutMenuItemEnabled(false);
        setCopyMenuItemEnabled(false);
        setPasteMenuItemEnabled(false);
        setDeleteMenuItemEnabled(false);
        setUndoItemEnabled(false);


        window.getInvoker().addPropertyChangeListener(new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent propertyChangeEvent) {
                // se è vuoto
                setUndoItemEnabled(!((boolean) propertyChangeEvent.getNewValue()));
            }
        });
        window.getCanvas().addPropertyChangeListener("SELECTION", new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent propertyChangeEvent) {
                // c'è un oggetto selezionato
                if (propertyChangeEvent.getNewValue() != null) {
                    Shape selected = ((SelectionGrid) propertyChangeEvent.getNewValue()).getSelectedShape();
                    setCutMenuItemEnabled(true);
                    setCopyMenuItemEnabled(true);
                    setDeleteMenuItemEnabled(true);
                    setFillPanelColor((Color) selected.getFillColor());
                    setStrokePanelColor((Color) selected.getStrokeColor());
                } else {
                    setCutMenuItemEnabled(false);
                    setCopyMenuItemEnabled(false);
                    setDeleteMenuItemEnabled(false);
                    setFillPanelColor(window.getCanvas().getCurrentFillColor());
                    setStrokePanelColor(window.getCanvas().getCurrentStrokeColor());
                }
            }
        });

        window.getCanvas().addPropertyChangeListener("CURRENT_TOOL", new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent propertyChangeEvent) {
                setCheckBoxScaleVisible(propertyChangeEvent.getNewValue() instanceof SelectionTool);
                setFillPanelEnabled(!(propertyChangeEvent.getNewValue() instanceof LineTool));
            }
        });

        window.getCanvas().addPropertyChangeListener("MODIFIED", new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent propertyChangeEvent) {
                window.setModified((boolean) propertyChangeEvent.getNewValue());
                String title;
                if (window.getCurrentFile() == null) {
                    title = "untitled";
                } else {
                    title = window.getCurrentFile().getName();
                }
                if (window.isModified()) {
                    window.setTitle(title + " * - " + Main.appTitle);
                } else {
                    window.setTitle(title + " - " + Main.appTitle);
                }
            }
        });
        window.getCanvas().addPropertyChangeListener("CLIPBOARD_EMPTY", new PropertyChangeListener() {
            @Override
            public void propertyChange(PropertyChangeEvent propertyChangeEvent) {
                setPasteMenuItemEnabled(!(boolean) propertyChangeEvent.getNewValue());
            }
        });
    }

    public void setFrameTitle(String title) {
        window.setTitle(title);
    }

    public void setFillPanelEnabled(boolean state) {
        window.getFillPanel().getButton().setEnabled(state);
    }

    public void setStrokePanelEnabled(boolean state) {
        window.getStrokePanel().getButton().setEnabled(state);
    }

    public void setCheckBoxScaleVisible(boolean state) {
        window.getCheckBoxScale().setVisible(state);
    }

    public void setCutMenuItemEnabled(boolean state) {
        window.getCutMenuItem().setEnabled(state);
    }

    public void setCopyMenuItemEnabled(boolean state) {
        window.getCopyMenuItem().setEnabled(state);
    }

    public void setPasteMenuItemEnabled(boolean state) {
        window.getPasteMenuItem().setEnabled(state);
    }

    public void setDeleteMenuItemEnabled(boolean state) {
        window.getDeleteMenuItem().setEnabled(state);
    }

    public void setUndoItemEnabled(boolean state) {
        window.getUndoMenuItem().setEnabled(state);
    }

    public void setFillPanelColor(Color color) {
        window.getFillPanel().getButton().changeColor(color);
    }

    public void setStrokePanelColor(Color color) {
        window.getStrokePanel().getButton().changeColor(color);
    }

}

