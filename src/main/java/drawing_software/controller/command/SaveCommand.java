package drawing_software.controller.command;

import drawing_software.view.Window;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

/**
 * Encapsulates the saving logic by implementing the ConcreteCommand save.
 */
public class SaveCommand implements Command {

    private final Window window;
    private final File file;

    /**
     * Allows the ConcreteCommand object to have a reference to the
     * receiver.
     *
     * @param window is the reference to the receiver which will perform the required action.
     * @param file   is the file to be saved.
     */
    public SaveCommand(Window window, File file) {
        this.window = window;
        this.file = file;
    }


    /**
     * Saves the current drawing inside the file.
     * Updates currentFile property.
     * The operation is completed by firing a PropertyChange that sets the MODIFIED property to false.
     */
    @Override
    public void execute() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file))) {
            window.setCurrentFile(file);
            window.getCanvas().firePropertyChange("MODIFIED", true, false);
            oos.writeObject(window.getCanvas().getDrawing());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

}