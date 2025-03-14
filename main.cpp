# include "isingmodel.h"
# include "2dmodel.h"
# include <iostream>
# include <vector>
# include <fstream>

using namespace std;

int main() {
    int N = 100; // number of spins
    int MC_STEPS = 1000000; // number of Monte Carlo steps
    double J = 1.0; // interaction energy
    int NUM_SAMPLES = 100; // number of independent configurations

    int choice;
    cout << "Enter 1 for 1D Ising model and 2 for 2D Ising model: ";
    cin >> choice;

    if (choice == 1) {
        // store the data in to .csv file
        std::ofstream outputFile("1dmodel_results.csv");
        outputFile << "beta,avgEnergy,avgMagnetization\n";

        // loop over different beta values
        for (double beta = 0.1; beta < 2.1; beta += 0.1) {
            double avgEnergy = 0.0;
            double avgMagnetization = 0.0;

            // generate multiple independent configurations
            for (int sample = 0; sample < NUM_SAMPLES; sample++) {
                IsingModel model(N, MC_STEPS, J);
                model.initializeAtoms();
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
    cout << "data saved to 1dmodel_results.csv" << endl;
    }

    else if (choice == 2) {
        std::ofstream outputFile("2dmodel_results.csv");
        outputFile << "beta,avgEnergy,avgMagnetization\n";

        for (double beta = 0.1; beta < 2.1; beta += 0.1) {
                double avgEnergy = 0.0;
                double avgMagnetization = 0.0;

                for (int sample = 0; sample < NUM_SAMPLES; sample++) {
                    IsingModel2D model2D(N, MC_STEPS, J);
                    model2D.initializeAtoms();
                    model2D.metropolisAlgorithm(beta);

                    avgEnergy += model2D.computeEnergy();
                    avgMagnetization += abs(model2D.computeMagnetization());
                }

                avgEnergy /= NUM_SAMPLES;
                avgMagnetization /= NUM_SAMPLES;

                outputFile << beta << "," << avgEnergy << "," << avgMagnetization << "\n";

                cout << "beta: " << beta
                    << " | avg energy: " << avgEnergy
                    << " | avg magnetization: " << avgMagnetization << endl;
        }

        outputFile.close();
        cout << "data saved to 2dmodel_results.csv" << endl;
    }

    return 0;
}