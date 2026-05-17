import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Servidor {
    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.createRegistry(1099);
            TaskManager taskManager = new TaskManagerImpl();
            registry.rebind("TaskManager", taskManager);

            System.out.println("Servidor de Tasks iniciado na porta 1099.");
            System.out.println("Serviço registrado com nome: TaskManager");
        } catch (Exception e) {
            System.err.println("Erro ao iniciar o servidor: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
