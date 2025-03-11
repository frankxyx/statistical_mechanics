# include "isingmodel.h"
# include <iostream>
# include <vector>

using namespace std;

int main() {
    int N = 100; // number of spins
    int MC_STEPS = 1000000; // number of Monte Carlo steps
    double J = 1.0; // interaction energy
    int NUM_SAMPLES = 100; // number of independent configurations

    vector <double> energySamples, magnetizationSamples;

    // loop over different beta values
    for (double beta = 0.1; beta <= 2.0; beta += 0.1) {
        double avgEnergy = 0.0;
        double avgMagnetization = 0.0;

        // generate multiple independent configurations
        for (int sample = 0; sample < NUM_SAMPLES; sample++) {
            IsingModel model(N, MC_STEPS, J);
            model.initializeSpins();
            model.metropolisAlgorithm(beta);

            double energy = model.computeEnergy();
            double magnetization = model.computeMagnetization();

            avgEnergy += energy;
            avgMagnetization += abs(magnetization);
        }

        avgEnergy /= NUM_SAMPLES;
        avgMagnetization /= NUM_SAMPLES;

        energySamples.push_back(avgEnergy);
        magnetizationSamples.push_back(avgMagnetization);

        cout << "beta: " << beta
             << " | avg energy: " << avgEnergy
             << " | avg magnetization: " << avgMagnetization << endl;
    }

    return 0;
}