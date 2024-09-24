package drawing_software.controller.command;

import drawing_software.model.Drawing;
import drawing_software.view.Window;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

/**
 * Implements a ConcreteCommand class; in this case, the Command is the Load command.
 */
public class LoadCommand implements Command {

    private final Window window;
    private final File file;

    /**
     * Allows the ConcreteCommand object to have a reference to the
     * receiver.
     *
     * @param window is the reference to the receiver which will perform the required action.
     * @param file   is the file to be loaded.
     */
    public LoadCommand(Window window, File file) {
        this.window = window;
        this.file = file;
    }

    /**
     * Opens the previously selected file .
     * Adds the shapes contained in the file to the Drawing data structure
     * and then repaints the canvas in order to show such drawn shapes.
     * Updates currentFile property.
     * The operation is completed by firing a PropertyChange that sets the MODIFIED property to false.
     */
    @Override
    public void execute() {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file))) {
            window.getCanvas().setDrawing((Drawing) ois.readObject());
            window.setCurrentFile(file);
            window.getCanvas().firePropertyChange("MODIFIED", true, false);
            window.getCanvas().repaint();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

    }

}