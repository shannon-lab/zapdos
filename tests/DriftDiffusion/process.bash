#!/bin/bash -i

OutputFile="Input_Ar_6_um_103_V_out"

module load paraview

pvpython ToCSV.py "${OutputFile}"

for file in $( ls ${OutputFile}*0.csv ) ; do
	TempOutputFile=${file//"0.csv"/".txt"}
	mv ${file} ${TempOutputFile}
done

rm ${OutputFile}*.csv

for file in $( ls ${OutputFile}*.txt ) ; do
	NewOutputFile=${file//"_out"/""}
	NewOutputFile=${NewOutputFile//"Input"/"Output"}
	NewOutputFile=${NewOutputFile//".txt"/".csv"}

	mv ${file} ${NewOutputFile}
done
