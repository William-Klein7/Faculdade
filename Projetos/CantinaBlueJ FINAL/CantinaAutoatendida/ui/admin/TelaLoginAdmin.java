package ui.admin;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;
import model.entidades.Pedido;
import model.negocio.Caixa;
import model.negocio.Estoque;
import model.negocio.SessaoAdmin;
import ui.cliente.TelaPrincipalCliente;
import java.util.List;

/**
 * Representa a janela de diálogo (JDialog) para o login do administrador.
 * <p>
 * Esta tela modal solicita um nome de usuário e senha. Após a autenticação
 * bem-sucedida através da classe {@link SessaoAdmin}, ela fecha a si mesma e
 * abre o {@link PainelAdmin}, concedendo acesso às funcionalidades administrativas.
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class TelaLoginAdmin extends JDialog {

    /** Cor de fundo principal para o painel de login. */
    private final Color COR_FUNDO = new Color(30, 30, 30);
    /** Cor padrão para o texto dos componentes. */
    private final Color COR_TEXTO = new Color(220, 220, 220);
    /** Cor de fundo para os campos de texto. */
    private final Color COR_CAMPO = new Color(50, 50, 50);

    /**
     * Construtor da tela de login administrativo.
     * <p>
     * Configura a janela de diálogo modal com campos para usuário e senha.
     * O botão de login utiliza a classe {@link SessaoAdmin} para validar as credenciais.
     * Se o login for bem-sucedido, esta janela é fechada e o {@link PainelAdmin} é exibido.
     *
     * @param parent          A instância da {@link TelaPrincipalCliente}, que serve como janela pai.
     * @param estoque         A instância do {@link Estoque} a ser passada para o painel admin.
     * @param caixa           A instância do {@link Caixa} a ser passada para o painel admin.
     * @param historicoVendas A lista de {@link Pedido} (histórico de vendas) a ser passada para o painel admin.
     */
    public TelaLoginAdmin(TelaPrincipalCliente parent, Estoque estoque, Caixa caixa, List<Pedido> historicoVendas) {
        super(parent, "Acesso Administrativo", true);

        SessaoAdmin sessao = new SessaoAdmin();


        JPanel painel = new JPanel(new GridBagLayout());
        painel.setBackground(COR_FUNDO);
        painel.setBorder(new EmptyBorder(20, 20, 20, 20));

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        JLabel labelUsuario = new JLabel("Usuário:");
        labelUsuario.setForeground(COR_TEXTO);
        gbc.gridx = 0;
        gbc.gridy = 0;
        painel.add(labelUsuario, gbc);

        JTextField txtUsuario = new JTextField(20);
        txtUsuario.setBackground(COR_CAMPO);
        txtUsuario.setForeground(COR_TEXTO);
        txtUsuario.setCaretColor(COR_TEXTO);
        gbc.gridx = 1;
        painel.add(txtUsuario, gbc);
        JLabel labelSenha = new JLabel("Senha:");
        labelSenha.setForeground(COR_TEXTO);
        gbc.gridx = 0;
        gbc.gridy = 1;
        painel.add(labelSenha, gbc);

        JPasswordField txtSenha = new JPasswordField(20);
        txtSenha.setBackground(COR_CAMPO);
        txtSenha.setForeground(COR_TEXTO);
        txtSenha.setCaretColor(COR_TEXTO);
        gbc.gridx = 1;
        painel.add(txtSenha, gbc);

        // Botão de Login e sua ação
        JButton btnLogin = new JButton("Login");
        btnLogin.setBackground(new Color(60, 60, 60));
        btnLogin.setForeground(COR_TEXTO);
        btnLogin.setOpaque(true);
        btnLogin.setFocusPainted(false);
        btnLogin.addActionListener(e -> {
            String usuario = txtUsuario.getText();
            String senha = new String(txtSenha.getPassword());

            if (sessao.autenticar(usuario, senha)) {
                dispose();
                new PainelAdmin(parent, estoque, caixa, historicoVendas).setVisible(true);
            } else {
                JOptionPane.showMessageDialog(this, "Usuário ou senha inválidos.", "Erro de Acesso", JOptionPane.ERROR_MESSAGE);
            }
        });

        gbc.gridx = 1;
        gbc.gridy = 2;
        gbc.anchor = GridBagConstraints.EAST;
        gbc.fill = GridBagConstraints.NONE;
        painel.add(btnLogin, gbc);
        add(painel);
        pack();
        setLocationRelativeTo(parent);
    }
}
