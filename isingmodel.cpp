# include "isingmodel.h"
# include <iostream>
# include <cmath>
# include <ctime>
# include <random>
# include <vector>

using namespace std;

// random number generator
random_device rd;
mt19937 gen(rd()); 
uniform_real_distribution<double> dist(0.0, 1.0);

// constructor
IsingModel::IsingModel(int size, int steps, double interactionEnergy)
    : N(size), MC_STEPS(steps), J(interactionEnergy), spins(size) {}

// initialize the 1D spin system randomly
void IsingModel::initializeSpins() {
    for (int i = 0; i < N; i++) {
        spins[i] = (dist(gen) < 0.5) ? 1 : -1; // randomly assign spins to +1 or -1
    }
}

// compute total energy with periodic boundary conditions
double IsingModel::computeEnergy() const {
    double energy = 0.0;
    for (int i = 0; i < N; i++) {
        int rightNeighbor = (i == N - 1) ? spins[0] : spins[i + 1];
        energy += -J * spins[i] * rightNeighbor;
    }
    return energy;
}

// function to compute magnetization of the system
double IsingModel::computeMagnetization() const {
    double magnetization = 0.0;
    for (int i = 0; i < N; i++) {
        magnetization += spins[i];
    }
    return magnetization;
}

// monte carlo metropolis algorithm
void IsingModel::metropolisAlgorithm(double beta) {
    uniform_int_distribution<int> randSpin(0, N - 1);

    for (int step = 0; step < MC_STEPS; step++){
        int i = randSpin(gen); // pick a random spin

        // compute the energy change if the spin is fplipped
        int left = (i == 0) ? spins[N - 1] : spins[i -1];
        int right = (i == N - 1) ? spins[0] : spins[i + 1]; 
        double deltaE = 2.0 * J * spins[i] * (left + right);

        // Metropolis acceptance criterion
        if (deltaE < 0 || dist(gen) < exp(-beta * deltaE)) {
            spins[i] *= -1; // flip the spin
        }
    }
}

vector<int> IsingModel::getSpins() const {
    return spins;
}
