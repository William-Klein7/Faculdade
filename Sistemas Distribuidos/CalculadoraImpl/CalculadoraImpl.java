import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class CalculadoraImpl extends UnicastRemoteObject implements ICalculadora {
    
    public CalculadoraImpl() throws RemoteException {
        super();
    }
    
    @Override
    public double somar(double a, double b) throws RemoteException {
        System.out.println("Executando: " + a + " + " + b);
        return a + b;
    }
    
    @Override
    public double subtrair(double a, double b) throws RemoteException {
        System.out.println("Executando: " + a + " - " + b);
        return a - b;
    }
    
    @Override
    public double multiplicar(double a, double b) throws RemoteException {
        System.out.println("Executando: " + a + " * " + b);
        return a * b;
    }
    
    @Override
    public double dividir(double a, double b) throws RemoteException {
        if (b == 0) {
            throw new ArithmeticException("Divisão por zero não é permitida");
        }
        System.out.println("Executando: " + a + " / " + b);
        return a / b;
    }
}
