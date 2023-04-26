import numpy as np
import matplotlib.pyplot as plt

# WEAK SCALING

# Define filenames and corresponding plot labels
filenames = ['strong_eigen.txt', 'strong_eigen_O3.txt', 'strong_simple.txt', 'strong_simple_O3.txt']
labels = ['Eigen Matmul Weak Scaling', 'Optimized Eigen Matmul Weak Scaling', 'Simple Matmul Weak Scaling', 'Optimized Simple Matmul Weak Scaling']

# Read data from files
data = []
for filename in filenames:
    data.append(np.loadtxt(filename, usecols=(0, 1)))

# Divide mean wall times by value for n=10 in strong_eigen.txt
unoptimized_eigen_n10 = data[0][0, 1]
unoptimized_eigen_n4000 = data[0][8, 1]

for i in range(len(data)):
    data[i][:, 1] /= unoptimized_eigen_n10

# Plot data
plt.figure()
for i in range(len(data)):
    plt.plot(data[i][:, 0], data[i][:, 1], '*-', label=labels[i])
plt.legend()
plt.xlabel('Matrix Size [$n$]')
plt.ylabel("'Normalized' Wall Clock Time")
plt.title('Weak Scaling (Unoptimized Eigen $n=10$ WC Time: ${:.2e}$)'.format(unoptimized_eigen_n10))
plt.savefig('weak_scaling.pdf')

# STRONG SCALING

# Read data from file
nthreads = []
times = []
problem_size = -1
with open('weak_eigen_O3_OMP.txt', 'r') as f:
    for i, line in enumerate(f):
        if i % 2 == 0:
            nthreads.append(line.split()[0]) 
        else:
            times.append(line.split()[1])
            problem_size = line.split()[0]

times = np.array(times).astype(np.float64)

# Divide all times by first value : to "nomralize"
times /= unoptimized_eigen_n4000

# Plot data
plt.figure()
plt.plot(nthreads, times, '*-', color='darkmagenta')
plt.xlabel('Number of Threads')
plt.ylabel("'Normalized' Wall Clock Time")
plt.title('$n={}$ Strong Scaling (Unopt. Eigen $n=4000$ WC Time: ${:.2e}$)'.format(problem_size, unoptimized_eigen_n4000))
plt.savefig('strong_scaling.pdf')