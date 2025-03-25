package app_web;

import java.io.FileReader;
import java.util.HashMap;
import java.util.Map;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

public class LectorJSON {
    public static ModeloRegresion cargarModelo(String ruta) {
        try {
            Gson gson = new Gson();
            FileReader reader = new FileReader(ruta);
            Map<String, Double> datos = gson.fromJson(reader, new TypeToken<Map<String, Double>>(){}.getType());

            double intercepto = datos.get("intercept");
            datos.remove("intercept");

            return new ModeloRegresion(datos, intercepto);
        } catch (Exception e) {
            System.err.println("Error al leer el archivo JSON: " + e.getMessage());
            return null;
        }
    }
}
