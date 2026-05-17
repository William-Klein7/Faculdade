import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IClima extends Remote {

    String getTemperatura(String cidade) throws RemoteException;
}
