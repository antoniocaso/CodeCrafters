package drawing_software.view;

import drawing_software.controller.CanvasController;
import drawing_software.controller.command.Invoker;
import drawing_software.view.colors.FillPanel;
import drawing_software.view.colors.StrokePanel;
import drawing_software.view.menu.*;
import drawing_software.view.toolbar.EllipseToolbarItem;
import drawing_software.view.toolbar.LineToolbarItem;
import drawing_software.view.toolbar.RectangleToolbarItem;
import drawing_software.view.toolbar.SelectionToolbarItem;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ItemEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseWheelEvent;
import java.io.File;
import java.net.URL;

/**
 * The main window
 */
public class Window extends JFrame {
    private final Invoker invoker;
    private final Canvas canvas;
    private final FillPanel fillPanel;
    private final StrokePanel strokePanel;
    private final JCheckBox checkBoxScale;

    private JMenuItem cutMenuItem;
    private JMenuItem copyMenuItem;
    private JMenuItem pasteMenuItem;
    private JMenuItem deleteMenuItem;
    private JMenuItem undoMenuItem;

    private final static int whiteIntensity = 230;

    private File currentFile;
    private boolean modified = false;

    /**
     * Creates the JFrame and sets all its properties.
     * Creates a new canvas and the canvas controller.
     * <p>
     * Adds the scrollpane to the window.
     * The mouseWheelMoved event checks if the CTRL key button is pressed while the mouseWheel scrolls;
     * in that case it resizes the canvas; otherwise it acts normally and scrolls the canvas.
     * <p>
     * Adds the toolbar with all the tools.
     * <p>
     * Adds the bottom panel containing the Fill and Stroke buttons, the respective labels and the checkbox used for the fixed resize.
     * <p>
     * Adds the menubar with all the menu items.
     *
     * @param appTitle the title of the application
     */
    public Window(String appTitle) {
        super("untitled - " + appTitle);
        invoker = new Invoker();
        this.setFocusable(false);
        this.setBackground(new Color(whiteIntensity, whiteIntensity, whiteIntensity));
        canvas = new Canvas(invoker);
        new CanvasController(canvas);
        canvas.setFocusable(true);

        JScrollPane scrollPane = new JScrollPane(canvas);

        scrollPane.addMouseWheelListener(new MouseAdapter() {
            @Override
            public void mouseWheelMoved(MouseWheelEvent e) {

                if (e.isControlDown()) {
                    scrollPane.setWheelScrollingEnabled(false);
                    int scaleFactor = canvas.getScaleFactor();

                    canvas.setScalePoint(e.getPoint());
                    if (e.getWheelRotation() < 0 && scaleFactor < 18) {
                        scaleFactor += 1;
                    } else if (e.getWheelRotation() > 0 && scaleFactor > 2) {
                        scaleFactor -= 1;
                    }

                    canvas.setScaleFactor(scaleFactor);
                    canvas.repaint();

                } else {
                    scrollPane.setWheelScrollingEnabled(true);
                }

            }
        });

        /* ToolBar */

        JToolBar toolBar = createToolBar(canvas, invoker);
        toolBar.setFocusable(false);
        this.add(toolBar, BorderLayout.WEST);



        /* BottomPanel */

        JPanel bottomPanel = new JPanel();
        fillPanel = new FillPanel(canvas, invoker);
        bottomPanel.add(fillPanel);
        strokePanel = new StrokePanel(canvas, invoker);
        bottomPanel.add(strokePanel);
        bottomPanel.add(Box.createHorizontalStrut(50));


        checkBoxScale = new JCheckBox("Fixed proportions");
        checkBoxScale.addItemListener(e -> {
            canvas.setFixedResize(e.getStateChange() == ItemEvent.SELECTED);
        });
        bottomPanel.add(checkBoxScale);


        this.add(bottomPanel, BorderLayout.SOUTH);



        /* MenuBar */

        JMenuBar menuBar = createMenuBar(canvas, invoker);
        menuBar.setFocusable(false);
        this.setJMenuBar(menuBar);


        this.add(scrollPane);
        /* Icon */

        URL url = Window.class.getResource("/icon.png");
        ImageIcon icon = new ImageIcon(url);
        this.setIconImage(icon.getImage());

    }

