#* This file is part of Zapdos, an open-source
#* application for the simulation of plasmas
#* https://github.com/shannon-lab/zapdos
#*
#* Zapdos is powered by the MOOSE Framework
#* https://www.mooseframework.org
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html

import re
import numpy as np
import fileinput

filename = 'snes_test_output.txt'
patterns = ['^.*:']
replacements = ['']

for line in fileinput.input(filename,inplace = True):
    if not (re.search('^ *M',line) or re.search('^ *t',line)):
        new_line = line
        for pattern, repl in zip(patterns,replacements):
            new_line = re.sub(pattern,repl,new_line)
        print new_line,

i = 0
for line in fileinput.input(filename,inplace = True):
    str_i = str(i)
    new_line = line
    new_line = re.sub('\(','(' + re.escape(str_i) + ', ',new_line)
    new_line = re.sub('\(','',new_line)
    new_line = re.sub('\)',',',new_line)
    i+=1
    print new_line,

string = ''
with open(filename) as f:
    string = " ".join(line.strip() for line in f)

with open(filename,'w') as f:
    f.write(string)

for line in fileinput.input(filename,inplace = True):
    newline = re.sub(', *$','',line)
    print newline,

data = np.loadtxt(filename,delimiter=',')
a = data.size
num_rows = int(data[a-3] + 1)
mat = np.zeros((num_rows,num_rows))
for elem in xrange(0,len(data),3):
    i = data[elem]
    j = data[elem+1]
    mat[i][j] = data[elem+2]

for i in range(num_rows):
    for j in range(num_rows):
        if abs(mat[i][j]) < 1e-3:
            mat[i][j] = 0
