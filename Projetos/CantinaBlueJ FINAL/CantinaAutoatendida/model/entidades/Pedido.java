package model.entidades;

import model.excecoes.EstoqueInsuficienteException;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * Representa um pedido de venda, que consiste em uma coleção de itens,
 * um valor total e a data e hora em que foi criado.
 * <p>
 * Esta classe gerencia a adição e remoção de {@link ItemPedido} e é responsável
 * por validar o estoque antes de adicionar um produto, além de calcular
 * automaticamente o valor total do pedido.
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class Pedido {

    /** A lista de itens que compõem o pedido. */
    private final List<ItemPedido> itens;

    /** O custo total do pedido, calculado a partir dos subtotais dos itens. */
    private double valorTotal;

    /** A data e hora exatas em que o pedido foi instanciado. */
    private final LocalDateTime dataHora;

    /**
     * Construtor padrão que inicializa um novo pedido vazio.
     * Cria uma lista de itens, define o valor total como 0.0 e registra
     * a data e hora atuais como o momento de criação do pedido.
     */
    public Pedido() {
        this.itens = new ArrayList<>();
        this.valorTotal = 0.0;
        this.dataHora = LocalDateTime.now();
    }

    /**
     * Adiciona um produto ao pedido ou atualiza sua quantidade se ele já existir na lista.
     * <p>
     * Antes de adicionar, o método verifica se o estoque disponível do produto é suficiente,
     * considerando não apenas a quantidade que está sendo adicionada agora, mas também
     * qualquer quantidade do mesmo produto que já esteja no carrinho.
     * </p>
     * Se o produto já estiver no pedido, sua quantidade é incrementada. Caso contrário,
     * um novo {@link ItemPedido} é criado e adicionado à lista. Ao final, o valor
     * total do pedido é recalculado.
     *
     * @param produto    O {@link Produto} a ser adicionado.
     * @param quantidade A quantidade do produto a ser adicionada.
     * @throws EstoqueInsuficienteException Se a quantidade total desejada (incluindo o que
     * já está no carrinho) exceder o estoque disponível.
     */
    public void adicionarItem(Produto produto, int quantidade) throws EstoqueInsuficienteException {
        int qtdJaNoCarrinho = getItens().stream()
                .filter(item -> item.getProduto().equals(produto))
                .mapToInt(ItemPedido::getQuantidade)
                .sum();

        if (produto.getQuantidade() < (qtdJaNoCarrinho + quantidade)) {
            throw new EstoqueInsuficienteException("Estoque insuficiente para " + produto.getNome() + ".\n"
                    + "Disponível: " + produto.getQuantidade() + ", No seu carrinho: " + qtdJaNoCarrinho);
        }

        Optional<ItemPedido> itemExistente = this.itens.stream()
                .filter(item -> item.getProduto().equals(produto))
                .findFirst();

        if (itemExistente.isPresent()) {
            ItemPedido item = itemExistente.get();
            int novaQuantidade = item.getQuantidade() + quantidade;
            // Substitui o item antigo por um novo com a quantidade atualizada
            this.itens.set(this.itens.indexOf(item), new ItemPedido(produto, novaQuantidade));
        } else {
            this.itens.add(new ItemPedido(produto, quantidade));
        }

        calcularTotal();
    }

    /**
     * Remove completamente um item (todas as suas unidades) do pedido, com base no produto.
     * Após a remoção, o valor total do pedido é recalculado.
     *
     * @param produto O {@link Produto} a ser removido do pedido.
     */
    public void removerItem(Produto produto) {
        this.itens.removeIf(item -> item.getProduto().equals(produto));
        calcularTotal();
    }

    /**
     * Método privado para recalcular o valor total do pedido.
     * Ele itera sobre todos os {@link ItemPedido} na lista, soma seus subtotais
     * e atualiza o atributo {@code valorTotal}.
     */
    private void calcularTotal() {
        this.valorTotal = this.itens.stream()
                .mapToDouble(ItemPedido::getSubtotal)
                .sum();
    }

    /**
     * Retorna a lista de itens contidos neste pedido.
     *
     * @return Uma lista de {@link ItemPedido}.
     */
    public List<ItemPedido> getItens() {
        return itens;
    }

    /**
     * Retorna o valor total calculado do pedido.
     *
     * @return O valor total como um {@code double}.
     */
    public double getValorTotal() {
        return valorTotal;
    }

    /**
     * Retorna a data e hora em que o pedido foi criado.
     *
     * @return O {@link LocalDateTime} da criação do pedido.
     */
    public LocalDateTime getDataHora() {
        return dataHora;
    }
}