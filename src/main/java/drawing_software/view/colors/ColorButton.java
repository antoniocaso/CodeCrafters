package drawing_software.view.colors;

import javax.swing.*;
import javax.swing.plaf.basic.BasicButtonUI;
import java.awt.*;

public class ColorButton extends JButton {

    private final ColorButtonUI buttonUI;

    public ColorButton(Color color) {
        super();
        this.setPreferredSize(new Dimension(30, 30));
        buttonUI = new ColorButtonUI(color);
        this.setUI(buttonUI);
    }

    /**
     * Updates the ButtonUI by changing the color.
     *
     * @param color selected color
     */
    public void changeColor(Color color) {
        buttonUI.setColor(color);
    }

    /**
     * Defines a custom UI for ColorButtons. It will show a squared button with
     * the selected color.
     */
    private class ColorButtonUI extends BasicButtonUI {

        public Color getColor() {
            return color;
        }

        public void setColor(Color color) {
            this.color = color;
            repaint();
        }

        private Color color;

        ColorButtonUI(Color color) {
            this.color = color;
        }

        @Override
        public void paint(Graphics g, JComponent c) {
            g.setColor(color);
            g.fill3DRect(0, 0, c.getWidth(), c.getHeight(), true);
            super.paint(g, c);
        }
    }
}
