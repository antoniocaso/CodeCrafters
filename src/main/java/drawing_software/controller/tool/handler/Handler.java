package drawing_software.controller.tool.handler;


import drawing_software.controller.tool.MouseRequest;
import drawing_software.view.Canvas;

/**
 * Provides a common interface to all the concrete Handlers. These classes are meant to process
 * the interaction of the user when using the selection tool and act accordingly to the sequence of actions.
 */
public abstract class Handler {

    protected Handler nextHandler;

    protected Canvas canvas;

    public Handler(Canvas canvas) {
        this.canvas = canvas;
    }

    /**
     * Processes a pressing event.
     *
     * @param request the request to be processed
     */
    abstract void handlePressed(MouseRequest request);

    /**
     * Processes a dragging event.
     *
     * @param request the request to be processed
     */
    abstract void handleDragged(MouseRequest request);

    void setNext(Handler next) {
        this.nextHandler = next;
    }
}
