package model.negocio;

import model.entidades.ItemPedido;
import model.entidades.Pedido;
import model.entidades.Produto;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Classe utilitária responsável por gerar diferentes tipos de relatórios textuais.
 * <p>
 * Esta classe é stateless e seus métodos recebem os dados necessários
 * (como histórico de pedidos ou o estoque atual) para processar e retornar
 * uma {@code String} formatada contendo o relatório solicitado.
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class GeradorRelatorios {

    /**
     * Gera um relatório cronológico de todas as transações (pedidos) realizadas.
     * Para cada pedido, exibe a data, a hora e o valor total.
     *
     * @param historico A lista de todos os {@link Pedido}s concluídos.
     * @return Uma {@code String} formatada com o relatório de transações,
     * ou uma mensagem indicando que não há registros.
     */
    public String gerarRelatorioTransacoes(List<Pedido> historico) {
        if (historico == null || historico.isEmpty()) {
            return "Nenhuma transação registrada.";
        }
        StringBuilder sb = new StringBuilder("--- Relatório de Todas as Transações ---\n\n");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss");
        historico.forEach(p -> sb.append("Data/Hora: ")
                .append(p.getDataHora().format(formatter))
                .append(" | Valor Total: R$ ")
                .append(String.format("%.2f", p.getValorTotal()))
                .append("\n"));
        return sb.toString();
    }

    /**
     * Gera um relatório dos produtos mais vendidos, ordenados por quantidade.
     * O método agrega a quantidade vendida de cada produto em todo o histórico
     * de pedidos e os lista em ordem decrescente.
     *
     * @param historico A lista de todos os {@link Pedido}s concluídos.
     * @return Uma {@code String} formatada com o ranking de produtos mais vendidos.
     */
    public String gerarRelatorioMaisVendidos(List<Pedido> historico) {
        if (historico == null || historico.isEmpty()) {
            return "Nenhuma venda registrada para gerar relatório.";
        }
        StringBuilder sb = new StringBuilder("--- Relatório de Produtos Mais Vendidos ---\n\n");
        Map<String, Integer> contagem = new HashMap<>();
        historico.forEach(p -> p.getItens()
                .forEach(item -> contagem.merge(item.getProduto().getNome(), item.getQuantidade(), Integer::sum)));

        contagem.entrySet().stream()
                .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
                .forEach(entry -> sb.append(String.format("%-25s | Vendidos: %d\n", entry.getKey(), entry.getValue())));

        return sb.toString();
    }

    /**
     * Gera um relatório de vendas agrupadas por hora do dia para identificar horários de pico.
     * O relatório é ordenado cromaticamente pela hora (00h, 01h, 02h...).
     *
     * @param historico A lista de todos os {@link Pedido}s concluídos.
     * @return Uma {@code String} formatada com a contagem de vendas por faixa de hora.
     */
    public String gerarRelatorioHorarioDePico(List<Pedido> historico) {
        if (historico == null || historico.isEmpty()) {
            return "Nenhuma venda registrada para gerar relatório.";
        }
        StringBuilder sb = new StringBuilder("--- Relatório de Horários de Maior Movimento ---\n\n");
        Map<Integer, Long> contagemPorHora = historico.stream()
                .collect(Collectors.groupingBy(p -> p.getDataHora().getHour(), Collectors.counting()));

        contagemPorHora.entrySet().stream()
                .sorted(Map.Entry.comparingByKey())
                .forEach(entry -> sb.append(String.format("Hora: %02d:00 - %02d:59 | Vendas: %d\n",
                        entry.getKey(), entry.getKey(), entry.getValue())));

        return sb.toString();
    }

    /**
     * Gera um relatório sobre o estado de validade dos produtos em estoque.
     * O relatório é dividido em duas seções: produtos que já venceram e
     * produtos que estão próximos de vencer (nos próximos 7 dias).
     *
     * @param estoque O objeto {@link Estoque} contendo os produtos a serem analisados.
     * @return Uma {@code String} formatada com o status de validade dos produtos.
     */
    public String gerarRelatorioDeValidade(Estoque estoque) {
        StringBuilder sb = new StringBuilder("--- Relatório de Validade de Produtos ---\n\n");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");

        sb.append("PRODUTOS VENCIDOS:\n");
        List<Produto> produtos = estoque.getProdutos();
        long vencidos = produtos.stream()
                .filter(Produto::isVencido)
                .peek(p -> sb.append(p.getNome())
                        .append(" - Venceu em: ")
                        .append(p.getDataValidade().format(formatter))
                        .append("\n"))
                .count();

        if (vencidos == 0) {
            sb.append("Nenhum.\n");
        }

        sb.append("\nPRODUTOS PRÓXIMOS DO VENCIMENTO (7 dias):\n");
        LocalDate limite = LocalDate.now().plusDays(8);
        long proximos = produtos.stream()
                .filter(p -> !p.isVencido() && p.getDataValidade().isBefore(limite))
                .peek(p -> sb.append(p.getNome())
                        .append(" - Vence em: ")
                        .append(p.getDataValidade().format(formatter))
                        .append("\n"))
                .count();

        if (proximos == 0) {
            sb.append("Nenhum.\n");
        }

        return sb.toString();
    }
}