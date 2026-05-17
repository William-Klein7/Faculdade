package model.entidades;

import java.time.LocalDate;

/**
 * Representa um Lanche, que é um tipo específico de {@link Produto}.
 * <p>
 * Esta classe herda todos os atributos e comportamentos básicos da classe {@link Produto},
 * como nome, preço e quantidade. Ela implementa o método abstrato {@code getCategoria()},
 * definindo-a permanentemente como "Lanche".
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class Lanche extends Produto {

    /**
     * Construtor para criar um novo objeto Lanche.
     * <p>
     * Este construtor simplesmente repassa todos os parâmetros para o construtor
     * da superclasse {@link Produto}.
     * </p>
     *
     * @param nome          O nome do lanche (ex: "Hambúrguer", "Misto Quente").
     * @param preco         O preço unitário do lanche.
     * @param quantidade    A quantidade inicial do lanche em estoque.
     * @param dataValidade  A data de validade do lanche.
     */
    public Lanche(String nome, double preco, int quantidade, LocalDate dataValidade) {
        super(nome, preco, quantidade, dataValidade);
    }

    /**
     * Retorna a categoria específica para este tipo de produto.
     *
     * @return A string fixa "Lanche".
     * @override
     */
    @Override
    public String getCategoria() {
        return "Lanche";
    }
}