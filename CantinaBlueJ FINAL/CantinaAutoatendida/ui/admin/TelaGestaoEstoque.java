package ui.admin;

import java.awt.*;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import model.entidades.Bebida;
import model.entidades.Lanche;
import model.entidades.Produto;
import model.negocio.Estoque;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

/**
 * Representa uma janela de diálogo (JDialog) para o gerenciamento de estoque.
 * <p>
 * Esta tela permite ao administrador visualizar, adicionar, editar a quantidade e
 * remover produtos do estoque. Os produtos são exibidos em tabelas, com abas
 * separadas para visualização geral e para bebidas especificamente.
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class TelaGestaoEstoque extends JDialog {

    
    private final Color COR_FUNDO = new Color(30, 30, 30);
    private final Color COR_TEXTO = new Color(220, 220, 220);
    private final Color COR_CAMPO = new Color(50, 50, 50);
    private final Color COR_BOTAO = new Color(60, 60, 60);

    /** A instância do gerenciador de estoque a ser manipulada por esta tela. */
    private final Estoque estoque;
    /** A tabela Swing para exibir todos os produtos. */
    private final JTable tabelaProdutos;
    /** O modelo de dados para a tabela de produtos. */
    private final DefaultTableModel tableModel;

    
    

    /**
     * Renderer customizado para aplicar um estilo escuro ao cabeçalho das tabelas.
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
     * Construtor da tela de Gestão de Estoque.
     *
     * @param parent  O JFrame pai ao qual este diálogo modal está associado.
     * @param estoque A instância do {@link Estoque} que será gerenciada.
     */
    public TelaGestaoEstoque(JFrame parent, Estoque estoque) {
        super(parent, "Gestão de Estoque", true);
        this.estoque = estoque;

        setSize(800, 600);
        setLocationRelativeTo(parent);
        getContentPane().setBackground(COR_FUNDO);
        setLayout(new BorderLayout());

        // Painel de botões na parte inferior
        JPanel painelBotoes = new JPanel();
        painelBotoes.setBackground(COR_FUNDO);

        JButton btnAdicionar = new JButton("Adicionar Produto");
        personalizarBotao(btnAdicionar);
        btnAdicionar.addActionListener(e -> adicionarProduto());

        JButton btnEditarQtd = new JButton("Editar Quantidade");
        personalizarBotao(btnEditarQtd);
        btnEditarQtd.addActionListener(e -> editarQuantidade());

        JButton btnRemover = new JButton("Remover Produto");
        personalizarBotao(btnRemover);
        btnRemover.addActionListener(e -> removerProduto());

        painelBotoes.add(btnAdicionar);
        painelBotoes.add(btnEditarQtd);
        painelBotoes.add(btnRemover);
        add(painelBotoes, BorderLayout.SOUTH);

        // Configuração das tabelas
        String[] colunasProdutos = {"Nome", "Preço", "Quantidade", "Categoria", "Validade"};
        tableModel = new DefaultTableModel(colunasProdutos, 0);
        tabelaProdutos = new JTable(tableModel);
        estilizarTabela(tabelaProdutos);

        JTabbedPane abas = new JTabbedPane();
        abas.addTab("Todos os Produtos", new JScrollPane(tabelaProdutos));
        add(abas, BorderLayout.CENTER);

        carregarTabela();
    }

    /**
     * Carrega (ou recarrega) os dados do estoque nas tabelas da interface.
     * Limpa as tabelas e as preenche com os produtos atuais do estoque.
     */
    private void carregarTabela() {
        tableModel.setRowCount(0);
        
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");

        for (Produto p : estoque.getProdutos()) {
            Object[] linhaGeral = {
                p.getNome(),
                String.format("%.2f", p.getPreco()),
                p.getQuantidade(),
                p.getCategoria(),
                p.getDataValidade().format(formatter)
            };
            tableModel.addRow(linhaGeral);

        }
    }

    /**
     * Inicia o fluxo de adição de um novo produto.
     * Pergunta ao usuário o tipo de produto (Lanche ou Bebida) e chama o método correspondente.
     */
    private void adicionarProduto() {
        Object[] options = {"Lanche", "Bebida"};
        int tipoProduto = JOptionPane.showOptionDialog(this, "Qual tipo de produto você deseja adicionar?", "Selecionar Tipo de Produto", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[0]);
        if (tipoProduto == JOptionPane.CLOSED_OPTION) return;
        if (tipoProduto == 0) {
            adicionarLanche();
        } else {
            adicionarBebida();
        }
    }

    /**
     * Exibe um diálogo para coletar os dados e adicionar um novo lanche ao estoque.
     */
    private void adicionarLanche() {
        JTextField nomeField = new JTextField();
        JTextField precoField = new JTextField();
        JTextField qtdField = new JTextField();
        JTextField valField = new JTextField("dd/MM/yyyy");
        estilizarCampos(new JComponent[]{nomeField, precoField, qtdField, valField});
        Object[] message = {"Nome:", nomeField, "Preço (ex: 9.99):", precoField, "Quantidade:", qtdField, "Validade (dd/MM/yyyy):", valField};
        int option = JOptionPane.showConfirmDialog(this, message, "Adicionar Novo Lanche", JOptionPane.OK_CANCEL_OPTION);
        if (option == JOptionPane.OK_OPTION) {
            try {
                String nome = nomeField.getText();
                double preco = Double.parseDouble(precoField.getText().replace(",", "."));
                int qtd = Integer.parseInt(qtdField.getText());
                if (preco < 0 || qtd < 0) throw new IllegalArgumentException("Valores não podem ser negativos.");
                LocalDate val = LocalDate.parse(valField.getText(), DateTimeFormatter.ofPattern("dd/MM/yyyy"));
                estoque.adicionarProduto(new Lanche(nome, preco, qtd, val));
                carregarTabela();
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Dados inválidos. Verifique os valores e o formato da data.\n" + ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    /**
     * Exibe um diálogo para coletar os dados e adicionar uma nova bebida ao estoque.
     */
    private void adicionarBebida() {
        JTextField nomeField = new JTextField();
        JTextField precoField = new JTextField();
        JTextField qtdField = new JTextField();
        JTextField valField = new JTextField("dd/MM/yyyy");
        JTextField volField = new JTextField();
        estilizarCampos(new JComponent[]{nomeField, precoField, qtdField, valField, volField});
        Object[] message = {"Nome:", nomeField, "Preço (ex: 9.99):", precoField, "Quantidade:", qtdField, "Validade (dd/MM/yyyy):", valField, "Volume (ml):", volField};
        int option = JOptionPane.showConfirmDialog(this, message, "Adicionar Nova Bebida", JOptionPane.OK_CANCEL_OPTION);
        if (option == JOptionPane.OK_OPTION) {
            try {
                String nome = nomeField.getText();
                double preco = Double.parseDouble(precoField.getText().replace(",", "."));
                int qtd = Integer.parseInt(qtdField.getText());
                int vol = Integer.parseInt(volField.getText());
                if (preco < 0 || qtd < 0 || vol <= 0) throw new IllegalArgumentException("Valores inválidos. Preço e quantidade não podem ser negativos e volume deve ser positivo.");
                LocalDate val = LocalDate.parse(valField.getText(), DateTimeFormatter.ofPattern("dd/MM/yyyy"));
                estoque.adicionarProduto(new Bebida(nome, preco, qtd, val, vol));
                carregarTabela();
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Dados inválidos. Verifique os valores e o formato da data.\n" + ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    /**
     * Permite a edição da quantidade de um produto selecionado na tabela.
     */

    private void editarQuantidade() {
        int selectedRow = tabelaProdutos.getSelectedRow();
        if (selectedRow == -1) {
            JOptionPane.showMessageDialog(this, "Selecione um produto.", "Aviso", JOptionPane.WARNING_MESSAGE);
            return;
          }
  
        String nomeProduto = (String) tableModel.getValueAt(selectedRow, 0);
        String novaQtdStr = JOptionPane.showInputDialog(this, "Nova quantidade para " + nomeProduto + ":", "Editar Quantidade", JOptionPane.QUESTION_MESSAGE);
        if (novaQtdStr != null) {
            try {
                int novaQtd = Integer.parseInt(novaQtdStr);
                if (novaQtd < 0) throw new NumberFormatException("Quantidade não pode ser negativa.");
                estoque.buscarProdutoPorNome(nomeProduto).ifPresent(p -> {
                    int diferenca = novaQtd - p.getQuantidade();
                    p.adicionarEstoque(diferenca);
                });
                carregarTabela();
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Quantidade inválida.", "Erro", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
    /**
     * Remove um produto selecionado na tabela, após confirmação do usuário.
     */
    private void removerProduto() {
        int selectedRow = tabelaProdutos.getSelectedRow();
        if (selectedRow == -1) {
            JOptionPane.showMessageDialog(this, "Selecione um produto para remover.", "Aviso", JOptionPane.WARNING_MESSAGE);
            return;
        }
        String nomeProduto = (String) tableModel.getValueAt(selectedRow, 0);
        int confirm = JOptionPane.showConfirmDialog(this, "Tem certeza que deseja remover o produto '" + nomeProduto + "'?", "Confirmar Remoção", JOptionPane.YES_NO_OPTION, JOptionPane.WARNING_MESSAGE);
        if (confirm == JOptionPane.YES_OPTION) {
            estoque.removerProduto(nomeProduto);
            carregarTabela();
        }
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

    /**
     * Aplica um estilo visual padrão a um conjunto de componentes, como campos de texto.
     * @param components Um array de {@link JComponent} a serem estilizados.
     */
    private void estilizarCampos(JComponent[] components) {
        for (JComponent component : components) {
            component.setBackground(COR_CAMPO);
            component.setForeground(COR_TEXTO);
            if (component instanceof JTextField textField) {
                textField.setCaretColor(COR_TEXTO);
                textField.setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createLineBorder(new Color(80, 80, 80)),
                    new EmptyBorder(2, 5, 2, 5)
                ));
            }
        }
    }
}
