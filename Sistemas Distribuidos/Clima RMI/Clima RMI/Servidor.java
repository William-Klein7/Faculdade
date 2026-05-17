import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class Servidor {

    public static void main(String[] args) {
        try {
            LocateRegistry.createRegistry(1099);
            System.out.println("[Servidor] Registro RMI criado na porta 1099.");

            ClimaImpl clima = new ClimaImpl();

            Naming.rebind("ServicoClima", clima);

            System.out.println("[Servidor] Serviço de Clima registrado com sucesso!");
            System.out.println("[Servidor] Aguardando chamadas de clientes...");
            System.out.println("[Servidor] Cidades disponíveis: São Paulo, Rio de Janeiro, Curitiba,");
            System.out.println("           Belo Horizonte, Porto Alegre, Salvador, Brasília,");
            System.out.println("           Manaus, Recife, Fortaleza");
            System.out.println("---------------------------------------------------");

        } catch (Exception e) {
            System.err.println("[Servidor] Erro: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
