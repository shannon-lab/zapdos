#!/bin/bash

oldGas="Ar"
newGas="Ar"

minVoltage=10
maxVoltage=1000
VoltageStep=5
sigDigits=3

minGap=1
maxGap=12
GapStep=1

geometryFile="Geometry.geo"
gasFile="td_argon_mean_en.txt"
SubmissionFile="Submission.job"

olddom0Size=5 #Domain size in um


oldGasLine="gas=\"${oldGas}\""
oldDomainLine="dom0Size = ${olddom0Size}E-6"

voltages=$(awk -v m="$minVoltage" -v M="$maxVoltage" -v s="$VoltageStep" -v d="$sigDigits" 'BEGIN{for(i=m;i<=M+s/2;i+=s) printf "%.*f ", d, i}')

gaps=$(awk -v m="$minGap" -v M="$maxGap" -v s="$GapStep" 'BEGIN{for(i=m;i<=M+s/2;i+=s) print i}')

for newdom0Size in $gaps
do
	newGasLine="gas=\"${newGas}\""

	newDir="${newGas}_${newdom0Size}_um"

	if [ ! -d "$newDir" ] ; then mkdir $newDir; fi

	cp $geometryFile $newDir/
	cp $gasFile $newDir/
	cd $newDir

	newDomainLine="dom0Size = ${newdom0Size}E-6"
	sed -i "s@$oldDomainLine@$newDomainLine@g" "$geometryFile"
	gmsh -1 -v 0 $geometryFile
	
	cp ../$SubmissionFile .
	sed -i "s@JobName@${newGas}_${newdom0Size}_um@g" "$SubmissionFile"
	sed -i "s@${oldGasLine}@${newGasLine}@g" "$SubmissionFile"
	sed -i "s@newdom0Size=${olddom0Size}@newdom0Size=${newdom0Size}@g" "$SubmissionFile"
	sed -i "s@#$ -t 10-100:5@#$ -t ${minVoltage}-${maxVoltage}:${VoltageStep}@g" "$SubmissionFile"

	qsub $SubmissionFile
	
	cd ..
done
