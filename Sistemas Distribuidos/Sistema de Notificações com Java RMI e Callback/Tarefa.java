import java.io.Serializable;

public class Tarefa implements Serializable {
    private static final long serialVersionUID = 1L;

    private final int id;
    private final String descricao;
    private final int novoValor;

    public Tarefa(int id, String descricao, int novoValor) {
        this.id = id;
        this.descricao = descricao;
        this.novoValor = novoValor;
    }

    public int getId() {
        return id;
    }

    public String getDescricao() {
        return descricao;
    }

    public int getNovoValor() {
        return novoValor;
    }

    @Override
    public String toString() {
        return "Tarefa{id=" + id + ", descricao='" + descricao + "', novoValor=" + novoValor + "}";
    }
}
