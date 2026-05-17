import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class CalculadoraServer {
    
    public static void main(String[] args) {
        try {
            CalculadoraImpl calculadora = new CalculadoraImpl();
            
            Registry registry = LocateRegistry.createRegistry(1099);
            
            registry.rebind("CalculadoraService", calculadora);
            
            System.out.println("Servidor de Calculadora RMI iniciado na porta 1099");
            System.out.println("Aguardando requisicoes dos clientes...");
            
        } catch (Exception e) {
            System.err.println("Erro no servidor: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
