# include "isingmodel.h"
# include <iostream>
# include <vector>
# include <fstream>

using namespace std;

int main() {
    int N = 100; // number of spins
    int MC_STEPS = 1000000; // number of Monte Carlo steps
    double J = 1.0; // interaction energy
    int NUM_SAMPLES = 100; // number of independent configurations

    // store the data in to .csv file
    std::ofstream outputFile("ising_results.csv");
    outputFile << "beta,avgEnergy,avgMagnetization\n";

    // loop over different beta values
    for (double beta = 0.1; beta <= 2.0; beta += 0.1) {
        double avgEnergy = 0.0;
        double avgMagnetization = 0.0;

        // generate multiple independent configurations
        for (int sample = 0; sample < NUM_SAMPLES; sample++) {
            IsingModel model(N, MC_STEPS, J);
            model.initializeSpins();
            model.metropolisAlgorithm(beta);

            avgEnergy += model.computeEnergy();
            avgMagnetization += abs(model.computeMagnetization());
        }

        avgEnergy /= NUM_SAMPLES;
        avgMagnetization /= NUM_SAMPLES;

        outputFile << beta << "," << avgEnergy << "," << avgMagnetization << "\n";

        cout << "beta: " << beta
             << " | avg energy: " << avgEnergy
             << " | avg magnetization: " << avgMagnetization << endl;
    }

    outputFile.close();
    cout << "data saved to ising_results.csv" << endl;

    return 0;
}