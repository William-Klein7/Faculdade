package model.entidades;

import java.time.LocalDate;

/**
 * Representa uma Bebida, que é um tipo específico de {@link Produto}.
 * <p>
 * Esta classe herda os atributos e comportamentos da classe {@link Produto} e adiciona
 * um atributo específico para o volume em mililitros (ml). Ela também implementa
 * o método {@code getCategoria()} para retornar a string "Bebida".
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class Bebida extends Produto {

    /**
     * O volume da bebida em mililitros (ml).
     */
    private int volumeMl;

    /**
     * Construtor para criar um novo objeto Bebida.
     * <p>
     * Repassa os parâmetros comuns para o construtor da superclasse {@link Produto} e
     * inicializa o atributo específico de volume desta classe.
     * </p>
     *
     * @param nome          O nome da bebida (ex: "Refrigerante", "Suco de Laranja").
     * @param preco         O preço unitário da bebida.
     * @param quantidade    A quantidade inicial da bebida em estoque.
     * @param dataValidade  A data de validade da bebida.
     * @param volumeMl      O volume da bebida em mililitros (ml).
     */
    public Bebida(String nome, double preco, int quantidade, LocalDate dataValidade, int volumeMl) {
        super(nome, preco, quantidade, dataValidade);
        this.volumeMl = volumeMl;
    }

    /**
     * Retorna o volume da bebida em mililitros.
     *
     * @return O volume da bebida em ml.
     */
    public int getVolumeMl() {
        return volumeMl;
    }

    /**
     * Retorna a categoria específica para este tipo de produto.
     *
     * @return A string fixa "Bebida".
     * @override
     */
    @Override
    public String getCategoria() {
        return "Bebida";
    }
}