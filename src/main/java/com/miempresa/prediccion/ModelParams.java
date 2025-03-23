import java.util.Map;

public class ModelParams {
    double intercept;
    Map<String, Double> coefficients;
    double mse;
    double r2;

    // Método para calcular la predicción dado un arreglo de valores en el orden correcto:
    public double predict(double[] features) {
        double prediction = intercept;
        // Orden de las variables:
        String[] featureNames = {"GRE Score", "TOEFL Score", "University Rating", "SOP", "LOR", "CGPA", "Research"};
        for (int i = 0; i < features.length; i++) {
            prediction += coefficients.get(featureNames[i]) * features[i];
        }
        return prediction;
    }
}

