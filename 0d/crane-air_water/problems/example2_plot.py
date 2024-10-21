import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import ternary
import random

def random_points(num_points=25, scale=40):
    points = []
    for i in range(num_points):
        x = random.randint(1, scale)
        y = random.randint(0, scale - x)
        z = scale - x - y
        points.append((x,y,z))
    return points


def get_coordinates(points):
    return([(points[0], points[1], points[2])])


stiff_file = 'example2_out_stiff.csv'
nonstiff_file = 'example2_out_nonstiff.csv'
# nonstiff_file = 'example2_out.csv'
stiff_data = np.genfromtxt(stiff_file, dtype=float, delimiter=',', skip_header=1)
nonstiff_data = np.genfromtxt(nonstiff_file, dtype=float, delimiter=',', skip_header=1)

y0 = stiff_data[:, 31:34]
y1 = stiff_data[:, 34:37]
y2 = stiff_data[:, 37:40]
y3 = stiff_data[:, 40:43]
y4 = stiff_data[:, 43:46]


x0 = nonstiff_data[:, 31:34]
x1 = nonstiff_data[:, 34:37]
x2 = nonstiff_data[:, 37:40]
x3 = nonstiff_data[:, 40:43]
x4 = nonstiff_data[:, 43:46]

mark_val = len(x4[:, 0])
figure, ax = plt.subplots(1, 2, figsize=(12,6))
tax1 = ternary.TernaryAxesSubplot(ax=ax[0])
eq_point = get_coordinates(y4[-1,:])
st_point = []
st_point.append(get_coordinates(y0[0, :]))
st_point.append(get_coordinates(y1[0, :]))
st_point.append(get_coordinates(y2[0, :]))
st_point.append(get_coordinates(y3[0, :]))
st_point.append(get_coordinates(y4[0, :]))

tax1.boundary()
tax1.gridlines(multiple=0.1, color="black")
tax1.set_title("(a) Stiff Trajectories", fontsize=14)
fontsize = 12
offset = 0.105
tax1.left_axis_label("$H^+$", fontsize=fontsize, offset=offset)
tax1.right_axis_label("$H^*$", fontsize=fontsize, offset=offset)
tax1.bottom_axis_label("$H$", fontsize=fontsize, offset=offset)
tax1.plot(y0, linewidth=2.0, zorder=10)
tax1.plot(y1, linewidth=2.0, zorder=8)
tax1.plot(y2, linewidth=2.0, zorder=6)
tax1.plot(y3, linewidth=2.0, zorder=4)
tax1.plot(y4, linewidth=2.0, zorder=2)
tax1.scatter(eq_point, marker='D', color='black', zorder=50, label='Equilibrium Point')
for i in range(5):
    if (i==0):
        legend_name = 'Start Points'
    else:
        legend_name = None
    tax1.scatter(st_point[i], marker='o', color='black', zorder=51, facecolors='none', label=legend_name)

tax1.ticks(axis='lbr', multiple=0.1, linewidth=1, tick_formats="%.1f", offset=0.02)
tax1.get_axes().axis('off')
# tax1.clear_matplotlib_ticks()
tax1.legend(loc='best')



tax2 = ternary.TernaryAxesSubplot(ax=ax[1])
eq_point = get_coordinates(x4[-1,:])
st_point = []
st_point.append(get_coordinates(x0[0, :]))
st_point.append(get_coordinates(x1[0, :]))
st_point.append(get_coordinates(x2[0, :]))
st_point.append(get_coordinates(x3[0, :]))
st_point.append(get_coordinates(x4[0, :]))

tax2.boundary()
tax2.gridlines(multiple=0.1, color="black")
tax2.set_title("(b) Non-stiff Trajectories", fontsize=14)
fontsize = 12
# offset = 0.1
# tax.right_corner_label("X", fontsize=fontsize)
# tax.top_corner_label("Y", fontsize=fontsize)
# tax.left_corner_label("Z", fontsize=fontsize)
tax2.left_axis_label("$H^+$", fontsize=fontsize, offset=offset)
tax2.right_axis_label("$H^*$", fontsize=fontsize, offset=offset)
tax2.bottom_axis_label("$H$", fontsize=fontsize, offset=offset)
# print(x1)
# tax.scatter(eq_point, marker='D', color='black')
tax2.plot(x0, linewidth=2.0, zorder=10)
tax2.plot(x1, linewidth=2.0, zorder=8)
tax2.plot(x2, linewidth=2.0, zorder=6)
tax2.plot(x3, linewidth=2.0, zorder=4)
tax2.plot(x4, linewidth=2.0, zorder=2)
tax2.scatter(eq_point, marker='D', color='black', zorder=50, label='Equilibrium Point')
for i in range(5):
    if (i==0):
        legend_name = 'Start Points'
    else:
        legend_name = None
    tax2.scatter(st_point[i], marker='o', color='black', zorder=51, facecolors='none', label=legend_name)

tax2.ticks(axis='lbr', multiple=0.1, linewidth=1, tick_formats="%.1f", offset=0.02)
tax2.get_axes().axis('off')
# tax2.legend()
# plt.show()
plt.savefig('trajectories.pdf', dpi=300, bbox_inches='tight')
plt.close()



# ax.plot(y0[:,0], y0[:,1], y0[:,2], alpha=0.6)
# ax.plot(y1[:,0], y1[:,1], y1[:,2], alpha=0.6)
# ax.plot(y2[:,0], y2[:,1], y2[:,2], alpha=0.6)
# ax.plot(y3[:,0], y3[:,1], y3[:,2], alpha=0.6)
# ax.plot(y4[:,0], y4[:,1], y4[:,2], alpha=0.6)
# plt.show()
