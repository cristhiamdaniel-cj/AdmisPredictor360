package com.puj.admission.model;

public class PredictionResult {
    private double chance;

    public PredictionResult(double chance) {
        this.chance = chance;
    }

    public double getChance() {
        return chance;
    }
}