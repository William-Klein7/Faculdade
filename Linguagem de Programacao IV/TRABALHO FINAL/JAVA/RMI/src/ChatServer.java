import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;

public class ChatServer implements ChatInterface {
    private String name;
    private static List<ChatInterface> clients = new ArrayList<>();
    public ChatServer(String name) {
        this.name = name;
    }
    @Override
    public void sendMessage(String sender, String message) {
        String formatted = sender + ": " + message;
        System.out.println(formatted);

        for (ChatInterface client : clients) {
            try {
                if (!client.getName().equals(sender)) {
                    client.sendMessage(sender, message);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
    public void registerClient(ChatInterface client) {
        clients.add(client);
        try {
            System.out.println(client.getName() + " entrou no chat!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public String getName() {
        return name;
    }

    public static void main(String[] args) {
        try {
            ChatServer server = new ChatServer("Servidor");
            ChatInterface stub = (ChatInterface) UnicastRemoteObject.exportObject(server, 0);

            Registry registry = LocateRegistry.createRegistry(1099);
            registry.bind("ChatServer", stub);

            System.out.println("Servidor pronto!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
