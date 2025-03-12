import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("ising_results.csv")

beta = data["beta"]
avgEnergy = data["avgEnergy"]
avgMagnetization = data["avgMagnetization"]

plt.figure(figsize=(6, 4))
plt.plot(beta, avgEnergy, marker='o', linestyle='-', color='b', label='avgEnergy')
plt.xlabel("β")
plt.ylabel("avgEnergy")
plt.title("avgEnergy vs. β")
plt.legend()
plt.grid(True)
plt.savefig("avgEnergy_vs_beta.png", dpi = 300)
plt.show()

plt.figure(figsize=(6, 4))
plt.plot(beta, avgMagnetization, marker='s', linestyle='-', color='r', label='avgMagnetization')
plt.xlabel("β")
plt.ylabel("avgMagnetization")
plt.title("avgMagnetization vs. β")
plt.legend()
plt.grid(True)
plt.savefig("avgMagnetization_vs_beta.png", dpi = 300)
plt.show()