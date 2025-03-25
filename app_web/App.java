package app_web;

import java.util.HashMap;
import java.util.Map;

public class App {
    public static void main(String[] args) {
        String rutaJSON = "app_web/datos/modelo_coeficientes.json";

        ModeloRegresion modelo = LectorJSON.cargarModelo(rutaJSON);

        if (modelo == null) {
            System.out.println("No se pudo cargar el modelo.");
            return;
        }

        // Simulamos una entrada de usuario
        Map<String, Double> entrada = new HashMap<>();
        entrada.put("GRE Score", 330.0);
        entrada.put("TOEFL Score", 115.0);
        entrada.put("University Rating", 4.0);
        entrada.put("SOP", 4.5);
        entrada.put("LOR", 4.0);
        entrada.put("CGPA", 9.2);
        entrada.put("Research", 1.0);

        double prediccion = modelo.predecir(entrada);

        System.out.printf("Probabilidad de admisión estimada: %.4f%n", prediccion);
    }
}
