import java.io.*;
import java.net.*;

public class ChatClient {
    private static final String SERVER_ADDRESS = "localhost";
    private static final int PORT = 12345;

    public static void main(String[] args) {
        try {
            Socket socket = new Socket(SERVER_ADDRESS, PORT);

            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            BufferedReader consoleReader = new BufferedReader(new InputStreamReader(System.in));

            System.out.println("Connected to the server. Start typing messages:");

            // Start a separate thread for receiving messages from the server
            Thread receiveThread = new Thread(() -> {
                try {
                    String message;
                    while ((message = reader.readLine()) != null) {
                        System.out.println(message);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
            receiveThread.start();

            // Main thread for sending messages
            String userInput;
            while ((userInput = consoleReader.readLine()) != null) {
                writer.write(userInput + "\n");
                writer.flush();
            }

            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
