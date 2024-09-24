package drawing_software.view.colors;

import drawing_software.controller.command.FillCommand;
import drawing_software.controller.command.Invoker;
import drawing_software.view.Canvas;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FillPanel extends ColorPanelFactory implements ActionListener {

    public FillPanel(Canvas canvas, Invoker invoker) {
        super(canvas, invoker);
        this.setLayout(new FlowLayout());
        this.button = new ColorButton(null);
        this.add(new JLabel("Fill: "));
        this.button.setName("fill");
        this.button.changeColor(canvas.getCurrentFillColor());
        this.button.addActionListener(this);
        this.add(this.button);
    }


    /**
     * Shows to the user the color chooser, executes FillCommand with the color selected by
     * the user and updates the ColorButton accordingly.
     *
     * @param actionEvent the event to be processed
     */
    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        ColorButton source = (ColorButton) actionEvent.getSource();
        Color firstColor = canvas.getCurrentFillColor();
        Color color = JColorChooser.showDialog(canvas, "Select color", firstColor);
        invoker.executeCommand(new FillCommand(canvas, color));
        source.changeColor(color);
    }
}
