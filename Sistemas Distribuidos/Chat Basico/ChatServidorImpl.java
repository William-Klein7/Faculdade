import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class ChatServidorImpl extends UnicastRemoteObject implements ChatServidor {
    private static final DateTimeFormatter FORMATTER = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss");
    private final List<String> mensagens;

    public ChatServidorImpl() throws RemoteException {
        super();
        this.mensagens = Collections.synchronizedList(new ArrayList<>());
    }

    @Override
    public void enviarMensagem(String msg) throws RemoteException {
        String mensagemFormatada = "[" + LocalDateTime.now().format(FORMATTER) + "] " + msg;
        mensagens.add(mensagemFormatada);
        System.out.println("Mensagem recebida: " + mensagemFormatada);
    }

    public List<String> getMensagens() {
        synchronized (mensagens) {
            return new ArrayList<>(mensagens);
        }
    }
}
