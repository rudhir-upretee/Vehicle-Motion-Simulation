#!/bin/bash

# Command line arguments
numVehicles=$1
vehSampleInt=$2
reactT=$3
updateT=$4
tauT=$5
echo "Arg: ${numVehicles} ${vehSampleInt} ${reactT} ${updateT} ${tauT}"
numVehicles=$((numVehicles/vehSampleInt))

# Save the present Dir path
presentDir=`pwd`
plotsOutDir="/home/rudhir/Research/CarFollow/plots"
plotScriptDir="/home/rudhir/Research/CarFollow/src/plotscript"
cd $plotScriptDir

# Output script file names
velTimePlt="$plotsOutDir/""VelTimeScript_""r$reactT""u$updateT""t$tauT.plt"
hdwayTimePlt="$plotsOutDir/""HdwayTimeScript_""r$reactT""u$updateT""t$tauT.plt"
distTimePlt="$plotsOutDir/""DistTimeScript_""r$reactT""u$updateT""t$tauT.plt"
rangeErrTimePlt="$plotsOutDir/""RangeErrTimeScript_""r$reactT""u$updateT""t$tauT.plt"
> $velTimePlt
> $hdwayTimePlt
> $distTimePlt
> $rangeErrTimePlt

# Output pdf file names
velTimePdf="$plotsOutDir/""VelTime_""r$reactT""u$updateT""t$tauT.pdf"
hdwayTimePdf="$plotsOutDir/""HdwayTimePdf_""r$reactT""u$updateT""t$tauT.pdf"
distTimePdf="$plotsOutDir/""DistTime_""r$reactT""u$updateT""t$tauT.pdf"
rangeErrTimePdf="$plotsOutDir/""RangeErrTime_""r$reactT""u$updateT""t$tauT.pdf"

# Log file names
velTimeLog="/home/rudhir/workspace/CarFollow_Git/Debug/velTime.log" 
distTimeLog="/home/rudhir/workspace/CarFollow_Git/Debug/distTime.log"
paramsLog="/home/rudhir/workspace/CarFollow_Git/Debug/params.log"
rangeErrTimeLog="/home/rudhir/workspace/CarFollow_Git/Debug/rangeErrTime.log"
tmpLog="/home/rudhir/workspace/CarFollow_Git/Debug/temp.log"
> $tmpLog

# Capture simulation params
simParams="`cat $paramsLog`"

###############################################################################
## Generate GNUPlot script for VelTime.pdf
###############################################################################
echo "Generating script $velTimePlt"
echo "set terminal pdf" >> $velTimePlt
echo "set output '$velTimePdf'" >> $velTimePlt
echo "set title 'Velocity Profile'" >> $velTimePlt
echo "set grid" >> $velTimePlt
echo "set mxtics" >> $velTimePlt
#echo "set xtics font \"Times-Roman, 4\"" >> $velTimePlt
#echo "set ytics font \"Times-Roman, 4\"" >> $velTimePlt
#echo "set xtics 10" >> $velTimePlt
echo "set xlabel 'Time (seconds)'" >> $velTimePlt
echo "set ylabel 'Velocity (meters/sec)'" >> $velTimePlt
echo "set label \"$simParams\" at 1.5,38.0 tc rgb \"black\" font \",4\" front" >> $velTimePlt
#echo "set yrange [-10:80]" >> $velTimePlt
echo "unset key" >> $velTimePlt
firstLine="plot "
for (( i=0; i<numVehicles-1; i++ ))
do
	echo "$firstLine'-'  with lines,\\" >> $velTimePlt
	firstLine=""
done
echo "'-'  with lines" >> $velTimePlt

for (( i=1; i<=numVehicles; i++ ))
do
	echo >> $velTimePlt
	./GroupVehicle.awk lineStart=$i vehCnt=$numVehicles $velTimeLog > $tmpLog 
	awk 'BEGIN{FS=":"}{print $1,$2}' $tmpLog >> $velTimePlt
	echo "e" >> $velTimePlt
done

###############################################################################
## Generate GNUPlot script for HdwayTime.pdf
###############################################################################
echo "Generating script $hdwayTimePlt"
echo "set terminal pdf" >> $hdwayTimePlt
echo "set output '$hdwayTimePdf'" >> $hdwayTimePlt
echo "set title 'Headway Time Profile'" >> $hdwayTimePlt
echo "set grid" >> $hdwayTimePlt
echo "set mxtics" >> $hdwayTimePlt
#echo "set xtics font \"Times-Roman, 4\"" >> $hdwayTimePlt
#echo "set ytics font \"Times-Roman, 4\"" >> $hdwayTimePlt
#echo "set xtics 10" >> $hdwayTimePlt
echo "set xlabel 'Time (seconds)'" >> $hdwayTimePlt
echo "set ylabel 'Head Way Time (seconds)'" >> $hdwayTimePlt
echo "set label \"$simParams\" at 1.5,38.0 tc rgb \"black\" font \",4\" front" >> $hdwayTimePlt
#echo "set yrange [-10:80]" >> $hdwayTimePlt
echo "unset key" >> $hdwayTimePlt
firstLine="plot "
for (( i=0; i<numVehicles-1; i++ ))
do
	echo "$firstLine'-'  with lines,\\" >> $hdwayTimePlt
	firstLine=""
done
echo "'-'  with lines" >> $hdwayTimePlt

for (( i=1; i<=numVehicles; i++ ))
do
	echo >> $hdwayTimePlt
	./GroupVehicle.awk lineStart=$i vehCnt=$numVehicles $velTimeLog > $tmpLog 
	awk 'BEGIN{FS=":"}{print $1,$5}' $tmpLog >> $hdwayTimePlt
	echo "e" >> $hdwayTimePlt
