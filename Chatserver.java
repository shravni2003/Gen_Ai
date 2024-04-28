//Write a multithreaded program in JAVA for chatting
import java.io.*;
import java.net.*;
import java.util.*;

public class ChatServer {
    private static final int PORT = 12345;
    private static Set<String> usernames = new HashSet<>();
    private static List<ClientHandler> clients = new ArrayList<>();

    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(PORT);
            System.out.println("Chat Server started on port " + PORT);

            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("New client connected: " + clientSocket);

                ClientHandler clientHandler = new ClientHandler(clientSocket);
                clients.add(clientHandler);
                clientHandler.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static class ClientHandler extends Thread {
        private Socket clientSocket;
        private PrintWriter out;
        private BufferedReader in;
        private String username;

        public ClientHandler(Socket socket) {
            this.clientSocket = socket;
        }

        @Override
        public void run() {
            try {
                out = new PrintWriter(clientSocket.getOutputStream(), true);
                in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

                // Ask for username
                out.println("Enter your username:");
                username = in.readLine();

                synchronized (usernames) {
                    while (usernames.contains(username)) {
                        out.println("Username already taken. Please choose another one:");
                        username = in.readLine();
                    }
                    usernames.add(username);
                }

                // Welcome message
                out.println("Welcome to the chat, " + username + "!");
                broadcast(username + " has joined the chat.");

                // Chatting
                String message;
                while ((message = in.readLine()) != null) {
                    if ("exit".equalsIgnoreCase(message)) {
                        break;
                    }
                    broadcast(username + ": " + message);
                }

                // Cleanup
                out.println("Goodbye, " + username + "!");
                clients.remove(this);
                usernames.remove(username);
                broadcast(username + " has left the chat.");
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        private void broadcast(String message) {
            synchronized (clients) {
                for (ClientHandler client : clients) {
                    client.out.println(message);
                }
            }
        }
    }
}
