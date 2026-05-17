import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.text.Normalizer;
import java.util.HashMap;
import java.util.Map;

public class ClimaImpl extends UnicastRemoteObject implements IClima {

    private Map<String, Double> temperaturas;

    public ClimaImpl() throws RemoteException {
        super();
        temperaturas = new HashMap<>();

        temperaturas.put("São Paulo", 22.5);
        temperaturas.put("Rio de Janeiro", 30.2);
        temperaturas.put("Curitiba", 18.0);
        temperaturas.put("Belo Horizonte", 25.3);
        temperaturas.put("Porto Alegre", 20.1);
        temperaturas.put("Salvador", 28.7);
        temperaturas.put("Brasília", 23.4);
        temperaturas.put("Manaus", 32.0);
        temperaturas.put("Recife", 27.9);
        temperaturas.put("Fortaleza", 29.5);
    }

    /**
     * Remove acentos de uma string para facilitar a comparação.
     */
    private String removerAcentos(String str) {
        return Normalizer.normalize(str, Normalizer.Form.NFD).replaceAll("[^\\p{ASCII}]", "");
    }

    @Override
    public String getTemperatura(String cidade) throws RemoteException {
        System.out.println("[Servidor] Chamada recebida - Consulta para a cidade: " + cidade);

        String cidadeLimpaConsulta = removerAcentos(cidade);

        for (Map.Entry<String, Double> entry : temperaturas.entrySet()) {
            String cidadeLimpaBase = removerAcentos(entry.getKey());
            if (cidadeLimpaBase.equalsIgnoreCase(cidadeLimpaConsulta)) {
                String resultado = "A temperatura em " + entry.getKey() + " é de " + entry.getValue() + "°C";
                System.out.println("[Servidor] Resposta enviada: " + resultado);
                return resultado;
            }
        }

        String msgErro = "Cidade '" + cidade + "' não encontrada na base de dados.";
        System.out.println("[Servidor] " + msgErro);
        return msgErro;
    }
}
