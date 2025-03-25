package com.puj.admission.controller;

import com.puj.admission.model.ApplicantData;
import com.puj.admission.model.PredictionResult;
import com.puj.admission.service.PredictionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/predict")
public class PredictionController {

    @Autowired
    private PredictionService predictionService;

    @PostMapping
    public PredictionResult predict(@RequestBody ApplicantData data) {
        return predictionService.predict(data);
    }
}

