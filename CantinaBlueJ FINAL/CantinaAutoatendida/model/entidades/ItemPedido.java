package model.entidades;

/**
 * Representa um item específico dentro de um pedido de venda.
 * <p>
 * Esta classe associa um {@link Produto} a uma quantidade desejada,
 * permitindo o cálculo do subtotal para esse item específico no pedido.
 * Ela serve como um componente essencial para a classe {@code Pedido}.
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class ItemPedido {

    /**
     * O produto que está sendo pedido.
     */
    private Produto produto;

    /**
     * A quantidade de unidades do produto que está sendo pedida.
     */
    private int quantidade;

    /**
     * Construtor para criar um novo item de pedido.
     *
     * @param produto    A instância do {@link Produto} a ser adicionada ao pedido.
     * @param quantidade A quantidade de unidades deste produto.
     */
    public ItemPedido(Produto produto, int quantidade) {
        this.produto = produto;
        this.quantidade = quantidade;
    }

    /**
     * Retorna o objeto Produto associado a este item de pedido.
     *
     * @return A instância de {@link Produto}.
     */
    public Produto getProduto() {
        return produto;
    }

    /**
     * Retorna a quantidade de unidades deste item no pedido.
     *
     * @return A quantidade do produto.
     */
    public int getQuantidade() {
        return quantidade;
    }

    /**
     * Calcula e retorna o subtotal para este item de pedido.
     * <p>
     * O cálculo é feito multiplicando o preço do produto pela quantidade pedida.
     * </p>
     *
     * @return O valor do subtotal (preço * quantidade).
     */
    public double getSubtotal() {
        return produto.getPreco() * quantidade;
    }
}