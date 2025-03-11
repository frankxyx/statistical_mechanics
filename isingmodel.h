#ifndef ISINGMODEL_H
#define ISINGMODEL_H

#include <vector>

class IsingModel {
private:
    int N; // number of spins
    int MC_STEPS;
    double J;
    std::vector<int> spins;

public:
    IsingModel(int size, int steps, double interactionEnergy);
    void initializeSpins();
    double computeEnergy() const;
    double computeMagnetization() const;
    void metropolisAlgorithm(double beta);
    std::vector<int> getSpins() const;
};

#endif 