done

###############################################################################
## Generate GNUPlot script for DistTime.pdf
###############################################################################
echo "Generating script $distTimePlt"
echo "set terminal pdf" >> $distTimePlt
echo "set output '$distTimePdf'" >> $distTimePlt
echo "set title 'Inter Vehicular Gap Profile'" >> $distTimePlt
echo "set grid" >> $distTimePlt
echo "set mxtics" >> $distTimePlt
#echo "set xtics font \"Times-Roman, 4\"" >> $distTimePlt
#echo "set ytics font \"Times-Roman, 4\"" >> $distTimePlt
#echo "set xtics 10" >> $distTimePlt
echo "set xlabel 'Time (seconds)'" >> $distTimePlt
echo "set ylabel 'Inter Vehicular Gap (meters)'" >> $distTimePlt
echo "set label \"$simParams\" at 1.5,48.0 tc rgb \"black\" font \",4\" front" >> $distTimePlt
#echo "set yrange [-10:80]" >> $distTimePlt
echo "unset key" >> $distTimePlt
firstLine="plot "
if (( vehSampleInt>1 )) 
then
	for (( i=0; i<numVehicles-1; i++ ))
	do
		echo "$firstLine'-'  with lines,\\" >> $distTimePlt
		firstLine=""
	done
	echo "'-'  with lines" >> $distTimePlt

	for (( i=1; i<=numVehicles; i++ ))
	do
		echo >> $distTimePlt
		./GroupVehicle.awk lineStart=$i vehCnt=$numVehicles $distTimeLog > $tmpLog
		awk 'BEGIN{FS=":"}{print $1,$2}' $tmpLog >> $distTimePlt
		echo "e" >> $distTimePlt
	done
else
	for (( i=0; i<numVehicles-2; i++ ))
	do
		echo "$firstLine'-'  with lines,\\" >> $distTimePlt
		firstLine=""
	done
	echo "'-'  with lines" >> $distTimePlt

	for (( i=1; i<=numVehicles-1; i++ ))
	do
		echo >> $distTimePlt
		./GroupVehicle.awk lineStart=$i vehCnt=$((numVehicles-1)) $distTimeLog > $tmpLog
                awk 'BEGIN{FS=":"}{print $1,$2}' $tmpLog >> $distTimePlt
		echo "e" >> $distTimePlt
	done
fi

###############################################################################
# Generate GNUPlot script for RangeErrTime.pdf
###############################################################################
echo "Generating script $rangeErrTimePlt"
echo "set terminal pdf" >> $rangeErrTimePlt
echo "set output '$rangeErrTimePdf'" >> $rangeErrTimePlt
echo "set title 'Range Error Profile'" >> $rangeErrTimePlt
echo "set grid" >> $rangeErrTimePlt
echo "set mxtics" >> $rangeErrTimePlt
#echo "set xtics font \"Times-Roman, 4\"" >> $rangeErrTimePlt
#echo "set ytics font \"Times-Roman, 4\"" >> $rangeErrTimePlt
#echo "set xtics 10" >> $rangeErrTimePlt
echo "set xlabel 'Time (seconds)'" >> $rangeErrTimePlt
echo "set ylabel 'Range Error (meters)'" >> $rangeErrTimePlt
echo "set label \"$simParams\" at graph 0.03, graph 0.03 tc rgb \"black\" font \",4\" front" >> $rangeErrTimePlt
#echo "set yrange [0:10]" >> $rangeErrTimePlt
echo "unset key" >> $rangeErrTimePlt
firstLine="plot "
if (( vehSampleInt>1 )) 
then
	for (( i=0; i<numVehicles-1; i++ ))
	do
		echo "$firstLine'-'  with lines,\\" >> $rangeErrTimePlt
		firstLine=""
	done
	echo "'-'  with lines" >> $rangeErrTimePlt

	for (( i=1; i<=numVehicles; i++ ))
	do
		echo >> $rangeErrTimePlt
		./GroupVehicle.awk lineStart=$i vehCnt=$numVehicles $rangeErrTimeLog > $tmpLog 
		awk 'BEGIN{FS=":"}{print $1,$2}' $tmpLog >> $rangeErrTimePlt
		echo "e" >> $rangeErrTimePlt
	done
else
	for (( i=0; i<numVehicles-2; i++ ))
	do
		echo "$firstLine'-'  with lines,\\" >> $rangeErrTimePlt
		firstLine=""
	done
	echo "'-'  with lines" >> $rangeErrTimePlt

	for (( i=1; i<=numVehicles-1; i++ ))
	do
		echo >> $rangeErrTimePlt
		./GroupVehicle.awk lineStart=$i vehCnt=$((numVehicles-1)) $rangeErrTimeLog > $tmpLog
                awk 'BEGIN{FS=":"}{print $1,$2}' $tmpLog >> $rangeErrTimePlt
		echo "e" >> $rangeErrTimePlt
	done
fi

###############################################################################
# Generate PDF
###############################################################################
echo "Generating Pdf $velTimePdf"
gnuplot $velTimePlt
echo "Generating Pdf $hdwayTimePdf"
gnuplot $hdwayTimePlt
echo "Generating Pdf $distTimePdf"
gnuplot $distTimePlt
echo "Generating Pdf $rangeErrTimePdf"
gnuplot $rangeErrTimePlt

# Return to the saved dir path
#cd $presentDir
echo
