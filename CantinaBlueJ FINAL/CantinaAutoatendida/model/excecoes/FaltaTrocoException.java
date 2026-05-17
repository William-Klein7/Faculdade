package model.excecoes;

/**
 * Exceção lançada quando não há troco suficiente para completar uma transação.
 */

public class FaltaTrocoException extends Exception {
    
    /**
     * Construtor que cria a exceção com uma mensagem específica.
     *
     * @param message Mensagem detalhando o motivo da exceção.
     */

    public FaltaTrocoException(String message) { super(message); }
}
