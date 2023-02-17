import matplotlib.pyplot as plt

X1 = []
Y1 = []

X2 = []
Y2 = []

with open('DatosMarzo.txt') as f:
    lines = f.readlines() # doesn't include header due to "March" filter
    for line in lines:
        y = float(line.split()[0])
        x = float(line.split()[1])
        X1.append(x)
        Y1.append(y)

with open('GRF_vs_EQ.txt') as f:
    lines = f.readlines()
    lines = lines[1:] # header line removed
    for line in lines:
        y = float(line.split()[0])
        x = float(line.split()[1])
        X2.append(x)
        Y2.append(y)


fig, ax = plt.subplots()

ax.scatter(X1, Y1, c='green', s=50, label='March')
ax.scatter(X2, Y2, c='black', s=5, label='All Months')

ax.set_xlabel('EQ')
ax.set_ylabel('GRF')

ax.legend()
#plt.show()
plt.savefig('PlotTolima.pdf')

