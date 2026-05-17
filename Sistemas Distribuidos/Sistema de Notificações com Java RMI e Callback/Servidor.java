import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Servidor {
    public static final int PORTA_RMI = 1099;
    public static final String NOME_SERVICO = "NotificationService";

    public static void main(String[] args) {
        try {
            NotificationServerImpl server = new NotificationServerImpl();
            ServerInterface stub = (ServerInterface) UnicastRemoteObject.exportObject(server, 0);

            Registry registry = LocateRegistry.createRegistry(PORTA_RMI);
            registry.rebind(NOME_SERVICO, stub);

            System.out.println("Servidor RMI iniciado na porta " + PORTA_RMI + ".");
            System.out.println("Servico publicado como '" + NOME_SERVICO + "'.");
        } catch (Exception e) {
            System.err.println("Erro ao iniciar servidor: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
