import java.io.Serializable;

public class Confirmacao implements Serializable {
    private static final long serialVersionUID = 1L;

    private final String cliente;
    private final int tarefaId;
    private final String mensagem;

    public Confirmacao(String cliente, int tarefaId, String mensagem) {
        this.cliente = cliente;
        this.tarefaId = tarefaId;
        this.mensagem = mensagem;
    }

    public String getCliente() {
        return cliente;
    }

    public int getTarefaId() {
        return tarefaId;
    }

    public String getMensagem() {
        return mensagem;
    }

    @Override
    public String toString() {
        return "Confirmacao{cliente='" + cliente + "', tarefaId=" + tarefaId + ", mensagem='" + mensagem + "'}";
    }
}
