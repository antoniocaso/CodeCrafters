package drawing_software.view.menu;

import drawing_software.Main;
import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;
import drawing_software.view.Window;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Logger;

public class ExitMenuItem extends MenuItemFactory {
    private Window window;

    public ExitMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    public ExitMenuItem(Window window, Invoker invoker) {
        super(window.getCanvas(), invoker);
        this.window = window;
    }

    @Override
    public JMenuItem createMenuItem() {
        JMenuItem exitMenuItem = new JMenuItem("Exit");
        exitMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
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

        return exitMenuItem;
    }

}
