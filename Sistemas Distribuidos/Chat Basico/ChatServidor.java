import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ChatServidor extends Remote {
    void enviarMensagem(String msg) throws RemoteException;
}
