package drawing_software;

import com.formdev.flatlaf.FlatDarkLaf;
import com.formdev.flatlaf.util.SystemInfo;
import drawing_software.controller.WindowController;

import javax.swing.*;
import java.util.logging.Level;
import java.util.logging.Logger;
public class Main {
    public static final String appTitle = "Drawing software";

    /**
     * Sets custom properties for MacOS devices.
     * Sets the FlatDarkLaf look&feel.
     *
     * @param args
     */
    public static void main(String[] args) {
        if (SystemInfo.isMacOS) {
            System.setProperty("apple.laf.useScreenMenuBar", "true");
            System.setProperty("apple.awt.application.name", appTitle);
            System.setProperty("com.apple.mrj.application.apple.menu.about.name", appTitle);
            System.setProperty("apple.awt.application.appearance", "system");
        }
        FlatDarkLaf.setup();
        SwingUtilities.invokeLater(() -> {
            Logger logger = Logger.getLogger("root");
            logger.setLevel(Level.ALL);
            WindowController windowController = new WindowController(appTitle);
        });
    }
}