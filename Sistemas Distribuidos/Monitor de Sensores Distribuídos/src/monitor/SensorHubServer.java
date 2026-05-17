package monitor;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class SensorHubServer {
    public static final String NOME_SERVICO = "SensorHub";
    public static final int PORTA_RMI = 1099;

    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.createRegistry(PORTA_RMI);
            ISensorHub hub = new SensorHubImpl();
            registry.rebind(NOME_SERVICO, hub);

            System.out.println("Concentrador de sensores pronto.");
            System.out.printf("Servico '%s' publicado na porta %d.%n", NOME_SERVICO, PORTA_RMI);
        } catch (Exception e) {
            System.err.println("Falha ao iniciar o servidor RMI: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
