package drawing_software.controller.command;

/**
 * Represents the contract for the undo functionality. Every class implementing
 * this interface represents a command which can be canceled.
 */
interface Undoable {
    void undo();
}
