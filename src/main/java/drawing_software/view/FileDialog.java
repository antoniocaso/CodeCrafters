package drawing_software.view;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;

/**
 * Factory class for file dialogs.
 */
public class FileDialog {
    private final JFileChooser chooser;
    public static final int OPEN_DIALOG = 1;
    public static final int SAVE_DIALOG = 2;

    public FileDialog() {
        chooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter("Drawing file", "draw");
        chooser.addChoosableFileFilter(filter);
    }

    /**
     * Shows a file dialog, depending on the type parameter, and implements logic
     * for checking the file extension.
     *
     * @param parent the Component where the dialog will be added
     * @param type   OPEN_DIALOG or SAVE_DIALOG
     * @return the file selected by the user
     * @throws FileNotFoundException
     * @throws IllegalArgumentException
     */
    public File show(Component parent, int type) throws FileNotFoundException, IllegalArgumentException {
        int returnVal;
        if (type == OPEN_DIALOG) {
            returnVal = chooser.showOpenDialog(parent);
        } else if (type == SAVE_DIALOG) {
            returnVal = chooser.showSaveDialog(parent);
        } else {
            throw new IllegalArgumentException("Invalid type of dialog");
        }

        if (returnVal == JFileChooser.APPROVE_OPTION) {
            String fileName = chooser.getSelectedFile().toString();
            if (fileName.endsWith(".draw")) {
                return new File(fileName);
            } else {
                return new File(fileName + ".draw");
            }
        }

        throw new FileNotFoundException();
    }

}
