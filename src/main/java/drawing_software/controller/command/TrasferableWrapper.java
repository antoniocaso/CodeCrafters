package drawing_software.controller.command;

import drawing_software.model.Drawable;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;

/**
 * Allows to wrap the Drawable intended to be cut or copied so that the setContents()
 * method for the clipboard will accept it as an input parameter.
 */
public class TrasferableWrapper implements Transferable {
    private Drawable selectedShape;

    public TrasferableWrapper(Drawable selectedShape) {
        this.selectedShape = selectedShape;
    }

    @Override
    public DataFlavor[] getTransferDataFlavors() {
        return new DataFlavor[0];
    }

    @Override
    public boolean isDataFlavorSupported(DataFlavor flavor) {
        return false;
    }

    @Override
    public Drawable getTransferData(DataFlavor flavor) {
        return this.selectedShape;

    }

    public Drawable getSelectedShape() {
        return selectedShape;
    }

    public void setSelectedShape(Drawable selectedShape) {
        this.selectedShape = selectedShape;
    }


}

