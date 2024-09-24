# Software Architecture
Java is used to create the drawing software, while the GUI will be created using the Swing library and the primitives of the AWT library will be used to render the geometric figures.
Although Swing does not natively implement the MVC architectural pattern, the graphical interface will be decoupled from the implementation of the features it offers.

One of the main classes that will be implemented is the CanvasPanel class, which abstracts the worksheet. The latter extends the JPanel class and will have the task of rendering the drawing (built by the user) through the paintComponent method, which is inherited from the JPanel class. The CanvasPanel class will hold a reference to a data structure that contains all the pictures that the user has chosen to insert. At each call to the paintComponent method, the visible area will be emptied and each figure of the data structure will be drawn using the reference to an object of the Graphics2D class.

Most of the features that will add or modify geometrical figures will be classes that implement the Command interface so as to apply the homonymous pattern. In this way it will be possible both to easily implement the undo function and to recall the same command in several points, for example from a sidebar of buttons or with a shortcut.

AWT library listeners objects will be used to capture user input.