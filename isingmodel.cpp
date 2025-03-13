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
    : N(size), MC_STEPS(steps), J(interactionEnergy), atoms(size) {}

// populate the 1D Ising model of size N with atoms in random states
void IsingModel::initializeAtoms() {
    for (int i = 0; i < N; i++) {
        atoms[i] = (dist(gen) < 0.5) ? 1 : -1; // randomly assign the value of the atom to +1 or -1
    }
}

// compute total energy with periodic boundary conditions
double IsingModel::computeEnergy() const {
    double energy = 0.0;
    for (int i = 0; i < N; i++) {
        int rightNeighbor = (i == N - 1) ? atoms[0] : atoms[i + 1];
        energy += -J * atoms[i] * rightNeighbor;
    }
    return energy;
}

// function to compute magnetization of the system
double IsingModel::computeMagnetization() const {
    double magnetization = 0.0;
    for (int i = 0; i < N; i++) {
        magnetization += atoms[i];
    }
    return magnetization;
}

// monte carlo metropolis algorithm
void IsingModel::metropolisAlgorithm(double beta) {
    uniform_int_distribution<int> randSpin(0, N - 1);

    for (int step = 0; step < MC_STEPS; step++){

        // randomly select an atom(entry)
        int i = randSpin(gen); // generate a uniformly ranodm integer between 0 and N - 1

        // compute the energy change if the spin is fplipped
        int left = (i == 0) ? atoms[N - 1] : atoms[i -1];
        int right = (i == N - 1) ? atoms[0] : atoms[i + 1]; 
        double deltaE = 2.0 * J * atoms[i] * (left + right);

        double P = exp(-beta * deltaE);

        // if P is greater than 1, set P to 1
       if (P > 1.0) {
           P = 1.0;
       }

       // generate a random number between 0 and 1
        double r = dist(gen);

       // accept the flip if r < P
       if (r < P) {
           atoms[i] *= -1;
       }
    }
}

vector<int> IsingModel::getAtoms() const {
    return atoms;
}
