#ifndef ISINGMODEL_H
#define ISINGMODEL_H

#include <vector>
#include <random>

extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<double> dist;

class IsingModel {
private:
    int N; // number of atoms
    int MC_STEPS;
    double J; // interaction energy
    std::vector<int> atoms;

public:
    IsingModel(int size, int steps, double interactionEnergy);
    void initializeAtoms();
    double computeEnergy() const;
    double computeMagnetization() const;
    void metropolisAlgorithm(double beta);
    std::vector<int> getAtoms() const;
};

#endif 