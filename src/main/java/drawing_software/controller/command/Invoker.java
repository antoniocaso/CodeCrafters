package drawing_software.controller.command;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Invoker class of the Command pattern. Through this class, ConcreteCommand can
 * be carried out by the receiver and it can be undone (if the undo method is provided).
 */
public class Invoker {

    private final Deque<Undoable> commands = new ArrayDeque<>();

    private final PropertyChangeSupport changes = new PropertyChangeSupport(this);

    /**
     * Allows the invoker to call for the execution of a command given as
     * an input parameter. If the command implements the Undo interface, it is
     * stored inside the "commands" stack, then it notifies that the stack is no more empty.
     *
     * @param command is the command to be executed by the receiver, and is
     *                given by the Client classed who want that command to be executed.
     */
    public void executeCommand(Command command) {
        if (command instanceof Undoable undoable) {
            commands.offerLast(undoable);
            changes.firePropertyChange("IS_INVOKER_EMPTY", true, false);
        }
        command.execute();
    }

    /**
     * Removes an undoable command from the stack and calls the undo method. When
     * the stack is empty, it notifies its subscribers, so that the undo menu item is disabled.
     */
    public void undoLastCommand() {
        Undoable last = commands.pollLast();
        if (last != null) {
            last.undo();
        }
        if (commands.isEmpty()) {
            changes.firePropertyChange("IS_INVOKER_EMPTY", false, true);
        }

    }

    public void addPropertyChangeListener(PropertyChangeListener listener) {
        changes.addPropertyChangeListener(listener);
    }

    public void removePropertyChangeListener(PropertyChangeListener listener) {
        changes.removePropertyChangeListener(listener);
    }

}
