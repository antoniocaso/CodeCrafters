/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXML2.java to edit this template
 */
package gruppo05;

import java.net.URL;
import java.util.Optional;
import java.util.ResourceBundle;
import javafx.application.Platform;
import javafx.beans.binding.Bindings;
import javafx.beans.binding.BooleanBinding;
import javafx.beans.property.ListProperty;
import javafx.beans.property.SimpleListProperty;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import java.io.*;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.function.UnaryOperator;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.collections.ObservableList;
import javafx.scene.control.PasswordField;
import javafx.scene.control.SplitPane;
import javafx.scene.control.TextFormatter;
import javafx.scene.control.TextFormatter.Change;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.scene.input.Clipboard;
import javafx.scene.input.ClipboardContent;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.input.KeyCode;
/**
 *
 * @author gruppo05
 */
public class FXMLDocumentController implements Initializable {

    @FXML
    private MenuBar menuBar;
    @FXML
    private MenuItem menuItemSalva;
    @FXML
    private MenuItem menuItemEsci;
    @FXML
    private TextField txtFieldNome;
    @FXML
    private Button btnAggiungiContatto;
    @FXML
    private TableView<Contact> tableView;
    @FXML
    private TableColumn<Contact, String> clmNome;
    @FXML
    private TableColumn<Contact, String> clmCognome;
    @FXML
    private TableColumn<Contact, String> clmNumeroTelefonico;
    @FXML
    private PasswordField txtFieldOTP;
    @FXML
    private Button btnSblocca;
    @FXML
    private Label lblPasswordError;
    @FXML
    private TextField txtFieldCognome;
    @FXML
    private TextField txtFieldNumeroTelefonico;
    @FXML
    private AnchorPane lockScreen;
    
    @FXML
    private SplitPane mainScreen;

    private ListProperty list;

    private Alert alert = new Alert(AlertType.ERROR);

    private final Clipboard clipboard = Clipboard.getSystemClipboard();
    
    private ListProperty backupList;
        
    private Thread threadOTP; 

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
        /* OTP */
        
        lockScreen.setVisible(true);
        
        threadOTP = new Thread(new GenerateOTP());
        threadOTP.setDaemon(true);
        threadOTP.start();
        
        
        btnSblocca.disableProperty().bind(txtFieldOTP.textProperty().isEmpty());
                
        ArrayList<Contact> readList = null;
        
        try (ObjectInputStream in = new ObjectInputStream(new BufferedInputStream(new FileInputStream("saved.bin")))) {
            readList = (ArrayList<Contact>) in.readObject();
        } catch (FileNotFoundException e) {
            File f = new File("saved.bin");
            try {
                f.createNewFile();
            } catch (IOException ex) {
                Logger.getLogger(FXMLDocumentController.class.getName()).log(Level.SEVERE, null, ex);
            }
        } catch(IOException e){
            System.err.println(e);
        } catch(ClassNotFoundException e){
            System.err.println(e);
        }


        if (readList == null) {
            list = new SimpleListProperty(FXCollections.observableArrayList());
        } else {
            list = new SimpleListProperty(FXCollections.observableArrayList(readList));
        }

        clmNome.setCellValueFactory(new PropertyValueFactory("nome"));
        clmCognome.setCellValueFactory(new PropertyValueFactory("cognome"));
        clmNumeroTelefonico.setCellValueFactory(new PropertyValueFactory("numero"));

        clmNome.setCellFactory(TextFieldTableCell.forTableColumn());
        clmCognome.setCellFactory(TextFieldTableCell.forTableColumn());
        clmNumeroTelefonico.setCellFactory(TextFieldTableCell.forTableColumn());

        txtFieldNumeroTelefonico.setTextFormatter(new TextFormatter((UnaryOperator<Change>) c -> {
            return c.getControlNewText().matches("\\d+") || c.getControlNewText().isEmpty() ? c : null; // DA SISTEMARE
        }));
        
        tableView.setItems(list);

        BooleanBinding b1 = Bindings.or(txtFieldCognome.textProperty().isEmpty(), txtFieldNumeroTelefonico.textProperty().isEmpty());
        BooleanBinding b = Bindings.or(txtFieldNome.textProperty().isEmpty(), b1);
        btnAggiungiContatto.disableProperty().bind(b);

