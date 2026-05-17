import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class TaskManagerImpl extends UnicastRemoteObject implements TaskManager {
    private final Map<Integer, Task> tasks;
    private final AtomicInteger proximoId;

    public TaskManagerImpl() throws RemoteException {
        this.tasks = new ConcurrentHashMap<>();
        this.proximoId = new AtomicInteger(1);
    }

    @Override
    public void adicionarTask(String descricao) throws RemoteException {
        if (descricao == null || descricao.isBlank()) {
            throw new IllegalArgumentException("A descrição da task não pode ser vazia.");
        }

        int id = proximoId.getAndIncrement();
        tasks.put(id, new Task(id, descricao.trim()));
    }

    @Override
    public List<String> listarTasks() throws RemoteException {
        List<Task> ordenadas = new ArrayList<>(tasks.values());
        ordenadas.sort(Comparator.comparingInt(Task::getId));

        List<String> resultado = new ArrayList<>();
        for (Task task : ordenadas) {
            resultado.add(task.toString());
        }

        return resultado;
    }

    @Override
    public boolean marcarComoConcluida(int id) throws RemoteException {
        Task task = tasks.get(id);
        if (task == null || task.isConcluida()) {
            return false;
        }

        task.marcarComoConcluida();
        return true;
    }
}
