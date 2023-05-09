import matplotlib.pyplot as plt

# Read in the data from the file
with open('times.txt', 'r') as f:
    lines = f.readlines()

data = {}
for line in lines:
    parts = line.split()
    threads = int(parts[0])
    policy = parts[1]
    time = float(parts[2])
    if policy not in data:
        data[policy] = {}
    data[policy][threads] = time

# Calculate the speedup and parallel efficiency for each policy
parallel_speedup = {}
parallel_efficiency = {}
for policy in data:
    parallel_speedup[policy] = {}
    parallel_efficiency[policy] = {}
    for threads in data[policy]:
        parallel_speedup[policy][threads] = data[policy][1] / data[policy][threads]
        parallel_efficiency[policy][threads] = parallel_speedup[policy][threads] / threads

policy_names = ['', 'sequenced', 'parallel', 'parallel unsequenced', 'unsequenced']

# Calculate the theoretical speedup for the entire algorithm
p = 1  # assuming the entire algorithm can be parallelized
max_threads = max([max(data[policy].keys()) for policy in data]) # get the maximum number of threads used
theoretical_speedup = [1 / ((1 - p) + (p / n)) for n in range(1, max_threads+1)]

# Plot the speedup for each policy
plt.figure(1)
plt.title('Parallel Speedup vs Number of Threads (8 phys. cores)')
plt.xlabel('Number of Threads')
plt.ylabel('Parallel Speedup (semilogy)')
for policy in parallel_speedup:
    threads = list(parallel_speedup[policy].keys())
    times = list(parallel_speedup[policy].values())
    plt.semilogy(threads, times, '*-', label=policy_names[int(policy)])
plt.semilogy(range(1, max_threads+1), theoretical_speedup, '--', label='Theoretical')
plt.legend()
plt.savefig('parallel_speedup.pdf')

# Plot the parallel efficiency for each policy
plt.figure(2)
plt.title('Parallel Efficiency vs Number of Threads (8 phys. cores)')
plt.xlabel('Number of Threads')
plt.ylabel('Parallel Efficiency (semilogy)')
for policy in parallel_efficiency:
    threads = list(parallel_efficiency[policy].keys())
    efficiency = list(parallel_efficiency[policy].values())
    plt.semilogy(threads, efficiency, '*-', label=policy_names[int(policy)])
plt.axhline(y=0.6, color='red', linestyle='--', label='Efficiency = 0.6')
plt.legend()
plt.savefig('parallel_efficiency.pdf')


