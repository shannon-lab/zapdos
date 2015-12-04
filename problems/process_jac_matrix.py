import re
import numpy as np
import fileinput

filename = 'sans_dg_kernels.txt'
patterns = ['^.*:','\([0-9]+, ','\)']
replacements = ['','','']
# pattern  = '^.*:'
# new_file = []

# Make sure file gets closed after being iterated
# with open(filename, 'r') as f:
#    # Read the file contents and generate a list with each line
#    lines = f.readlines()

# # Iterate each line
# for line in lines:

#     # Regex applied to each line 
#     new_line = re.sub(pattern,'',line)
#     new_line = re.sub('\([0-9]+, ','',new_line)
#     new_line = re.sub('\)','',new_line)
#     print new_line
#     new_file.append(new_line)

# with open(filename, 'w') as f:
#      # go to start of file
#      f.seek(0)
#      # actually write the lines
#      f.writelines(new_file)

for line in fileinput.input(filename,inplace = True):
    if not (re.search('^ *M',line) or re.search('^ *t',line)):
        new_line = line
        for pattern, repl in zip(patterns,replacements):
            new_line = re.sub(pattern,repl,new_line)
        # new_line = re.sub('^.*:','',line)
        # new_line = re.sub('\([0-9]+, ','',new_line)
        # new_line = re.sub('\)','',new_line)
        print new_line,
        # print line,
        
Jac = np.loadtxt(filename)
print Jac
