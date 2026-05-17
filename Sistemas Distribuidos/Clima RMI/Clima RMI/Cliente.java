import java.rmi.Naming;
import java.util.Scanner;

public class Cliente {

    public static void main(String[] args) {
        try {
            IClima stub = (IClima) Naming.lookup("rmi://localhost/ServicoClima");
            System.out.println("[Cliente] Conectado ao Serviço de Clima!");
            System.out.println("[Cliente] Digite o nome de uma cidade para consultar a temperatura.");
            System.out.println("[Cliente] Digite 'sair' para encerrar.");
            System.out.println("---------------------------------------------------");

            Scanner scanner = new Scanner(System.in);

            while (true) {
                System.out.print("\nDigite o nome da cidade: ");
                String cidade = scanner.nextLine().trim();

                if (cidade.equalsIgnoreCase("sair")) {
                    System.out.println("[Cliente] Encerrando...");
                    break;
                }

                if (cidade.isEmpty()) {
                    System.out.println("[Cliente] Por favor, digite o nome de uma cidade.");
                    continue;
                }

                String resultado = stub.getTemperatura(cidade);
                System.out.println("[Cliente] Resultado: " + resultado);
            }

            scanner.close();

        } catch (Exception e) {
            System.err.println("[Cliente] Erro: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
