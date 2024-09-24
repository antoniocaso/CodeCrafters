package controller;

import drawing_software.controller.command.Command;
import drawing_software.controller.command.Invoker;
import drawing_software.controller.command.LoadCommand;
import drawing_software.controller.command.SaveCommand;
import drawing_software.model.*;
import drawing_software.view.Canvas;
import drawing_software.view.Window;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.awt.geom.Point2D;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.LinkedList;
import java.util.List;

import static org.junit.Assert.assertEquals;

public class LoadCommandTest {

    private Canvas canvas;

    private File file;

    private Command loadCommand;

    private Invoker invoker;

    private Window window;

    @Before
    public void setUp() {
        window = new Window("title");
        invoker = new Invoker();


        window.getCanvas().getDrawing().addDrawable(new DrawableRectangle(1, 1));
        window.getCanvas().getDrawing().addDrawable(new DrawableEllipse(4, 3));
        window.getCanvas().getDrawing().addDrawable(new DrawableLine(new Point2D.Double(10, 4), new Point2D.Double(20, 8)));

        file = new File("./testfile.draw");
        new SaveCommand(window, file).execute();

        loadCommand = new LoadCommand(window, file);
    }

    @Test
    public void testExecute() {
        window.getCanvas().setDrawing(new Drawing());
        loadCommand.execute();
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file))) {
            Drawing saved = (Drawing) ois.readObject();
            List<Drawable> savedList = new LinkedList<>();
            for (Drawable d : saved) {
                savedList.add(d);
            }

            List<Drawable> current = new LinkedList<>();
            for (Drawable d : window.getCanvas().getDrawing()) {
                current.add(d);
            }

            assertEquals(savedList, current);

        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    @After
    public void tearDown() {
        file.delete();
    }

}