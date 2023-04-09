import matplotlib.pyplot as plt

# Define the scenarios
scenarios = [1, 2, 3, 4, 5]
scenarios_names = ['', '2D rows first', '1D rows first', '1D cols first', '1D sequential', '2D cols first']

# Read the data from the text file
with open('times.txt', 'r') as f:
    data = f.readlines()

# Parse the data into lists for each scenario
mn = {}
time = {}
for s in scenarios:
    mn[s] = []
    time[s] = []
for line in data:
    line = line.strip().split()
    s = int(line[1])
    if s in scenarios:
        mn[s].append(int(line[0]))
        time[s].append(float(line[2]))

# Plot the curves for each scenario
for s in scenarios:
    plt.semilogx(mn[s], time[s], '*-', label=f'{scenarios_names[s]}')

# Add labels and legend to the plot
plt.xlabel('Size $mn$')
plt.ylabel('Time (s)')
plt.title('Initialization Time vs Size $mn$')
plt.legend()

# Show the plot
plt.savefig('times.pdf')
