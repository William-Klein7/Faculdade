import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class CalculadoraClient {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            
            ICalculadora calculadora = (ICalculadora) registry.lookup("CalculadoraService");
            
            System.out.println("=== Calculadora Distribuida RMI ===");
            System.out.println("Conectado ao servidor!");
            
            boolean continuar = true;
            
            while (continuar) {
                System.out.println("\nEscolha a operacao:");
                System.out.println("1 - Somar");
                System.out.println("2 - Subtrair");
                System.out.println("3 - Multiplicar");
                System.out.println("4 - Dividir");
                System.out.println("0 - Sair");
                System.out.print("Opcao: ");
                
                int opcao = scanner.nextInt();
                
                if (opcao == 0) {
                    continuar = false;
                    System.out.println("Encerrando cliente...");
                    continue;
                }
                
                System.out.print("Digite o primeiro numero: ");
                double num1 = scanner.nextDouble();
                
                System.out.print("Digite o segundo numero: ");
                double num2 = scanner.nextDouble();
                
                double resultado = 0;
                
                try {
                    switch (opcao) {
                        case 1:
                            resultado = calculadora.somar(num1, num2);
                            System.out.println("Resultado: " + num1 + " + " + num2 + " = " + resultado);
                            break;
                        case 2:
                            resultado = calculadora.subtrair(num1, num2);
                            System.out.println("Resultado: " + num1 + " - " + num2 + " = " + resultado);
                            break;
                        case 3:
                            resultado = calculadora.multiplicar(num1, num2);
                            System.out.println("Resultado: " + num1 + " * " + num2 + " = " + resultado);
                            break;
                        case 4:
                            resultado = calculadora.dividir(num1, num2);
                            System.out.println("Resultado: " + num1 + " / " + num2 + " = " + resultado);
                            break;
                        default:
                            System.out.println("Opcao invalida!");
                    }
                } catch (ArithmeticException e) {
                    System.out.println("Erro: " + e.getMessage());
                }
            }
            
            scanner.close();
            
        } catch (Exception e) {
            System.err.println("Erro no cliente: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
