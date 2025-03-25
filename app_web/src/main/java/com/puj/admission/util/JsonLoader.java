package com.puj.admission.util;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.puj.admission.model.ModelCoefficients;

import java.io.InputStream;

public class JsonLoader {
    public static ModelCoefficients loadModel(String path) {
        try {
            ObjectMapper mapper = new ObjectMapper();
            InputStream is = JsonLoader.class.getClassLoader().getResourceAsStream(path);
            if (is == null) {
                throw new RuntimeException("Archivo JSON no encontrado: " + path);
            }
            return mapper.readValue(is, ModelCoefficients.class);
        } catch (Exception e) {
            e.printStackTrace();
            throw new RuntimeException("Error al cargar el modelo JSON");
        }
    }
}
