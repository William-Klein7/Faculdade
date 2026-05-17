package model.negocio;

import model.excecoes.FaltaTrocoException;
import model.excecoes.OperacaoCaixaException;
import java.util.*;

/**
 * Simula um caixa registrador físico, gerenciando o dinheiro disponível.
 * <p>
 * Esta classe é responsável por manter o controle das quantidades de cada
 * cédula e moeda (denominação), permitir o abastecimento e a retirada manual,
 * e calcular o troco para transações de venda.
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class Caixa {

    /**
     * Mapa que representa a gaveta de dinheiro.
     * A chave (Double) é o valor da cédula/moeda (ex: 50.0, 0.25) e o
     * valor (Integer) é a quantidade disponível daquela denominação.
     */
    private Map<Double, Integer> gavetaDinheiro;

    /**
     * Construtor que inicializa o caixa com um conjunto padrão de cédulas e moedas.
     * Popula a gaveta com valores comuns da moeda brasileira (Real) para simular
     * um caixa pronto para o início das operações.
     */
    public Caixa() {
        // LinkedHashMap mantém a ordem de inserção, útil para exibição.
        gavetaDinheiro = new LinkedHashMap<>();
        gavetaDinheiro.put(50.0, 10);
        gavetaDinheiro.put(20.0, 10);
        gavetaDinheiro.put(10.0, 10);
        gavetaDinheiro.put(5.0, 10);
        gavetaDinheiro.put(2.0, 10);
        gavetaDinheiro.put(1.0, 20);
        gavetaDinheiro.put(0.50, 20);
        gavetaDinheiro.put(0.25, 20);
        gavetaDinheiro.put(0.10, 20);
    }

    /**
     * Retorna uma visão do conteúdo atual da gaveta de dinheiro.
     *
     * @return Um mapa com as denominações e suas respectivas quantidades.
     */
    public Map<Double, Integer> getGavetaDinheiro() {
        return gavetaDinheiro;
    }

    /**
     * Adiciona uma quantidade específica de uma cédula ou moeda ao caixa (abastecimento).
     *
     * @param valor      O valor da denominação a ser adicionada (ex: 50.0 para R$50, 0.25 para R$0.25).
     * @param quantidade O número de cédulas/moedas a serem adicionadas.
     * @throws OperacaoCaixaException Se o valor ou a quantidade fornecidos forem negativos ou nulos.
     */
    public void abastecerDinheiro(double valor, int quantidade) throws OperacaoCaixaException {
        if (quantidade <= 0) {
            throw new OperacaoCaixaException("A quantidade para abastecer deve ser positiva.");
        }
        if (valor <= 0) {
            throw new OperacaoCaixaException("O valor da cédula/moeda deve ser positivo.");
        }
        gavetaDinheiro.merge(valor, quantidade, Integer::sum);
    }

    /**
     * Retira uma quantidade específica de uma cédula ou moeda do caixa.
     *
     * @param valor      O valor da denominação a ser retirada.
     * @param quantidade A quantidade de cédulas/moedas a serem retiradas.
     * @throws OperacaoCaixaException Se o valor ou a quantidade forem inválidos, ou se não
     * houver quantidade suficiente daquela denominação no caixa.
     */
    public void retirarDinheiro(double valor, int quantidade) throws OperacaoCaixaException {
        if (quantidade <= 0) {
            throw new OperacaoCaixaException("A quantidade para retirar deve ser positiva.");
        }
        if (valor <= 0) {
            throw new OperacaoCaixaException("O valor da cédula/moeda deve ser positivo.");
        }
        if (gavetaDinheiro.getOrDefault(valor, 0) < quantidade) {
            throw new OperacaoCaixaException("Não há cédulas/moedas de R$ " + String.format("%.2f", valor) + " suficientes para retirar.");
        }
        gavetaDinheiro.merge(valor, -quantidade, Integer::sum);
    }

    /**
     * Calcula e fornece o troco para um determinado valor, utilizando um algoritmo guloso.
     * <p>
     * O método tenta compor o troco usando o menor número de cédulas/moedas possível,
     * priorizando as de maior valor. Se o troco for calculado com sucesso, as quantidades
     * são deduzidas da gaveta. Caso contrário, uma exceção é lançada e o estado da gaveta
     * permanece inalterado.
     * </p>
     * Este método também lida com imprecisões de ponto flutuante durante os cálculos.
     *
     * @param valorTroco O valor total do troco a ser fornecido.
     * @return Um mapa contendo as cédulas/moedas e as respectivas quantidades que compõem o troco.
     * @throws FaltaTrocoException Se o caixa não possuir as cédulas/moedas necessárias para
     * fornecer o troco exato.
     */
    public Map<Double, Integer> fornecerTroco(double valorTroco) throws FaltaTrocoException {
        Map<Double, Integer> trocoCalculado = new LinkedHashMap<>();
        double trocoRestante = valorTroco;

        Double[] valoresOrdenados = gavetaDinheiro.keySet().toArray(new Double[0]);
        Arrays.sort(valoresOrdenados, Collections.reverseOrder());

        for (double valorNota : valoresOrdenados) {
            if (trocoRestante < valorNota) {
                continue;
            }
            int qtdDisponivel = gavetaDinheiro.get(valorNota);
            int qtdNecessaria = (int) (trocoRestante / valorNota);

            if (qtdDisponivel > 0 && qtdNecessaria > 0) {
                int qtdAUsar = Math.min(qtdDisponivel, qtdNecessaria);
                trocoCalculado.put(valorNota, qtdAUsar);
                trocoRestante -= qtdAUsar * valorNota;
                trocoRestante = Math.round(trocoRestante * 100.0) / 100.0;
            }
        }

        // Verifica se foi possível calcular o troco exato (com uma pequena tolerância)
        if (trocoRestante > 0.001) {
            throw new FaltaTrocoException("Não há troco exato disponível. Faltou: R$ " + String.format("%.2f", trocoRestante));
        }

        // Se o troco foi calculado com sucesso, efetivamente remove o dinheiro da gaveta.
        trocoCalculado.forEach((valor, qtd) -> gavetaDinheiro.merge(valor, -qtd, Integer::sum));

        return trocoCalculado;
    }
}