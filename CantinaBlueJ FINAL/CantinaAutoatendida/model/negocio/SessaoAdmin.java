package model.negocio;

/**
 * Gerencia a lógica de autenticação para o acesso administrativo do sistema.
 * <p>
 * Esta classe fornece um mecanismo simples para validar as credenciais de um
 * usuário administrador contra valores pré-definidos e constantes.
 * </p>
 * <p>
 * <strong>Aviso de Segurança:</strong> Esta implementação utiliza credenciais
 * fixas no código ("hardcoded") e serve apenas para fins de demonstração ou
 * aplicações muito simples. Não é uma prática segura para ambientes de produção,
 * pois as credenciais ficam expostas no código-fonte.
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class SessaoAdmin {

    /** O nome de usuário correto e fixo para o administrador. */
    private static final String USUARIO_CORRETO = "admin";

    /** A senha correta e fixa para o administrador. */
    private static final String SENHA_CORRETA = "1234";

    /**
     * Valida as credenciais fornecidas pelo usuário.
     * <p>
     * Compara o usuário e a senha recebidos como parâmetro com as constantes
     * internas {@code USUARIO_CORRETO} e {@code SENHA_CORRETA}.
     * </p>
     *
     * @param usuario O nome de usuário a ser verificado.
     * @param senha   A senha a ser verificada.
     * @return {@code true} se o usuário e a senha corresponderem exatamente aos
     * valores corretos, {@code false} caso contrário.
     */
    public boolean autenticar(String usuario, String senha) {
        return USUARIO_CORRETO.equals(usuario) && SENHA_CORRETA.equals(senha);
    }
}