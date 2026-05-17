package ui.admin;

import model.negocio.Caixa;
import model.excecoes.OperacaoCaixaException;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.Map;

/**
 * Representa uma janela de diálogo (JDialog) para o gerenciamento do caixa.
 * <p>
 * Esta tela permite ao administrador visualizar a quantidade de cada nota e moeda
 * disponível no caixa, além de realizar operações de abastecimento (adicionar dinheiro)
 * e retirada de valores.
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class TelaGestaoCaixa extends JDialog {

    private final Color COR_FUNDO = new Color(30, 30, 30);
    private final Color COR_TEXTO = new Color(220, 220, 220);
    private final Color COR_CAMPO = new Color(50, 50, 50);
    private final Color COR_BOTAO = new Color(60, 60, 60);

    /** A instância do gerenciador de caixa a ser manipulada. */
    private final Caixa caixa;
    /** A tabela Swing para exibir o conteúdo do caixa. */
    private final JTable tabelaCaixa;
    /** O modelo de dados para a tabela do caixa. */
    private final DefaultTableModel tableModel;

    /**
     * Renderer customizado para aplicar um estilo escuro ao cabeçalho da tabela.
     */
    private static class DarkHeaderRenderer extends DefaultTableCellRenderer {
        /**
         * Construtor do renderer.
         * Define a propriedade 'opaque' como true para que a cor de fundo seja desenhada.
         */
        public DarkHeaderRenderer() {
            setOpaque(true);
        }

        /**
         * Configura a aparência do componente de renderização do cabeçalho.
         *
         * @return O componente de cabeçalho estilizado.
         */
        @Override
        public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int col) {
            super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, col);
            setBackground(new Color(40, 40, 40));
            setForeground(new Color(220, 220, 220));
            setFont(new Font("Segoe UI", Font.BOLD, 12));
            setBorder(BorderFactory.createLineBorder(new Color(60, 60, 60)));
            setHorizontalAlignment(SwingConstants.CENTER);
            return this;
        }
    }

    /**
     * Construtor da tela de Gestão de Caixa.
     *
     * @param parent O JFrame pai ao qual este diálogo modal está associado.
     * @param caixa  A instância do {@link Caixa} que será gerenciada.
     */
    public TelaGestaoCaixa(JFrame parent, Caixa caixa) {
        super(parent, "Gestão de Caixa", true);
        this.caixa = caixa;

        // Configurações da Janela
        setSize(500, 400);
        setLocationRelativeTo(parent);
        getContentPane().setBackground(COR_FUNDO);
        setLayout(new BorderLayout());

        // Configuração da Tabela
        String[] colunas = {"Valor (R$)", "Quantidade"};
        tableModel = new DefaultTableModel(colunas, 0) {
            @Override
            public boolean isCellEditable(int r, int c) {
                return false;
            }
        };
        tabelaCaixa = new JTable(tableModel);
        estilizarTabela(tabelaCaixa);
        carregarTabela();

        // Painel de Botões
        JPanel painelBotoes = new JPanel();
        painelBotoes.setBackground(COR_FUNDO);

        JButton btnAbastecer = new JButton("Abastecer Caixa");
        personalizarBotao(btnAbastecer);
        btnAbastecer.addActionListener(e -> abastecer());

        JButton btnRetirar = new JButton("Retirar Valor");
        personalizarBotao(btnRetirar);
        btnRetirar.addActionListener(e -> retirar());

        painelBotoes.add(btnAbastecer);
        painelBotoes.add(btnRetirar);

        // Adiciona os componentes ao JDialog
        JScrollPane scrollPane = new JScrollPane(tabelaCaixa);
        scrollPane.getViewport().setBackground(COR_FUNDO);
        add(scrollPane, BorderLayout.CENTER);
        add(painelBotoes, BorderLayout.SOUTH);
    }

    /**
     * Inicia o fluxo para abastecer o caixa.
     * Solicita ao usuário o valor da nota/moeda e a quantidade, e então
     * chama o método de negócio para adicionar o dinheiro. Trata exceções
     * de formato e de regras de negócio.
     */
    private void abastecer() {
        String valorStr = JOptionPane.showInputDialog(this, "Digite o valor da nota/moeda (ex: 50.00, 0.50):", "Abastecer Caixa", JOptionPane.QUESTION_MESSAGE);
        if (valorStr == null || valorStr.trim().isEmpty()) return;

        String qtdStr = JOptionPane.showInputDialog(this, "Digite a quantidade:", "Abastecer Caixa", JOptionPane.QUESTION_MESSAGE);
        if (qtdStr == null || qtdStr.trim().isEmpty()) return;

        try {
            double valor = Double.parseDouble(valorStr.replace(",", "."));
            int qtd = Integer.parseInt(qtdStr);
            caixa.abastecerDinheiro(valor, qtd);
            carregarTabela();
        } catch (OperacaoCaixaException ex) {
            JOptionPane.showMessageDialog(this, "Erro ao abastecer: " + ex.getMessage(), "Erro de Operação", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Valor ou quantidade inválida.", "Erro de Formato", JOptionPane.ERROR_MESSAGE);
        }
    }

    /**
     * Inicia o fluxo para retirar dinheiro do caixa.
     * Solicita ao usuário o valor da nota/moeda e a quantidade a ser retirada,
     * e então chama o método de negócio correspondente. Trata exceções.
     */
    private void retirar() {
        String valorStr = JOptionPane.showInputDialog(this, "Digite o valor da nota/moeda a retirar:", "Retirar Valor", JOptionPane.QUESTION_MESSAGE);
        if (valorStr == null || valorStr.trim().isEmpty()) return;

        String qtdStr = JOptionPane.showInputDialog(this, "Digite a quantidade:", "Retirar Valor", JOptionPane.QUESTION_MESSAGE);
        if (qtdStr == null || qtdStr.trim().isEmpty()) return;

        try {
            double valor = Double.parseDouble(valorStr.replace(",", "."));
            int qtd = Integer.parseInt(qtdStr);
            caixa.retirarDinheiro(valor, qtd);
            carregarTabela();
        } catch (OperacaoCaixaException ex) {
            JOptionPane.showMessageDialog(this, "Erro ao retirar: " + ex.getMessage(), "Erro de Operação", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Valor ou quantidade inválida.", "Erro de Formato", JOptionPane.ERROR_MESSAGE);
        }
    }

    /**
     * Carrega (ou recarrega) os dados do caixa na tabela da interface.
     * Limpa a tabela e a preenche com as notas/moedas e suas respectivas
     * quantidades, ordenadas do maior valor para o menor.
     */
    private void carregarTabela() {
        tableModel.setRowCount(0);
        caixa.getGavetaDinheiro().entrySet().stream()
             .sorted(Map.Entry.<Double, Integer>comparingByKey().reversed())
             .forEach(entry -> tableModel.addRow(new Object[]{String.format("%.2f", entry.getKey()), entry.getValue()}));
    }

    /**
     * Aplica um estilo visual escuro e consistente a uma tabela.
     * @param tabela A {@link JTable} a ser estilizada.
     */
    private void estilizarTabela(JTable tabela) {
        tabela.setBackground(COR_CAMPO);
        tabela.setForeground(COR_TEXTO);
        tabela.setGridColor(new Color(80, 80, 80));
        tabela.setRowHeight(25);
        tabela.getTableHeader().setDefaultRenderer(new DarkHeaderRenderer());
        tabela.getTableHeader().setReorderingAllowed(false);
    }

    /**
     * Aplica um estilo visual padrão aos botões da tela.
     * @param botao O {@link JButton} a ser personalizado.
     */
    private void personalizarBotao(JButton botao) {
        botao.setBackground(COR_BOTAO);
        botao.setForeground(COR_TEXTO);
        botao.setOpaque(true);
        Border bordaLinha = BorderFactory.createLineBorder(new Color(90, 90, 90), 1);
        Border margemInterna = new EmptyBorder(5, 10, 5, 10);
        botao.setBorder(BorderFactory.createCompoundBorder(bordaLinha, margemInterna));
        botao.setFocusPainted(false);
    }
}