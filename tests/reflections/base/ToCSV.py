from paraview.simple import *
import os
import sys
import numpy as np

path = os.getcwd() + "/"
file_name = sys.argv[1]
inp = file_name + ".e"
outCSV = file_name + ".csv"

reader = ExodusIIReader(FileName=path+inp)

tsteps = reader.TimestepValues

writer = CreateWriter(path+file_name+"_Cells.csv", reader)
writer.FieldAssociation = "Cells" # or "Points"
writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
del writer

writer = CreateWriter(path+file_name+"_Points.csv", reader)
writer.FieldAssociation = "Points" # or "Cells"
writer.UpdatePipeline(time=tsteps[len(tsteps)-1])
del writer
