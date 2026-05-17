package main;

import model.negocio.Caixa;
import model.negocio.Estoque;
import ui.cliente.TelaPrincipalCliente;

import javax.swing.*;
import javax.swing.plaf.ColorUIResource;
import java.awt.Color;

/**
 * Classe principal que serve como ponto de entrada para a aplicação.
 * <p>
 * Esta classe é responsável por inicializar o tema visual da interface gráfica (GUI),
 * instanciar os componentes principais do modelo de negócio (Estoque e Caixa) e
 * iniciar a tela principal da aplicação para o cliente.
 * </p>
 *
 * @author William, Murilo e Calebe
 * @version Final
 * @since 2024-07-08
 */
public class Main {

    /**
     * O método principal que inicia a execução da aplicação.
     * <p>
     * Primeiramente, este método configura um tema escuro customizado para todos os
     * componentes Swing. Em seguida, ele agenda a criação e exibição da interface
     * gráfica na Event Dispatch Thread (EDT) do Swing para garantir a segurança das threads.
     * Na EDT, ele inicializa os objetos de negócio {@link Estoque} e {@link Caixa},
     * e então cria e exibe a {@link TelaPrincipalCliente}.
     * </p>
     *
     * @param args os argumentos de linha de comando (não utilizados nesta aplicação).
     */
    public static void main(String[] args) {
        // Configura o nosso tema escuro customizado ANTES de qualquer componente ser criado.
        setupDarkTheme();
        SwingUtilities.invokeLater(() -> {
            Estoque estoque = new Estoque();
            Caixa caixa = new Caixa();
            TelaPrincipalCliente tela = new TelaPrincipalCliente(estoque, caixa);
            tela.setVisible(true);
        });
    }

    /**
     * Configura as propriedades globais do {@link UIManager} para aplicar um tema escuro
     * em toda a aplicação.
     * <p>
     * Este método define o Look and Feel padrão como "Metal" (CrossPlatform) por ser
     * altamente customizável. Em seguida, define uma paleta de cores escuras e a aplica
     * a diversas chaves de propriedades do UIManager, alterando a aparência de componentes
     * como painéis, botões, campos de texto, tabelas, e mais.
     * O uso de {@link ColorUIResource} é uma prática recomendada para garantir que o tema
     * funcione corretamente com diferentes Look and Feels.
     * <p>
     * Em caso de falha na configuração do Look and Feel, uma mensagem de erro é
     * impressa no console de erro padrão.
     * </p>
     */
    private static void setupDarkTheme() {
        try {
            UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());

            // Paleta de Cores
            Color fundoEscuro = new Color(30, 30, 30);
            Color painelEscuro = new Color(45, 45, 45);
            Color textoClaro = new Color(220, 220, 220);
            Color campoEscuro = new Color(50, 50, 50);
            Color destaqueAzul = new Color(30, 144, 255);

            // Aplica as cores a todos os componentes do Swing
            UIManager.put("Panel.background", new ColorUIResource(fundoEscuro));
            UIManager.put("Frame.background", new ColorUIResource(fundoEscuro));
            UIManager.put("Window.background", new ColorUIResource(fundoEscuro));
            UIManager.put("Dialog.background", new ColorUIResource(fundoEscuro));
            
            UIManager.put("Control", new ColorUIResource(painelEscuro));
            UIManager.put("text", new ColorUIResource(textoClaro));
            UIManager.put("nimbusLightBackground", new ColorUIResource(painelEscuro));

            // Botões
            UIManager.put("Button.background", new ColorUIResource(campoEscuro));
            UIManager.put("Button.foreground", new ColorUIResource(textoClaro));
            UIManager.put("Button.select", new ColorUIResource(destaqueAzul.darker())); 
            UIManager.put("Button.focus", new ColorUIResource(new Color(255, 255, 255, 50)));

            // Campos de Texto
            UIManager.put("TextField.background", new ColorUIResource(campoEscuro));
            UIManager.put("TextField.foreground", new ColorUIResource(textoClaro));
            UIManager.put("TextField.caretForeground", new ColorUIResource(textoClaro));
            UIManager.put("PasswordField.background", new ColorUIResource(campoEscuro));
            UIManager.put("PasswordField.foreground", new ColorUIResource(textoClaro));
            UIManager.put("PasswordField.caretForeground", new ColorUIResource(textoClaro));
            UIManager.put("TextArea.background", new ColorUIResource(campoEscuro));
            UIManager.put("TextArea.foreground", new ColorUIResource(textoClaro));
            UIManager.put("TextArea.caretForeground", new ColorUIResource(textoClaro));

            // Tabelas
            UIManager.put("Table.background", new ColorUIResource(campoEscuro));
            UIManager.put("Table.foreground", new ColorUIResource(textoClaro));
            UIManager.put("Table.gridColor", new ColorUIResource(fundoEscuro));
            UIManager.put("TableHeader.background", new ColorUIResource(new Color(40, 40, 40)));
            UIManager.put("TableHeader.foreground", new ColorUIResource(textoClaro));
            
            // ScrollPanes (Barras de Rolagem)
            UIManager.put("ScrollPane.background", new ColorUIResource(fundoEscuro));
            UIManager.put("ScrollPane.border", BorderFactory.createEmptyBorder());
            UIManager.put("Viewport.background", new ColorUIResource(fundoEscuro));

            // ComboBox (Caixa de Seleção)
            UIManager.put("ComboBox.background", new ColorUIResource(campoEscuro));
            UIManager.put("ComboBox.foreground", new ColorUIResource(textoClaro));
            UIManager.put("ComboBox.selectionBackground", new ColorUIResource(destaqueAzul));
            UIManager.put("ComboBox.selectionForeground", new ColorUIResource(Color.WHITE));

            // Caixas de Diálogo (JOptionPane)
            UIManager.put("OptionPane.background", new ColorUIResource(fundoEscuro));
            UIManager.put("OptionPane.messageForeground", new ColorUIResource(textoClaro));

        } catch (Exception e) {
            System.err.println("Erro ao configurar o tema escuro.");
            e.printStackTrace();
        }
    }
}