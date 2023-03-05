import numpy as np
import matplotlib.pylab as plt


datos=np.genfromtxt("err_derF.dat")

plt.figure()
plt.semilogy(datos[:,0],datos[:,3], 'b*--')
plt.savefig("err_derF.pdf")

datos=np.genfromtxt("err_derC.dat")

plt.figure()
plt.semilogy(datos[:,0],datos[:,3], 'b*--')
plt.savefig("err_derC.pdf")

datos=np.genfromtxt("err_der_h.dat")

plt.figure()
plt.loglog(datos[:,0],datos[:,3], 'g*--')
plt.gca().invert_xaxis()
plt.savefig("err_der_h.pdf")
