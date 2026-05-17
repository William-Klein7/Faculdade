import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class Servidor {
    public static void main(String[] args) {
        try {
            LocateRegistry.createRegistry(1099);
            ChatServidor chatServidor = new ChatServidorImpl();
            Naming.rebind("rmi://localhost/ChatServidor", chatServidor);
            System.out.println("Servidor de chat RMI iniciado na porta 1099.");
            System.out.println("Aguardando mensagens dos clientes...");
        } catch (Exception e) {
            System.err.println("Erro ao iniciar servidor: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
