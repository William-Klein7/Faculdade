package monitor;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class MonitorClient {
    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", SensorHubServer.PORTA_RMI);
            ISensorHub hub = (ISensorHub) registry.lookup(SensorHubServer.NOME_SERVICO);

            executarModoInterativo(hub);
        } catch (Exception e) {
            System.err.println("Falha ao iniciar o cliente: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void executarModoInterativo(ISensorHub hub) throws Exception {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.println("Cliente do monitor. Digite a opcao desejada.");

            while (true) {
                System.out.println();
                System.out.println("1 - Enviar temperatura (sensor)");
                System.out.println("2 - Consultar temperatura (painel)");
                System.out.println("3 - Sair");
                System.out.print("Opcao: ");

                String opcao = scanner.nextLine().trim();

                switch (opcao) {
                    case "1":
                        enviarLeitura(scanner, hub);
                        break;
                    case "2":
                        consultarLeitura(scanner, hub);
                        break;
                    case "3":
                    case "sair":
                        return;
                    default:
                        System.out.println("Opcao invalida.");
                        break;
                }
            }
        }
    }

    private static void enviarLeitura(Scanner scanner, ISensorHub hub) throws Exception {
        System.out.print("Local: ");
        String local = scanner.nextLine().trim();

        if (local.isEmpty()) {
            System.out.println("Informe um local valido.");
            return;
        }

        System.out.print("Temperatura: ");
        String valorTexto = scanner.nextLine().trim();

        double valor;

        try {
            valor = Double.parseDouble(valorTexto);
        } catch (NumberFormatException e) {
            System.out.println("A temperatura deve ser um numero decimal valido.");
            return;
        }

        hub.atualizarTemperatura(local, valor);
        System.out.printf("Sensor enviou %.2f°C para %s.%n", valor, local);
    }

    private static void consultarLeitura(Scanner scanner, ISensorHub hub) throws Exception {
        System.out.print("Local: ");
        String local = scanner.nextLine().trim();

        if (local.isEmpty()) {
            System.out.println("Informe um local valido.");
            return;
        }

        Double temperatura = hub.lerTemperatura(local);

        if (temperatura == null) {
            System.out.printf("Sala %s nao encontrada.%n", local);
            return;
        }

        System.out.printf("Painel leu %.2f°C em %s.%n", temperatura, local);
    }
}
