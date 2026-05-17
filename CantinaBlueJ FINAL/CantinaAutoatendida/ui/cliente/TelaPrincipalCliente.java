package ui.cliente;

import model.entidades.*;
import model.excecoes.*;
import model.negocio.*;
import ui.admin.TelaLoginAdmin;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;

/**
 * Representa a tela principal de autoatendimento para o cliente da cantina.
 * Nesta tela, o cliente pode visualizar os produtos disponíveis, adicioná-los
 * a um carrinho de compras, finalizar a compra e realizar o pagamento.
 * A interface também fornece um ponto de acesso para a tela de login do administrador.
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class TelaPrincipalCliente extends JFrame {


    private final Color COR_FUNDO_JANELA = new Color(30, 30, 30);
    private final Color COR_FUNDO_PAINEL = new Color(50, 50, 50);
    private final Color COR_FUNDO_ITEM_CARRINHO = new Color(45, 45, 45);
    private final Color COR_BOTAO_REMOVER = new Color(194, 54, 22);
    private final Color COR_BOTAO_DESTAQUE = new Color(30, 144, 255);
    private final Color COR_TEXTO_GERAL = new Color(220, 220, 220);
    private final Color COR_BORDA_BOTAO = new Color(80, 80, 80);


    /** Gerenciador do estoque de produtos da cantina. */
    private final Estoque estoque;
    /** Gerenciador do caixa, responsável por troco e pagamentos. */
    private final Caixa caixa;
    /** Lista que armazena o histórico de todos os pedidos finalizados. */
    private final List<Pedido> historicoVendas;
    /** O pedido que o cliente está montando atualmente. */
    private Pedido pedidoAtual;
    /** Painel que exibe os botões dos produtos disponíveis para compra. */
    private final JPanel painelProdutos;
    /** Painel que exibe os itens adicionados ao pedido atual (carrinho). */
    private final JPanel painelItensCarrinho;
    /** Rótulo que exibe o valor total do pedido atual. */
    private final JLabel labelTotal;


    /**
     * Construtor da tela principal do cliente.
     * Inicializa os componentes da interface gráfica, configura os layouts,
     * e associa as instâncias de Estoque e Caixa para a operação da tela.
     *
     * @param estoque A instância do gerenciador de estoque a ser utilizada.
     * @param caixa A instância do gerenciador de caixa a ser utilizada.
     */
    public TelaPrincipalCliente(Estoque estoque, Caixa caixa) {
        this.estoque = estoque;
        this.caixa = caixa;
        this.historicoVendas = new ArrayList<>();
        this.pedidoAtual = new Pedido();

        // Configurações da janela principal (JFrame)
        setTitle("Cantina Universitária - Autoatendimento");
        setSize(1200, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        getContentPane().setBackground(COR_FUNDO_JANELA);

        // Painel de Produtos (à esquerda/centro)
        painelProdutos = new JPanel(new GridLayout(0, 3, 10, 10));
        painelProdutos.setBackground(COR_FUNDO_JANELA);
        painelProdutos.setBorder(new EmptyBorder(10, 10, 10, 10));
        carregarPainelProdutos();
        JScrollPane scrollProdutos = new JScrollPane(painelProdutos);
        scrollProdutos.getViewport().setBackground(COR_FUNDO_JANELA);
        scrollProdutos.setBorder(BorderFactory.createEmptyBorder());

        // Painel do Carrinho (à direita)
        JPanel painelDireito = new JPanel(new BorderLayout(10, 10));
        painelDireito.setBackground(COR_FUNDO_JANELA);
        painelDireito.setBorder(new EmptyBorder(10, 10, 10, 10));

        JLabel tituloCarrinho = new JLabel("Seu Pedido:");
        tituloCarrinho.setForeground(COR_TEXTO_GERAL);
        tituloCarrinho.setFont(new Font("Segoe UI", Font.BOLD, 16));

        painelItensCarrinho = new JPanel();
        painelItensCarrinho.setBackground(COR_FUNDO_JANELA);
        painelItensCarrinho.setLayout(new BoxLayout(painelItensCarrinho, BoxLayout.Y_AXIS));

        JScrollPane scrollCarrinho = new JScrollPane(painelItensCarrinho);
        scrollCarrinho.getViewport().setBackground(COR_FUNDO_JANELA);
        scrollCarrinho.setBorder(new LineBorder(COR_BORDA_BOTAO));

        // Painel inferior do carrinho (Total e Botões de Ação)
        JPanel painelSulCarrinho = new JPanel(new BorderLayout(0, 10));
        painelSulCarrinho.setBackground(COR_FUNDO_JANELA);

        labelTotal = new JLabel("TOTAL: R$ 0.00");
        labelTotal.setForeground(COR_TEXTO_GERAL);
        labelTotal.setFont(new Font("Segoe UI", Font.BOLD, 18));

        JPanel painelBotoesAcao = new JPanel(new GridLayout(1, 2, 10, 0));
        painelBotoesAcao.setOpaque(false);

        JButton btnCancelar = new JButton("Cancelar");
        personalizarBotao(btnCancelar, COR_FUNDO_PAINEL, COR_TEXTO_GERAL, false);
        btnCancelar.addActionListener(e -> cancelarCompra());

        JButton btnFinalizar = new JButton("Finalizar Compra");
        personalizarBotao(btnFinalizar, COR_BOTAO_DESTAQUE, Color.WHITE, true);
        btnFinalizar.addActionListener(e -> abrirTelaPagamento());

        painelBotoesAcao.add(btnCancelar);
        painelBotoesAcao.add(btnFinalizar);

        painelSulCarrinho.add(labelTotal, BorderLayout.NORTH);
        painelSulCarrinho.add(painelBotoesAcao, BorderLayout.SOUTH);

        painelDireito.add(tituloCarrinho, BorderLayout.NORTH);
        painelDireito.add(scrollCarrinho, BorderLayout.CENTER);
        painelDireito.add(painelSulCarrinho, BorderLayout.SOUTH);

        // Painel de Acesso do Administrador (inferior)
        JPanel painelAdmin = new JPanel(new FlowLayout(FlowLayout.LEFT));
        painelAdmin.setBackground(COR_FUNDO_JANELA);
        JButton btnAdmin = new JButton("Admin");
        personalizarBotao(btnAdmin, COR_FUNDO_PAINEL, COR_TEXTO_GERAL, false);
        btnAdmin.addActionListener(e -> new TelaLoginAdmin(this, estoque, caixa, historicoVendas).setVisible(true));
        painelAdmin.add(btnAdmin);

        // Adiciona os painéis principais ao JFrame
        add(scrollProdutos, BorderLayout.CENTER);
        add(painelDireito, BorderLayout.EAST);
        add(painelAdmin, BorderLayout.SOUTH);

        atualizarCarrinho();
    }

    /**
     * Carrega ou recarrega o painel de produtos.
     * Limpa o painel existente e o preenche com botões para cada produto disponível no estoque.
     * Produtos esgotados são exibidos, mas desabilitados.
     */
    public void carregarPainelProdutos() {
        painelProdutos.removeAll();

        estoque.listarProdutosDisponiveis().forEach(produto -> {
            String textoBotao;

            // Verifica se o produto é uma bebida para incluir o volume no texto
            if (produto instanceof Bebida bebida) {
                textoBotao = "<html><center>" +
                        bebida.getNome() + " (" + bebida.getVolumeMl() + " mL)" + "<br><b>R$ " +
                        String.format("%.2f", bebida.getPreco()) + "</b><br><font size='-2' color='#AAAAAA'>" +
                        "Disponível: " + bebida.getQuantidade() + "</font></center></html>";
            } else {
                textoBotao = "<html><center>" +
                        produto.getNome() + "<br><b>R$ " +
                        String.format("%.2f", produto.getPreco()) + "</b><br><font size='-2' color='#AAAAAA'>" +
                        "Disponível: " + produto.getQuantidade() + "</font></center></html>";
            }

            JButton btnProduto = new JButton(textoBotao);

            // Desabilita e altera o texto se o produto estiver esgotado
            if (produto.getQuantidade() == 0) {
                btnProduto.setEnabled(false);
                String textoEsgotado = "<html><center>" + produto.getNome();
                if (produto instanceof Bebida bebida) {
                    textoEsgotado += " (" + bebida.getVolumeMl() + " mL)";
                }
                textoEsgotado += "<br><font color='red'>ESGOTADO</font></center></html>";
                btnProduto.setText(textoEsgotado);
            }

            personalizarBotao(btnProduto, COR_FUNDO_PAINEL, COR_TEXTO_GERAL, false);
            btnProduto.addActionListener(e -> solicitarQuantidadeEAdicionar(produto));
            painelProdutos.add(btnProduto);
        });

        painelProdutos.revalidate();
        painelProdutos.repaint();
    }

    /**
     * Atualiza a exibição do painel do carrinho de compras.
     * Limpa o painel e o reconstrói com base nos itens do {@code pedidoAtual}.
     * Também atualiza o rótulo do valor total.
     */
    private void atualizarCarrinho() {
        painelItensCarrinho.removeAll();
        for (ItemPedido item : pedidoAtual.getItens()) {
            JPanel linhaItem = new JPanel(new BorderLayout(10, 0));
            linhaItem.setBackground(COR_FUNDO_ITEM_CARRINHO);
            linhaItem.setBorder(BorderFactory.createCompoundBorder(new LineBorder(COR_FUNDO_JANELA, 2), new EmptyBorder(5, 5, 5, 5)));

            String infoTexto = String.format("<html>%s <font color='#AAAAAA'>x%d</font></html>", item.getProduto().getNome(), item.getQuantidade());
            JLabel labelInfo = new JLabel(infoTexto);
            labelInfo.setForeground(COR_TEXTO_GERAL);

            JButton btnRemover = new JButton("X");
            personalizarBotaoRemover(btnRemover);
            btnRemover.addActionListener(e -> {
                pedidoAtual.removerItem(item.getProduto());
                atualizarCarrinho();
            });

            linhaItem.add(labelInfo, BorderLayout.CENTER);
            linhaItem.add(btnRemover, BorderLayout.EAST);
            painelItensCarrinho.add(linhaItem);
        }

        // Adiciona um "filler" para empurrar os itens para cima
        JPanel filler = new JPanel();
        filler.setOpaque(false);
        filler.setPreferredSize(new Dimension(0, 10000));
        painelItensCarrinho.add(filler);

        labelTotal.setText(String.format("TOTAL: R$ %.2f", pedidoAtual.getValorTotal()));
        painelItensCarrinho.revalidate();
        painelItensCarrinho.repaint();
    }

    /**
     * Exibe um diálogo para o usuário inserir a quantidade de um produto selecionado.
     * Após a inserção, valida o valor e, se for válido, chama o método para adicionar o produto ao carrinho.
     *
     * @param produto O produto para o qual a quantidade será solicitada.
     */
    private void solicitarQuantidadeEAdicionar(Produto produto) {
        String qtdStr = JOptionPane.showInputDialog(this, "Digite a quantidade desejada para:\n" + produto.getNome(), "Adicionar ao Carrinho", JOptionPane.QUESTION_MESSAGE);
        if (qtdStr == null) return;

        try {
            int quantidade = Integer.parseInt(qtdStr);
            if (quantidade <= 0) {
                JOptionPane.showMessageDialog(this, "A quantidade deve ser um número positivo.", "Quantidade Inválida", JOptionPane.WARNING_MESSAGE);
                return;
            }
            adicionarProdutoAoCarrinho(produto, quantidade);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Por favor, digite um número válido.", "Erro de Formato", JOptionPane.ERROR_MESSAGE);
        }
    }

    /**
     * Adiciona um produto com a quantidade especificada ao pedido atual.
     * Trata a exceção de estoque insuficiente exibindo uma mensagem de aviso.
     *
     * @param produto    O produto a ser adicionado.
     * @param quantidade A quantidade desejada do produto.
     */
    private void adicionarProdutoAoCarrinho(Produto produto, int quantidade) {
        try {
            pedidoAtual.adicionarItem(produto, quantidade);
            atualizarCarrinho();
        } catch (EstoqueInsuficienteException e) {
            JOptionPane.showMessageDialog(this, e.getMessage(), "Estoque Insuficiente", JOptionPane.WARNING_MESSAGE);
        }
    }

    /**
     * Inicia o processo de pagamento.
     * Verifica se o carrinho não está vazio, solicita o valor pago pelo cliente,
     * calcula o troco, finaliza a venda (atualizando estoque e histórico) e reinicia o pedido.
     * Trata exceções de formato de número e falta de troco.
     */
    private void abrirTelaPagamento() {
        if (pedidoAtual.getItens().isEmpty()) {
            JOptionPane.showMessageDialog(this, "Seu carrinho está vazio!", "Aviso", JOptionPane.INFORMATION_MESSAGE);
            return;
        }

        String valorPagoStr = JOptionPane.showInputDialog(this, "Total a pagar: R$ " + String.format("%.2f", pedidoAtual.getValorTotal()) + "\n\nDigite o valor entregue pelo cliente:", "Pagamento", JOptionPane.PLAIN_MESSAGE);
        if (valorPagoStr == null) return;

        try {
            double valorPago = Double.parseDouble(valorPagoStr.replace(",", "."));
            if (valorPago < pedidoAtual.getValorTotal()) {
                JOptionPane.showMessageDialog(this, "O valor pago é insuficiente!", "Erro de Pagamento", JOptionPane.ERROR_MESSAGE);
                return;
            }

            double trocoValor = valorPago - pedidoAtual.getValorTotal();
            caixa.fornecerTroco(trocoValor); // Verifica se há troco antes de confirmar

            // Confirma a venda, reduz o estoque
            pedidoAtual.getItens().forEach(item ->
                    estoque.buscarProdutoPorNome(item.getProduto().getNome())
                           .ifPresent(p -> p.reduzirEstoque(item.getQuantidade()))
            );
            this.historicoVendas.add(pedidoAtual);

            JOptionPane.showMessageDialog(this, "Compra realizada com sucesso!\nSeu troco é: R$ " + String.format("%.2f", trocoValor), "Sucesso", JOptionPane.INFORMATION_MESSAGE);

            cancelarCompra(); // Limpa o pedido atual para a próxima compra
            carregarPainelProdutos(); // Atualiza a exibição dos produtos (estoque mudou)

        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Valor digitado é inválido. Use apenas números.", "Erro de Formato", JOptionPane.ERROR_MESSAGE);
        } catch (FaltaTrocoException ex) {
            JOptionPane.showMessageDialog(this, "ERRO NO CAIXA: " + ex.getMessage() + "\nPor favor, pague com um valor menor ou peça ajuda.", "Falta de Troco", JOptionPane.ERROR_MESSAGE);
        }
    }

    /**
     * Cancela a compra atual.
     * Cria uma nova instância de {@code Pedido} para {@code pedidoAtual} e atualiza
     * a interface do carrinho.
     */
    private void cancelarCompra() {
        this.pedidoAtual = new Pedido();
        atualizarCarrinho();
    }

    /**
     * Aplica um estilo visual padrão a um botão.
     *
     * @param botao   O JButton a ser personalizado.
     * @param fundo   A cor de fundo do botão.
     * @param texto   A cor do texto do botão.
     * @param negrito true para fonte em negrito, false para fonte normal.
     */
    private void personalizarBotao(JButton botao, Color fundo, Color texto, boolean negrito) {
        botao.setBackground(fundo);
        botao.setForeground(texto);
        botao.setOpaque(true);
        if (negrito) {
            botao.setFont(new Font("Segoe UI", Font.BOLD, 14));
        } else {
            botao.setFont(new Font("Segoe UI", Font.PLAIN, 14));
        }
        Border bordaLinha = BorderFactory.createLineBorder(COR_BORDA_BOTAO, 1);
        Border margemInterna = new EmptyBorder(8, 18, 8, 18);
        botao.setBorder(BorderFactory.createCompoundBorder(bordaLinha, margemInterna));
        botao.setFocusPainted(false);
    }

    /**
     * Aplica um estilo visual específico para o botão de remover item do carrinho.
     *
     * @param botao O JButton "remover" a ser personalizado.
     */
    private void personalizarBotaoRemover(JButton botao) {
        botao.setBackground(COR_BOTAO_REMOVER);
        botao.setForeground(Color.WHITE);
        botao.setFont(new Font("Segoe UI", Font.BOLD, 12));
        botao.setOpaque(true);
        botao.setFocusPainted(false);
        Border bordaLinha = BorderFactory.createLineBorder(COR_BOTAO_REMOVER.darker());
        Border margemInterna = new EmptyBorder(2, 8, 2, 8);
        botao.setBorder(BorderFactory.createCompoundBorder(bordaLinha, margemInterna));
    }
}