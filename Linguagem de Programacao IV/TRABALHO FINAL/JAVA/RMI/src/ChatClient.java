import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class ChatClient implements ChatInterface {
    private String name;

    public ChatClient(String name) {
        this.name = name;
    }

    @Override
    public void sendMessage(String sender, String message) {
        if (!sender.equals(this.name)) {
            System.out.println(sender + ": " + message);
        }
    }

    @Override
    public void registerClient(ChatInterface client) { }

    @Override
    public String getName() {
        return name;
    }

    public static void main(String[] args) {
        try {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Digite seu nome: ");
            String name = scanner.nextLine();

            ChatClient client = new ChatClient(name);
            ChatInterface stub = (ChatInterface) UnicastRemoteObject.exportObject(client, 0);

            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            ChatInterface server = (ChatInterface) registry.lookup("ChatServer");

            server.registerClient(stub);

            System.out.println("Conectado ao chat! Digite mensagens:");

            while (true) {
                String msg = scanner.nextLine();
                server.sendMessage(name, msg);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
