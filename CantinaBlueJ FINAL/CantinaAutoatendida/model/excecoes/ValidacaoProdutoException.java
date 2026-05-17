package model.excecoes;

/**
 * Exceção lançada quando um dado de produto é inválido
 * (ex: preço negativo, nome duplicado, etc.).
 */
public class ValidacaoProdutoException extends Exception {
    
    /**
     * Construtor que cria a exceção com uma mensagem específica.
     *
     * @param message Mensagem detalhando o motivo da exceção.
     */
    
    public ValidacaoProdutoException(String message) {
        super(message);
    }
}
