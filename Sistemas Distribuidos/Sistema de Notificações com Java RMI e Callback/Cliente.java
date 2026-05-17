import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class Cliente implements ClientCallbackInterface {
    private final String nome;
    private final ServerInterface server;

    public Cliente(String host, String nome) throws Exception {
        this.nome = nome;

        Registry registry = LocateRegistry.getRegistry(host, Servidor.PORTA_RMI);
        this.server = (ServerInterface) registry.lookup(Servidor.NOME_SERVICO);

        ClientCallbackInterface callbackStub = (ClientCallbackInterface) UnicastRemoteObject.exportObject(this, 0);
        this.server.register(callbackStub);
    }

    @Override
    public void notifyChange(int newValue) {
        System.out.println("[" + nome + "] Novo valor do contador: " + newValue);
    }

    @Override
    public Confirmacao notifyTask(Tarefa tarefa) {
        System.out.println("[" + nome + "] Tarefa recebida: " + tarefa);
        return new Confirmacao(nome, tarefa.getId(), "Tarefa processada com sucesso.");
    }

    private void iniciarMenu() throws Exception {
        try (Scanner scanner = new Scanner(System.in)) {
            boolean executando = true;

            while (executando) {
                System.out.println();
                System.out.println("=== Cliente de Notificacoes ===");
                System.out.println("1 - Incrementar");
                System.out.println("0 - Sair");
                System.out.print("Opcao: ");

                String opcao = scanner.nextLine().trim();

                switch (opcao) {
                    case "1":
                        server.increment();
                        break;
                    case "0":
                        executando = false;
                        break;
                    default:
                        System.out.println("Opcao invalida.");
                        break;
                }
            }
        }
    }

    public static void main(String[] args) {
        String host = args.length > 0 ? args[0] : "localhost";
        String nome = args.length > 1 ? args[1] : "Cliente-" + System.currentTimeMillis();

        try {
            Cliente cliente = new Cliente(host, nome);
            System.out.println(nome + " conectado ao servidor em " + host + ".");
            cliente.iniciarMenu();
        } catch (Exception e) {
            System.err.println("Erro no cliente: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
