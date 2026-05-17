import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ClientCallbackInterface extends Remote {
    void notifyChange(int newValue) throws RemoteException;

    Confirmacao notifyTask(Tarefa tarefa) throws RemoteException;
}
