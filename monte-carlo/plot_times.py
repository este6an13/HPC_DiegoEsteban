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
plt.plot(np_values, speedup_values, 'bo-')
plt.xlabel('Number of Processes')
plt.ylabel('Speedup')
plt.title('$\pi$ Monte Carlo Speedup for $N=1200000000$')
plt.savefig('S.pdf')

# Plot parallel efficiency
plt.figure()
plt.plot(np_values, efficiency_values, 'ro-')
plt.xlabel('Number of Processes')
plt.ylabel('Parallel Efficiency')
plt.title('$\pi$ Monte Carlo Parallel Efficiency for $N=1200000000$')
plt.savefig('E.pdf')

# Show the plots
plt.show()
