public class Task {
    private final int id;
    private final String descricao;
    private boolean concluida;

    public Task(int id, String descricao) {
        this.id = id;
        this.descricao = descricao;
        this.concluida = false;
    }

    public int getId() {
        return id;
    }

    public boolean isConcluida() {
        return concluida;
    }

    public void marcarComoConcluida() {
        this.concluida = true;
    }

    @Override
    public String toString() {
        String status = concluida ? "[Concluída]" : "[Pendente]";
        return id + " - " + status + " " + descricao;
    }
}
