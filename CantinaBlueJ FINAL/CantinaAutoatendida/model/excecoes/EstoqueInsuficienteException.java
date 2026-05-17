package model.excecoes;

/**
 * Exceção lançada quando a quantidade solicitada de um produto
 * é maior do que a disponível no estoque.
 */
public class EstoqueInsuficienteException extends Exception {
    
    /**
     * Construtor que cria a exceção com uma mensagem específica.
     *
     * @param message Mensagem detalhando o motivo da exceção.
     */
    
    public EstoqueInsuficienteException(String message) { super(message); }
}
