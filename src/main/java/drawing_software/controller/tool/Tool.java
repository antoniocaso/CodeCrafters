package drawing_software.controller.tool;

import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

/**
 * This interface defines the behaviour of the Canvas.
 * It corresponds to the "State" Interface of the State Pattern.
 */
public interface Tool {

    default void mouseLeftPressed(MouseEvent mouseEvent) {

    }

    default void mouseRightPressed(MouseEvent mouseEvent) {

    }

    default void mouseDragged(MouseEvent mouseEvent) {

    }

    default void mouseReleased(MouseEvent mouseEvent) {

    }

    default void mouseLeftClicked(MouseEvent mouseEvent) {

    }

    default void mouseRightClicked(MouseEvent mouseEvent) {

    }

    default void keyPressed(KeyEvent keyEvent) {

    }

}
