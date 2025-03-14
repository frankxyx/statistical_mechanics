#ifndef MODEL2D_H
#define MODEL2D_H

#include <vector>
#include <random>

extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<double> dist;

class IsingModel2D {
private:
    int N; // number of atoms
    int MC_STEPS; // number of Monte Carlo steps
    double J; // interaction energy
    std::vector<std::vector<int> > atoms; // 2D vector to store the atoms

public:
    IsingModel2D(int size, int steps, double interactionEnergy);
    void initializeAtoms();
    double computeEnergy() const;
    double computeMagnetization() const;
    void metropolisAlgorithm(double beta);
    std::vector<std::vector<int> > getAtoms() const;
};

#endif