import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

data = np.loadtxt('td_argon_mean_en.txt')
mean_en = data[:,0]
alpha_el = data[:,3]
mu = data[:,4]
diff = data[:,5]

# alpha_el_tck = interpolate.splrep(mean_en, alpha_el, s=0, k=2)
# mean_en_new = np.arange(0, 10, .05)
# alpha_el_new = interpolate.splev(mean_en_new, alpha_el_tck, der=0)
# plt.plot(mean_en_new, alpha_el_new)
# plt.show()

mu_tck = interpolate.splrep(mean_en, mu, s=0)
mean_en_new = np.arange(0, 10, .05)
mu_new = interpolate.splev(mean_en_new, mu_tck, der=0)
plt.plot(mean_en_new, mu_new)
plt.show()

diff_tck = interpolate.splrep(mean_en, diff, s=0)
mean_en_new = np.arange(0, 10, .05)
diff_new = interpolate.splev(mean_en_new, diff_tck, der=0)
plt.plot(mean_en_new, diff_new)
plt.show()


# plt.plot(data[:,0], data[:,3])
# plt.xlim(right = 10)
# plt.show()
# plt.plot(data[:,0], data[:,4], xmax = 10)
# plt.show()
# plt.plot(data[:,0], data[:,5], xmax = 10)
# plt.show()
