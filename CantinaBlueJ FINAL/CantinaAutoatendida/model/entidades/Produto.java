package model.entidades;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

/**
 * Classe abstrata que representa um item genérico vendável em uma cantina.
 * <p>
 * Esta classe encapsula os atributos e comportamentos comuns a todos os produtos,
 * como nome, preço, quantidade em estoque e data de validade. Ela deve ser estendida
 * por classes concretas que representem tipos específicos de produtos, como
 * {@code Lanche} ou {@code Bebida}.
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public abstract class Produto {

    /** O nome do produto. */
    protected String nome;

    /** O preço unitário do produto. */
    protected double preco;

    /** A quantidade de unidades do produto disponíveis em estoque. */
    protected int quantidade;

    /** A data de validade do produto. */
    protected LocalDate dataValidade;

    /**
     * Construtor para inicializar um novo produto com seus atributos básicos.
     *
     * @param nome          O nome do produto (ex: "Coxinha", "Refrigerante").
     * @param preco         O preço unitário do produto.
     * @param quantidade    A quantidade inicial do produto em estoque.
     * @param dataValidade  A data de validade do produto.
     */
    public Produto(String nome, double preco, int quantidade, LocalDate dataValidade) {
        this.nome = nome;
        this.preco = preco;
        this.quantidade = quantidade;
        this.dataValidade = dataValidade;
    }

    /**
     * Método abstrato para obter a categoria do produto.
     * Classes filhas devem implementar este método para retornar sua categoria
     * específica (ex: "Lanche", "Bebida").
     *
     * @return Uma {@code String} representando a categoria do produto.
     */
    public abstract String getCategoria();

    /**
     * Retorna o nome do produto.
     *
     * @return O nome do produto.
     */
    public String getNome() { return nome; }

    /**
     * Retorna o preço do produto.
     *
     * @return O preço do produto.
     */
    public double getPreco() { return preco; }

    /**
     * Retorna a quantidade atual do produto em estoque.
     *
     * @return A quantidade em estoque.
     */
    public int getQuantidade() { return quantidade; }

    /**
     * Retorna a data de validade do produto.
     *
     * @return A data de validade como um objeto {@link LocalDate}.
     */
    public LocalDate getDataValidade() { return dataValidade; }

    /**
     * Define um novo preço para o produto.
     *
     * @param preco O novo preço a ser definido.
     */
    public void setPreco(double preco) { this.preco = preco; }

    /**
     * Reduz a quantidade de itens do produto no estoque.
     * A operação só é realizada se a quantidade a ser removida for menor ou igual
     * à quantidade atual, evitando um estoque negativo.
     *
     * @param qtd A quantidade de itens a ser removida do estoque.
     */
    public void reduzirEstoque(int qtd) {
        if (this.quantidade >= qtd) {
            this.quantidade -= qtd;
        }
    }

    /**
     * Adiciona uma quantidade de itens ao estoque do produto.
     *
     * @param qtd A quantidade de itens a ser adicionada.
     */
    public void adicionarEstoque(int qtd) {
        this.quantidade += qtd;
    }

    /**
     * Verifica se o produto está com a data de validade expirada.
     * Compara a data de validade do produto com a data atual do sistema.
     *
     * @return {@code true} se a data atual for posterior à data de validade,
     * {@code false} caso contrário.
     */
    public boolean isVencido() {
        return LocalDate.now().isAfter(dataValidade);
    }

    /**
     * Retorna uma representação em formato de String do objeto Produto.
     * A string inclui nome, preço formatado, quantidade em estoque e data de
     * validade formatada (dd/MM/yyyy).
     *
     * @return Uma String formatada com os detalhes do produto.
     * @override
     */
    @Override
    public String toString() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        return nome + " (R$ " + String.format("%.2f", preco) + ") - Estoque: " + quantidade + " - Val: " + dataValidade.format(formatter);
    }
}