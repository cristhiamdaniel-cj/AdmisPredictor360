package com.puj.admission.service;

import com.puj.admission.model.ApplicantData;
import com.puj.admission.model.ModelCoefficients;
import com.puj.admission.model.PredictionResult;
import com.puj.admission.util.JsonLoader;
import org.springframework.stereotype.Service;

@Service
public class PredictionService {

    private final ModelCoefficients model;

    public PredictionService() {
        this.model = JsonLoader.loadModel("data/modelo_coeficientes.json");
    }

    public PredictionResult predict(ApplicantData data) {
        double chance =
                model.getIntercept()
                + model.getGreScore() * data.getGreScore()
                + model.getToeflScore() * data.getToeflScore()
                + model.getUniversityRating() * data.getUniversityRating()
                + model.getSop() * data.getSop()
                + model.getLor() * data.getLor()
                + model.getCgpa() * data.getCgpa()
                + model.getResearch() * data.getResearch();

        return new PredictionResult(Math.max(0, Math.min(1, chance))); // clamp [0, 1]
    }
}