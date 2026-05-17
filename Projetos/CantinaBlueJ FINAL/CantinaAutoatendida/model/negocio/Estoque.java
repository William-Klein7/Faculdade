package model.negocio;

import model.entidades.Bebida;
import model.entidades.Lanche;
import model.entidades.Produto;
import model.excecoes.ValidacaoProdutoException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * Gerencia o inventário de produtos da cantina.
 * <p>
 * Esta classe é responsável por armazenar, buscar, adicionar e remover
 * instâncias de {@link Produto}. Ela centraliza todas as operações relacionadas
 * ao estoque, incluindo validações e filtragens. Ao ser instanciada,
 * a classe já é populada com uma carga inicial de produtos para demonstração.
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class Estoque {

    /** A lista interna que armazena todas as instâncias de {@link Produto}. */
    private List<Produto> produtos;

    /**
     * Construtor que inicializa o estoque.
     * Cria a lista de produtos e a popula com um conjunto inicial de
     * {@link Lanche} e {@link Bebida} para fins de demonstração.
     */
    public Estoque() {
        this.produtos = new ArrayList<>();
        // Carga inicial para demonstração
        produtos.add(new Lanche("X-Salada", 15.00, 20, LocalDate.now().plusDays(2)));
        produtos.add(new Bebida("Refrigerante Lata", 5.00, 30, LocalDate.now().plusDays(30), 350));
        produtos.add(new Bebida("Suco Natural", 7.50, 15, LocalDate.now().plusDays(1), 500));
        produtos.add(new Lanche("Salgado Assado", 6.00, 25, LocalDate.now().plusDays(1)));
        produtos.add(new Lanche("Barra de Chocolate", 4.00, 50, LocalDate.now().plusDays(60)));
    }

    /**
     * Retorna a lista completa de todos os produtos no estoque.
     * <p>
     * Note que esta lista inclui todos os produtos cadastrados,
     * independentemente de estarem disponíveis (com quantidade > 0) ou vencidos.
     * Para obter apenas os produtos para venda, use {@link #listarProdutosDisponiveis()}.
     * </p>
     *
     * @return A lista de todos os {@link Produto} cadastrados.
     */
    public List<Produto> getProdutos() {
        return produtos;
    }

    /**
     * Busca um produto pelo seu nome, ignorando diferenças de maiúsculas e minúsculas.
     *
     * @param nome O nome do produto a ser buscado.
     * @return Um {@link Optional} contendo o {@link Produto} se encontrado,
     * ou um {@link Optional} vazio caso contrário.
     */
    public Optional<Produto> buscarProdutoPorNome(String nome) {
        return produtos.stream()
                .filter(p -> p.getNome().equalsIgnoreCase(nome))
                .findFirst();
    }

    /**
     * Adiciona um novo produto ao estoque após validar sua unicidade.
     * O método verifica se já existe um produto com o mesmo nome (ignorando capitalização)
     * antes de realizar a inserção.
     *
     * @param produto O {@link Produto} a ser adicionado.
     * @throws ValidacaoProdutoException Se já existir um produto com o mesmo nome no estoque.
     */
    public void adicionarProduto(Produto produto) throws ValidacaoProdutoException {
        if (buscarProdutoPorNome(produto.getNome()).isPresent()) {
            throw new ValidacaoProdutoException("Já existe um produto com o nome: " + produto.getNome());
        }
        produtos.add(produto);
    }

    /**
     * Remove um produto do estoque com base no seu nome.
     * A busca pelo nome para remoção ignora diferenças de maiúsculas e minúsculas.
     *
     * @param nomeProduto O nome do produto a ser removido.
     */
    public void removerProduto(String nomeProduto) {
        produtos.removeIf(p -> p.getNome().equalsIgnoreCase(nomeProduto));
    }

    /**
     * Retorna uma lista de produtos que estão disponíveis para venda.
     * <p>
     * A disponibilidade é definida por duas condições:
     * 1. A quantidade em estoque deve ser maior que zero.
     * 2. O produto não pode estar com a data de validade vencida.
     * </p>
     *
     * @return Uma nova lista contendo apenas os produtos disponíveis.
     */
    public List<Produto> listarProdutosDisponiveis() {
        return produtos.stream()
                .filter(p -> p.getQuantidade() > 0 && !p.isVencido())
                .collect(Collectors.toList());
    }
}