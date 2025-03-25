package com.puj.admission.model;

public class ApplicantData {
    private int greScore;
    private int toeflScore;
    private int universityRating;
    private double sop;
    private double lor;
    private double cgpa;
    private int research;

    // Getters and Setters
    public int getGreScore() { return greScore; }
    public void setGreScore(int greScore) { this.greScore = greScore; }

    public int getToeflScore() { return toeflScore; }
    public void setToeflScore(int toeflScore) { this.toeflScore = toeflScore; }

    public int getUniversityRating() { return universityRating; }
    public void setUniversityRating(int universityRating) { this.universityRating = universityRating; }

    public double getSop() { return sop; }
    public void setSop(double sop) { this.sop = sop; }

    public double getLor() { return lor; }
    public void setLor(double lor) { this.lor = lor; }

    public double getCgpa() { return cgpa; }
    public void setCgpa(double cgpa) { this.cgpa = cgpa; }

    public int getResearch() { return research; }
    public void setResearch(int research) { this.research = research; }
}