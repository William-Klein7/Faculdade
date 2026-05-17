package monitor;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ISensorHub extends Remote {
    void atualizarTemperatura(String local, double valor) throws RemoteException;

    Double lerTemperatura(String local) throws RemoteException;
}
