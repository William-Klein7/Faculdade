import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface TaskManager extends Remote {
    void adicionarTask(String descricao) throws RemoteException;

    List<String> listarTasks() throws RemoteException;

    boolean marcarComoConcluida(int id) throws RemoteException;
}
