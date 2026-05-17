package monitor;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.Map;

public class SensorHubImpl extends UnicastRemoteObject implements ISensorHub {
    private final Map<String, Double> temperaturas;

    protected SensorHubImpl() throws RemoteException {
        super();
        temperaturas = new HashMap<>();
    }

    @Override
    public synchronized void atualizarTemperatura(String local, double valor) throws RemoteException {
        System.out.printf("Atualizando %s para %.2f°C%n", local, valor);
        temperaturas.put(local, valor);
    }

    @Override
    public synchronized Double lerTemperatura(String local) throws RemoteException {
        return temperaturas.get(local);
    }
}
