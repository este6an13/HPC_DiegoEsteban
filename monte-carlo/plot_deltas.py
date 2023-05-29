import matplotlib.pyplot as plt

# Read data from the file
N_values = []
relative_errors = []
with open('deltas.txt', 'r') as file:
    for line in file:
        N, _, relative_error = line.split()
        N_values.append(int(N))
        relative_errors.append(float(relative_error))

# Plot relative error vs N
plt.loglog(N_values, relative_errors, 'o-', color='darkmagenta')
plt.xlabel('N')
plt.ylabel('Relative Error')
plt.title('$\pi$ Monte Carlo Relative Error vs. $N$')
plt.savefig('Delta.pdf')

# Show the plot
plt.show()
