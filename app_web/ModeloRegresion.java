package app_web;

import java.util.Map;

public class ModeloRegresion {
    private Map<String, Double> coeficientes;
    private double intercepto;

    public ModeloRegresion(Map<String, Double> coeficientes, double intercepto) {
        this.coeficientes = coeficientes;
        this.intercepto = intercepto;
    }

    public double predecir(Map<String, Double> datosEntrada) {
        double resultado = intercepto;
        for (String clave : datosEntrada.keySet()) {
            if (coeficientes.containsKey(clave)) {
                resultado += coeficientes.get(clave) * datosEntrada.get(clave);
            }
        }
        return resultado;
    }

    public double getIntercepto() {
        return intercepto;
    }

    public Map<String, Double> getCoeficientes() {
        return coeficientes;
    }
}