    /**
     * Creates the menu bar and adds to it all the MenuItems.
     *
     * @param canvas  canvas
     * @param invoker invoker
     * @return
     */
    private JMenuBar createMenuBar(Canvas canvas, Invoker invoker) {
        JMenuBar menuBar = new JMenuBar();
        menuBar.setFocusable(false);

        /* File Menu */

        JMenu fileMenu = new JMenu("File");
        fileMenu.setFocusable(false);

        JMenuItem newMenuItem = new NewMenuItem(this, invoker).createMenuItem();
        newMenuItem.setFocusable(false);
        fileMenu.add(newMenuItem);

        JMenuItem loadMenuItem = new LoadMenuItem(this, invoker).createMenuItem();
        loadMenuItem.setFocusable(false);
        fileMenu.add(loadMenuItem);

        JMenuItem saveMenuItem = new SaveMenuItem(this, invoker).createMenuItem();
        saveMenuItem.setFocusable(false);
        fileMenu.add(saveMenuItem);

        JMenuItem saveAsMenuItem = new SaveAsMenuItem(this, invoker).createMenuItem();
        saveAsMenuItem.setFocusable(false);
        fileMenu.add(saveAsMenuItem);

        JMenuItem exitMenuItem = new ExitMenuItem(this, invoker).createMenuItem();
        saveAsMenuItem.setFocusable(false);
        fileMenu.add(exitMenuItem);

        menuBar.add(fileMenu);



        /* Edit Menu */

        JMenu editMenu = new JMenu("Edit");
        editMenu.setFocusable(false);

        cutMenuItem = new CutMenuItem(canvas, invoker).createMenuItem();
        cutMenuItem.setFocusable(false);
        editMenu.add(cutMenuItem);

        copyMenuItem = new CopyMenuItem(canvas, invoker).createMenuItem();
        copyMenuItem.setFocusable(false);
        editMenu.add(copyMenuItem);

        pasteMenuItem = new PasteMenuItem(canvas, invoker).createMenuItem();
        pasteMenuItem.setFocusable(false);
        editMenu.add(pasteMenuItem);

        deleteMenuItem = new DeleteMenuItem(canvas, invoker).createMenuItem();
        deleteMenuItem.setFocusable(false);
        editMenu.add(deleteMenuItem);

        undoMenuItem = new UndoMenuItem(canvas, invoker).createMenuItem();
        deleteMenuItem.setFocusable(false);
        editMenu.add(undoMenuItem);

        menuBar.add(editMenu);

        JMenu viewMenu = new JMenu("View");
        viewMenu.setFocusable(false);

        JMenuItem showGridMenuItem = new ShowGridMenuItem(canvas, invoker).createMenuItem();
        showGridMenuItem.setFocusable(false);
        viewMenu.add(showGridMenuItem);

        JMenuItem increaseGridSizeMenuItem = new IncreaseGridSizeMenuItem(canvas, invoker).createMenuItem();
        increaseGridSizeMenuItem.setFocusable(false);
        viewMenu.add(increaseGridSizeMenuItem);

        JMenuItem decreaseGridSizeMenuItem = new DecreaseGridSizeMenuItem(canvas, invoker).createMenuItem();
        decreaseGridSizeMenuItem.setFocusable(false);
        viewMenu.add(decreaseGridSizeMenuItem);

        menuBar.add(viewMenu);

        JMenu helpMenu = new JMenu("Help");
        helpMenu.setFocusable(false);

        JMenuItem aboutMenuItem = new AboutMenuItem(canvas, invoker).createMenuItem();
        aboutMenuItem.setFocusable(false);
        helpMenu.add(aboutMenuItem);

        menuBar.add(helpMenu);

        return menuBar;
    }


    private static JToolBar createToolBar(Canvas canvas, Invoker invoker) {
        JToolBar toolPanel = new JToolBar(JToolBar.VERTICAL);
        toolPanel.setFocusable(false);
        toolPanel.setFloatable(false);

        BoxLayout layout = new BoxLayout(toolPanel, BoxLayout.PAGE_AXIS);
        toolPanel.setLayout(layout);

        ButtonGroup group = new ButtonGroup();

        JToggleButton selectionButton = new SelectionToolbarItem(canvas, invoker).itemCreate();
        selectionButton.setFocusable(false);
        group.add(selectionButton);
        toolPanel.add(selectionButton);

        JToggleButton lineButton = new LineToolbarItem(canvas, invoker).itemCreate();
        lineButton.setFocusable(false);
        group.add(lineButton);
        toolPanel.add(lineButton);

        JToggleButton rectangleButton = new RectangleToolbarItem(canvas, invoker).itemCreate();
        rectangleButton.setFocusable(false);
        group.add(rectangleButton);
        toolPanel.add(rectangleButton);

        JToggleButton ellipseButton = new EllipseToolbarItem(canvas, invoker).itemCreate();
        ellipseButton.setFocusable(false);
        group.add(ellipseButton);
        toolPanel.add(ellipseButton);

        return toolPanel;
    }

    public Invoker getInvoker() {
        return invoker;
    }

    public Canvas getCanvas() {
        return canvas;
    }

    public FillPanel getFillPanel() {
        return fillPanel;
    }

    public StrokePanel getStrokePanel() {
        return strokePanel;
    }

    public JCheckBox getCheckBoxScale() {
        return checkBoxScale;
    }

    public JMenuItem getCutMenuItem() {
        return cutMenuItem;
    }

    public JMenuItem getCopyMenuItem() {
        return copyMenuItem;
    }

    public JMenuItem getPasteMenuItem() {
        return pasteMenuItem;
    }

    public JMenuItem getDeleteMenuItem() {
        return deleteMenuItem;
    }

    public JMenuItem getUndoMenuItem() {
        return undoMenuItem;
    }

    public File getCurrentFile() {
        return currentFile;
    }

    public void setCurrentFile(File currentFile) {
        this.currentFile = currentFile;
    }

    public boolean isModified() {
        return modified;
    }

    public void setModified(boolean modified) {
        this.modified = modified;
    }
}
