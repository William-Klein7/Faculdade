package ui.admin;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import model.entidades.Pedido;
import model.negocio.Caixa;
import model.negocio.Estoque;
import ui.cliente.TelaPrincipalCliente;
import java.util.List;

/**
 * Representa o painel de navegação principal para as funções administrativas do sistema.
 * Esta janela (JFrame) serve como um dashboard, oferecendo acesso às telas de
 * gerenciamento de estoque, gerenciamento de caixa e visualização de relatórios.
 * <p>
 * Uma funcionalidade importante é que, ao fechar esta janela, a tela principal do
 * cliente é atualizada para refletir quaisquer mudanças feitas (ex: adição de novos produtos).
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class PainelAdmin extends JFrame {

    /** Cor de fundo principal para o painel. */
    private final Color COR_FUNDO = new Color(30, 30, 30);
    /** Cor padrão para o texto dos componentes. */
    private final Color COR_TEXTO = new Color(220, 220, 220);
    /** Cor de fundo para os botões. */
    private final Color COR_BOTAO = new Color(50, 50, 50);
    /** Cor da borda dos botões. */
    private final Color COR_BORDA_BOTAO = new Color(80, 80, 80);

    /**
     * Construtor do Painel Administrativo.
     * <p>
     * Configura a janela e cria os botões de navegação para as diferentes seções
     * administrativas. Adiciona um listener que atualiza a tela de cliente
     * {@code parent} sempre que esta janela administrativa é fechada, garantindo que
     * as alterações no estoque sejam refletidas imediatamente na interface do cliente.
     *
     * @param parent          A instância da {@link TelaPrincipalCliente}, que será atualizada ao fechar este painel.
     * @param estoque         A instância do gerenciador de {@link Estoque}, passada para as telas de gestão e relatórios.
     * @param caixa           A instância do gerenciador de {@link Caixa}, passada para a tela de gestão de caixa.
     * @param historicoVendas A lista de {@link Pedido} que representa o histórico de vendas, passada para a tela de relatórios.
     */
    public PainelAdmin(TelaPrincipalCliente parent, Estoque estoque, Caixa caixa, List<Pedido> historicoVendas) {
        setTitle("Painel Administrativo");
        setSize(500, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        
        JPanel painel = new JPanel(new GridLayout(3, 1, 20, 20));
        painel.setBorder(new EmptyBorder(30, 30, 30, 30));
        painel.setBackground(COR_FUNDO);

       
        JButton btnGestaoEstoque = new JButton("Gerenciar Estoque de Produtos");
        personalizarBotao(btnGestaoEstoque);
        btnGestaoEstoque.addActionListener(e -> new TelaGestaoEstoque(this, estoque).setVisible(true));

       
        JButton btnGestaoCaixa = new JButton("Gerenciar Caixa (Dinheiro)");
        personalizarBotao(btnGestaoCaixa);
        btnGestaoCaixa.addActionListener(e -> new TelaGestaoCaixa(this, caixa).setVisible(true));

       
        JButton btnRelatorios = new JButton("Visualizar Relatórios");
        personalizarBotao(btnRelatorios);
        btnRelatorios.addActionListener(e -> new TelaRelatorios(this, estoque, historicoVendas).setVisible(true));

        painel.add(btnGestaoEstoque);
        painel.add(btnGestaoCaixa);
        painel.add(btnRelatorios);

        add(painel);

        this.addWindowListener(new WindowAdapter() {
            /**
             * Invocado quando a janela é fechada.
             * Chama o método para recarregar os produtos na tela do cliente.
             * @param e o evento de janela.
             */
            @Override
            public void windowClosed(WindowEvent e) {
                parent.carregarPainelProdutos();
            }
        });
    }

    /**
     * Método auxiliar para aplicar um estilo visual consistente aos botões do painel.
     *
     * @param botao O {@link JButton} a ser personalizado.
     */
    private void personalizarBotao(JButton botao) {
        botao.setFont(new Font("Segoe UI", Font.BOLD, 16));
        botao.setBackground(COR_BOTAO);
        botao.setForeground(COR_TEXTO);
        botao.setOpaque(true);

        Border bordaLinha = BorderFactory.createLineBorder(COR_BORDA_BOTAO, 1);
        Border margemInterna = new EmptyBorder(10, 15, 10, 15);
        botao.setBorder(BorderFactory.createCompoundBorder(bordaLinha, margemInterna));
        botao.setFocusPainted(false);
    }
}