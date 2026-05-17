import java.rmi.RemoteException;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class NotificationServerImpl implements ServerInterface {
    private final List<ClientCallbackInterface> clientes;
    private int contador;
    private int proximaTarefaId;

    public NotificationServerImpl() {
        this.clientes = new CopyOnWriteArrayList<>();
        this.contador = 0;
        this.proximaTarefaId = 0;
    }

    @Override
    public void register(ClientCallbackInterface c) throws RemoteException {
        clientes.add(c);
        System.out.println("Cliente registrado. Total conectados: " + clientes.size());
    }

    @Override
    public void increment() throws RemoteException {
        int novoValor;
        Tarefa tarefa;

        synchronized (this) {
            contador++;
            proximaTarefaId++;
            novoValor = contador;
            tarefa = new Tarefa(proximaTarefaId, "Contador atualizado para " + novoValor, novoValor);
        }

        System.out.println("Contador atualizado para: " + novoValor);
        notificarClientes(novoValor, tarefa);
    }

    private void notificarClientes(int novoValor, Tarefa tarefa) {
        for (ClientCallbackInterface cliente : clientes) {
            try {
                cliente.notifyChange(novoValor);
                Confirmacao confirmacao = cliente.notifyTask(tarefa);
                System.out.println("Confirmacao recebida: " + confirmacao);
            } catch (RemoteException e) {
                clientes.remove(cliente);
                System.out.println("Cliente removido apos falha no callback: " + e.getMessage());
            }
        }
    }
}
