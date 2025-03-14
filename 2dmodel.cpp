#include "2dmodel.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <random>

// no need to define the random number generator here
//  global random number generator is already defined in isingmodel.cpp

// Constructor
IsingModel2D::IsingModel2D(int size, int steps, double interactionEnergy)
    : N(size), MC_STEPS(steps), J(interactionEnergy), atoms(size, std::vector<int>(size)) {}

// Populate the 2D Ising model of size N with atoms in random states
void IsingModel2D::initializeAtoms() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            atoms[i][j] = (dist(gen) <= 0.5) ? 1 : -1; // randomly assign the site of the atom to +1 or -1 
        }
    }
}

// Compute total energy with periodic boundary conditions
double IsingModel2D::computeEnergy() const {
    double energy = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int right = (j == N - 1) ? atoms[i][0] : atoms[i][j + 1]; // right neighbor with peridoic boundary conditions
            int down = (i == N - 1) ? atoms[0][j] : atoms[i + 1][j]; // down neighbor with peridoic boundary conditions
            
            // we only consider the interaction energy with the right and down neighbors
            // becasue in a square grid if we calculate the energy of each atom with all four of its neighbors
            // then the energy of the atom will be counted twice
            energy += -J * atoms[i][j] * (right + down);
        }
    }
    return energy;
}

// Compute magnetization
double IsingModel2D::computeMagnetization() const {
    double magnetization = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            magnetization += atoms[i][j];
        }
    }
    return magnetization;
}

// Monte Carlo Metropolis algorithm
void IsingModel2D::metropolisAlgorithm(double beta) {
    for (int steps = 0; steps < MC_STEPS; steps++) {
        // randomly select an entry(i, j) between 0 and N - 1
        std::uniform_int_distribution<int> randIndex(0, N - 1);
        int i = randIndex(gen);
        int j = randIndex(gen);

        int left = (j == 0) ? atoms[i][N - 1] : atoms[i][j - 1]; // left neighbor with periodic boundary conditions
        int right = (j == N - 1) ? atoms[i][0] : atoms[i][j + 1]; // right neighbor with periodic boundary conditions
        int top = (i == 0) ? atoms[N - 1][j] : atoms[i - 1][j]; // top neighbor with periodic boundary conditions
        int bottom = (i == N - 1) ? atoms[0][j] : atoms[i + 1][j]; // down neighbor with periodic boundary conditions

        double deltaE = 2.0 * J * atoms[i][j] * (left + right + top + bottom);

        double P = exp(-beta * deltaE);
        if (P > 1.0) P = 1.0;
        if (dist(gen) < P) {
            atoms[i][j] *= -1;
        }
    }
}

// return spin configuration
std::vector<std::vector<int> > IsingModel2D::getAtoms() const {
    return atoms;
}