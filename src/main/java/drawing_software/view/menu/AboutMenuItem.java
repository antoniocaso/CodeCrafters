package drawing_software.view.menu;

import drawing_software.controller.command.Invoker;
import drawing_software.view.AboutDialog;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AboutMenuItem extends MenuItemFactory {

    public AboutMenuItem(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
    }

    @Override
    public JMenuItem createMenuItem() {
        JMenuItem aboutMenuItem = new JMenuItem("About");
        aboutMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                AboutDialog aboutDialog = new AboutDialog();
                aboutDialog.setVisible(true);
            }
        });
        return aboutMenuItem;
    }
}
