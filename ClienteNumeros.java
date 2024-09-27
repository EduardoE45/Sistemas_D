// ClienteNumeros.java
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class ClienteNumeros {
    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("127.0.0.1", 5001);
        DataOutputStream out = new DataOutputStream(socket.getOutputStream());
        DataInputStream in = new DataInputStream(socket.getInputStream());
        Scanner scanner = new Scanner(System.in);

        int numero;
        do {
            System.out.print("Introduce un número (0 para salir): ");
            numero = scanner.nextInt();
            out.writeInt(numero); // Enviar número

            if (numero != 0) {
                int respuesta = in.readInt(); // Leer respuesta del servidor
                System.out.println("El servidor respondió con: " + respuesta);
            }
        } while (numero != 0);

        // Cerrar las conexiones
        out.close();
        in.close();
        socket.close();
        scanner.close();
    }
}
