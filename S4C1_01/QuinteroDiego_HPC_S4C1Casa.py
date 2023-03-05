import numpy as np
import matplotlib.pylab as plt

datos = np.genfromtxt("err_derF.dat")

plt.figure()
plt.semilogy(datos[:,0], datos[:,3], 'b*--', label='Forward Difference Error')
plt.title('Forward Difference Error of $sin(t), t\in(-\pi/2, \pi/2)$ vs. $t$')
plt.xlabel('t [radians]')
plt.ylabel('relative error with $cos(t)$')
plt.legend()
plt.grid()
plt.savefig("err_derF.pdf")

datos = np.genfromtxt("err_derC.dat")

plt.figure()
plt.plot(datos[:,0], datos[:,3], 'b*--', label='Central Difference Error') # no need of semilogy
plt.title('Central Difference Error of $sin(t), t\in(-\pi/2, \pi/2)$ vs. $t$')
plt.xlabel('t [radians]')
plt.ylabel('relative error with $cos(t)$')
plt.legend()
plt.grid()
plt.savefig("err_derC.pdf")

datos = np.genfromtxt("err_der_h.dat")

plt.figure()
plt.loglog(datos[:,0], datos[:,3], 'g*--', label='Central Difference Error')
plt.gca().invert_xaxis()
plt.title('Central DIfference Error of $sin(t), t=\pi/3$ vs. $h$')
plt.xlabel('h')
plt.ylabel('relative error with $cos(t)$')
plt.legend()
plt.grid()
plt.savefig("err_der_h.pdf")
