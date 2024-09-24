package gruppo05;

import java.io.PrintWriter;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.io.*;

/**
 *
 * @author gruppo05
 */
public class GenerateOTP implements Runnable {

    @Override
    public void run() {
        while (!Thread.currentThread().isInterrupted()) {
            Random r = new Random();
            System.out.println("Genero nuovo OTP");
            String otpString = "Il codice di sblocco OTP è: " + String.valueOf(r.nextInt(500));
            try (PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("otp.txt")))) {
                out.print(otpString);
            } catch (IOException ex) {
                Logger.getLogger(GenerateOTP.class.getName()).log(Level.SEVERE, null, ex);
            }

            try {
                Thread.sleep(10000);
            } catch (InterruptedException ex) {
                return;

            }

        }
    }

}
