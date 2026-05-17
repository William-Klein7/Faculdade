import java.rmi.Naming;
import java.rmi.RemoteException;
import java.util.Scanner;

public class Cliente {
    public static void main(String[] args) {
        try {
            ChatServidor chatServidor = (ChatServidor) Naming.lookup("rmi://localhost/ChatServidor");
            Scanner scanner = new Scanner(System.in);
            boolean encerradoPorComando = false;

            System.out.println("Conectado ao servidor de chat.");
            System.out.println("Digite suas mensagens (digite 'sair' para encerrar):");

            while (scanner.hasNextLine()) {
                String mensagem = scanner.nextLine();

                if ("sair".equalsIgnoreCase(mensagem.trim())) {
                    System.out.println("Encerrando cliente.");
                    encerradoPorComando = true;
                    break;
                }

                try {
                    chatServidor.enviarMensagem(mensagem);
                } catch (RemoteException envioErro) {
                    System.err.println("Falha ao enviar mensagem para o servidor: " + envioErro.getMessage());
                    break;
                }
            }

            if (!encerradoPorComando) {
                System.out.println("Entrada encerrada (EOF). Cliente finalizado.");
            }

            scanner.close();
        } catch (Exception e) {
            System.err.println("Erro no cliente: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
