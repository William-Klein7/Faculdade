import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.List;
import java.util.Scanner;

public class Cliente {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            TaskManager taskManager = (TaskManager) registry.lookup("TaskManager");

            boolean executando = true;
            while (executando) {
                exibirMenu();
                System.out.print("Escolha uma opção: ");

                String entrada = scanner.nextLine().trim();
                switch (entrada) {
                    case "1":
                        adicionarTask(scanner, taskManager);
                        break;
                    case "2":
                        listarTasks(taskManager);
                        break;
                    case "3":
                        concluirTask(scanner, taskManager);
                        break;
                    case "0":
                        executando = false;
                        System.out.println("Encerrando cliente...");
                        break;
                    default:
                        System.out.println("Opção inválida. Tente novamente.");
                }
            }
        } catch (Exception e) {
            System.err.println("Erro no cliente: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void exibirMenu() {
        System.out.println("\n===== Sistema de Gerenciamento de Tarefas =====");
        System.out.println("1. Adicionar Task");
        System.out.println("2. Listar Tasks");
        System.out.println("3. Concluir Task");
        System.out.println("0. Sair");
    }

    private static void adicionarTask(Scanner scanner, TaskManager taskManager) throws Exception {
        System.out.print("Descrição da task: ");
        String descricao = scanner.nextLine();
        taskManager.adicionarTask(descricao);
        System.out.println("Task adicionada com sucesso.");
    }

    private static void listarTasks(TaskManager taskManager) throws Exception {
        List<String> tasks = taskManager.listarTasks();
        if (tasks.isEmpty()) {
            System.out.println("Nenhuma task cadastrada.");
            return;
        }

        System.out.println("\n--- Lista de Tasks ---");
        for (String task : tasks) {
            System.out.println(task);
        }
    }

    private static void concluirTask(Scanner scanner, TaskManager taskManager) throws Exception {
        System.out.print("Informe o ID da task a concluir: ");
        String entradaId = scanner.nextLine().trim();

        try {
            int id = Integer.parseInt(entradaId);
            boolean concluida = taskManager.marcarComoConcluida(id);
            if (concluida) {
                System.out.println("Task marcada como concluída.");
            } else {
                System.out.println("Task não encontrada ou já estava concluída.");
            }
        } catch (NumberFormatException e) {
            System.out.println("ID inválido. Digite um número inteiro.");
        }
    }
}
