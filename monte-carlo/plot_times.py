import matplotlib.pyplot as plt

# Read data from the file
data = []
with open('times.txt', 'r') as file:
    for line in file:
        np, _, time = line.split()
        data.append((int(np), float(time)))

# Calculate speedup and parallel efficiency
ref_time = data[0][1]  # Time for 1 process (reference)
speedup = [(np, ref_time / time) for np, time in data]
efficiency = [(np, speedup_value / np) for np, speedup_value in speedup]

# Extract data for plotting
np_values, speedup_values = zip(*speedup)
_, efficiency_values = zip(*efficiency)

# Plot speedup
plt.figure()
plt.plot(np_values, speedup_values, 'bo-', label='Real Speedup')
plt.plot(np_values, np_values, '--', color='orange', label='Theretical Speedup')
plt.xlabel('Number of Processes')
plt.ylabel('Speedup')
plt.title('$\pi$ Monte Carlo Speedup for $N=1200000000$')
plt.legend()
plt.savefig('S.pdf')

# Plot parallel efficiency
plt.figure()
plt.plot(np_values, efficiency_values, 'ro-')
plt.axhline(y=0.6, color='orange', linestyle='--', label='$60$% Efficiency')
plt.xlabel('Number of Processes')
plt.ylabel('Parallel Efficiency')
plt.title('$\pi$ Monte Carlo Parallel Efficiency for $N=1200000000$')
plt.legend()
plt.savefig('E.pdf')

# Show the plots
plt.show()
