package ui.admin;

import java.awt.*;
import javax.swing.*;
import model.entidades.Pedido;
import model.negocio.Estoque;
import model.negocio.GeradorRelatorios;
import java.util.List;

/**
 * Representa uma janela de diálogo (JDialog) para a visualização de relatórios do sistema.
 * Esta tela é destinada ao uso administrativo, permitindo a seleção e exibição de diferentes
 * tipos de relatórios, como transações de vendas, produtos mais vendidos, horários de pico,
 * e controle de validade do estoque.
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class TelaRelatorios extends JDialog {


    /** Cor de fundo padrão para a janela e painéis. */
    private final Color COR_FUNDO = new Color(30, 30, 30);
    /** Cor padrão para textos e rótulos. */
    private final Color COR_TEXTO = new Color(220, 220, 220);
    /** Cor de fundo para campos de texto e caixas de seleção. */
    private final Color COR_CAMPO = new Color(50, 50, 50);
    /** Instância da classe responsável por gerar a lógica e o conteúdo dos relatórios. */
    private final GeradorRelatorios gerador;
    /** Área de texto onde o conteúdo do relatório gerado é exibido. */
    private final JTextArea areaRelatorio;

    /**
     * Construtor da tela de relatórios.
     * Inicializa a janela de diálogo, configura seus componentes visuais e define
     * os listeners para gerar relatórios com base na seleção do usuário.
     *
     * @param parent          O JFrame pai sobre o qual este diálogo será exibido.
     * O diálogo será modal em relação a este pai.
     * @param estoque         A instância do gerenciador de estoque, necessária para
     * gerar relatórios relacionados a produtos (ex: validade).
     * @param historicoVendas A lista de pedidos finalizados (histórico de vendas),
     * utilizada para gerar relatórios de transações e performance.
     */
    public TelaRelatorios(JFrame parent, Estoque estoque, List<Pedido> historicoVendas) {
        super(parent, "Relatórios do Sistema", true);
        this.gerador = new GeradorRelatorios();

        // Configurações básicas do JDialog
        setSize(700, 500);
        setLocationRelativeTo(parent);
        getContentPane().setBackground(COR_FUNDO);
        setLayout(new BorderLayout());

        // Painel superior com a caixa de seleção de relatórios
        JPanel painelSelecao = new JPanel();
        painelSelecao.setBackground(COR_FUNDO);

        String[] tiposRelatorio = {
            "Selecione um relatório...",
            "Todas as Transações",
            "Produtos Mais Vendidos",
            "Horários de Maior Movimento",
            "Controle de Validade"
        };
        JComboBox<String> comboRelatorios = new JComboBox<>(tiposRelatorio);
        comboRelatorios.setBackground(COR_CAMPO);
        comboRelatorios.setForeground(COR_TEXTO);
        painelSelecao.add(comboRelatorios);

        // Área de texto para exibir o relatório
        areaRelatorio = new JTextArea();
        areaRelatorio.setEditable(false);
        areaRelatorio.setFont(new Font("Monospaced", Font.PLAIN, 12));
        areaRelatorio.setBackground(COR_CAMPO);
        areaRelatorio.setForeground(COR_TEXTO);
        areaRelatorio.setCaretColor(COR_TEXTO);
        areaRelatorio.setMargin(new Insets(10, 10, 10, 10));

        comboRelatorios.addActionListener(e -> {
            String selecionado = (String) comboRelatorios.getSelectedItem();
            String relatorioGerado = "";

            if (selecionado == null) return;

            switch (selecionado) {
                case "Todas as Transações":
                    relatorioGerado = gerador.gerarRelatorioTransacoes(historicoVendas);
                    break;
                case "Produtos Mais Vendidos":
                    relatorioGerado = gerador.gerarRelatorioMaisVendidos(historicoVendas);
                    break;
                case "Horários de Maior Movimento":
                    relatorioGerado = gerador.gerarRelatorioHorarioDePico(historicoVendas);
                    break;
                case "Controle de Validade":
                    relatorioGerado = gerador.gerarRelatorioDeValidade(estoque);
                    break;
                default:
                    relatorioGerado = "Por favor, selecione uma opção de relatório válida.";
                    break;
            }
            areaRelatorio.setText(relatorioGerado);
            areaRelatorio.setCaretPosition(0); 
        });

        JScrollPane scrollPane = new JScrollPane(areaRelatorio);
        scrollPane.getViewport().setBackground(COR_CAMPO);
        scrollPane.setBorder(BorderFactory.createLineBorder(COR_FUNDO, 5));
        add(painelSelecao, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }
}
