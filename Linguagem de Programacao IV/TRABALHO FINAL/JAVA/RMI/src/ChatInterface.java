import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ChatInterface extends Remote {
    void sendMessage(String sender, String message) throws RemoteException;
    void registerClient(ChatInterface client) throws RemoteException;
    String getName() throws RemoteException;
}
