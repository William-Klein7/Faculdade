package model.excecoes;

/**
 * Exceção lançada para indicar erros em operações do caixa,
 * tais como tentativas de retirada sem saldo suficiente
 * ou fornecimento de valores inválidos.
 */
public class OperacaoCaixaException extends Exception {
    
    /**
     * Construtor que cria a exceção com uma mensagem detalhada.
     *
     * @param message Mensagem explicando o motivo da exceção.
     */
    
    public OperacaoCaixaException(String message) {
        super(message);
    }
}