        alert.setContentText("Contatto già presente.");
        
        
        //menuItemSalva.disableProperty().bind(list.isEqualTo(backupList));
        
        
    }

    @FXML
    private void addContact(ActionEvent event) {
        Contact c = new Contact(txtFieldNome.getText(), txtFieldCognome.getText(), txtFieldNumeroTelefonico.getText());
        if (list.contains(c)) {
            Optional<ButtonType> result = alert.showAndWait();
        } else {
            list.add(c);
            txtFieldNome.clear();
            txtFieldCognome.clear();
            txtFieldNumeroTelefonico.clear();
        }

    }

    @FXML
    private void unlockPhoneBook(ActionEvent event) {
        try(Scanner in = new Scanner(new BufferedReader(new FileReader("otp.txt")))){
            
            String otp = in.nextLine().substring(28);
            if(txtFieldOTP.getText().equals(otp)){
                lblPasswordError.setVisible(false);
                lockScreen.setVisible(false);
                mainScreen.setVisible(true);
                threadOTP.interrupt();
            }else{
                lblPasswordError.setVisible(true);
            }
        } catch(FileNotFoundException ex ){
            
        }
    }

    @FXML
    private void saveFile(ActionEvent event) {
        try (ObjectOutputStream out = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream("saved.bin")))) {
            backupList = new SimpleListProperty(list);
            out.writeObject(new ArrayList<>(list));
        } catch (Exception ex) {
            Logger.getLogger(FXMLDocumentController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @FXML
    private void exitApplication(ActionEvent event) {
        Platform.exit();
    }

    @FXML
    private void deleteContact(ActionEvent event) {
        Contact c = tableView.getSelectionModel().getSelectedItem();
        list.remove(c);
    }

    @FXML
    private void copyContact(ActionEvent event) {
        Contact c = tableView.getSelectionModel().getSelectedItem();
        ClipboardContent content = new ClipboardContent();
        content.putString(String.join(";", c.getCognome(), c.getNome(), c.getNumero()) + ";");
        clipboard.setContent(content);
    }

    @FXML
    private void editNome(TableColumn.CellEditEvent<Contact, String> event) {
        Contact selected = tableView.getSelectionModel().getSelectedItem();
        Contact c = new Contact(event.getNewValue(), selected.getCognome(), selected.getNumero());
        if (list.contains(c)) {
            Optional<ButtonType> result = alert.showAndWait();
            selected.setNome(event.getOldValue());
        } else {
            selected.setNome(event.getNewValue());
        }
    }

    @FXML
    private void editCognome(TableColumn.CellEditEvent<Contact, String> event) {
        Contact selected = tableView.getSelectionModel().getSelectedItem();
        
        Contact c = new Contact(selected.getNome(), event.getNewValue(), selected.getNumero());
        if (list.contains(c)) {
            Optional<ButtonType> result = alert.showAndWait();
            selected.setCognome(event.getOldValue());
        } else {
            selected.setCognome(event.getNewValue());
        }
    }

    @FXML
    private void editNumeroTelefonico(TableColumn.CellEditEvent<Contact, String> event) {
        Contact selected = tableView.getSelectionModel().getSelectedItem();
           Contact c = new Contact(selected.getNome(), selected.getCognome(), event.getNewValue());
        if (list.contains(c)) {
            Optional<ButtonType> result = alert.showAndWait();
            selected.setNumero(event.getOldValue());
        } else {
            selected.setNumero(event.getNewValue());
        }
    }
    
    /* Accetta invio per inserimento OTP */
    @FXML
    private void pressed(KeyEvent event){
        if(event.getCode() == KeyCode.ENTER){
             try(Scanner in = new Scanner(new BufferedReader(new FileReader("otp.txt")))){
            
            String otp = in.nextLine().substring(28);
            if(txtFieldOTP.getText().equals(otp)){
                lblPasswordError.setVisible(false);
                lockScreen.setVisible(false);
                mainScreen.setVisible(true);
                threadOTP.interrupt();
            }else{
                lblPasswordError.setVisible(true);
            }
        } catch(FileNotFoundException ex ){
            
        }
        }
            
    }
    
}
