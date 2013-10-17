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
maxRngErrPlt="$plotsOutDir/""MaxRngErrScript_""r$reactT""u$updateT""t$tauT.plt"
minInterVehGapPlt="$plotsOutDir/""MinInterVehGapScript_""r$reactT""u$updateT""t$tauT.plt"
minTimeToColPlt="$plotsOutDir/""MinTimeToColScript_""r$reactT""u$updateT""t$tauT.plt"
rangeErrTwoNormPlt="$plotsOutDir/""RangeErrTwoNormScript_""r$reactT""u$updateT""t$tauT.plt"
rateErrTwoNormPlt="$plotsOutDir/""RateErrTwoNormScript_""r$reactT""u$updateT""t$tauT.plt"
> $maxRngErrPlt
> $minInterVehGapPlt
> $minTimeToColPlt
> $rangeErrTwoNormPlt
> $rateErrTwoNormPlt

# Output pdf file names
maxRngErrPdf="$plotsOutDir/""MaxRngErr_""r$reactT""u$updateT""t$tauT.pdf"
minInterVehGapPdf="$plotsOutDir/""MinInterVehGap_""r$reactT""u$updateT""t$tauT.pdf"
minTimeToColPdf="$plotsOutDir/""MinTimeToCol_""r$reactT""u$updateT""t$tauT.pdf"
rangeErrTwoNormPdf="$plotsOutDir/""RangeErrTwoNorm_""r$reactT""u$updateT""t$tauT.pdf"
rateErrTwoNormPdf="$plotsOutDir/""RateErrTwoNorm_""r$reactT""u$updateT""t$tauT.pdf"

# Log file names
maxRngErrLog="/home/rudhir/workspace/CarFollow_Git/Debug/maxRngErr.log"
minInterVehGapLog="/home/rudhir/workspace/CarFollow_Git/Debug/minInterVehGap.log"
minTimeToColLog="/home/rudhir/workspace/CarFollow_Git/Debug/minTimeToCol.log"
paramsLog="/home/rudhir/workspace/CarFollow_Git/Debug/params.log"
rangeErrTimeLog="/home/rudhir/workspace/CarFollow_Git/Debug/rangeErrTime.log"
tmpLog="/home/rudhir/workspace/CarFollow_Git/Debug/temp.log"
> $tmpLog

# Capture simulation params
simParams="`cat $paramsLog`"

###############################################################################
## Generate GNUPlot script for MaxRngErr.pdf
###############################################################################
echo "Generating script $maxRngErrPlt"
echo "set terminal pdf" >> $maxRngErrPlt
echo "set output '$maxRngErrPdf'" >> $maxRngErrPlt
echo "set title 'Max Range Error'" >> $maxRngErrPlt
echo "set grid" >> $maxRngErrPlt
#echo "set xtics font \"Times-Roman, 4\"" >> $maxRngErrPlt
#echo "set ytics font \"Times-Roman, 4\"" >> $maxRngErrPlt
#echo "set xtics 10" >> $maxRngErrPlt
echo "set xlabel 'Vehicle Pairs'" >> $maxRngErrPlt
echo "set ylabel 'Max Range Error (meters)'" >> $maxRngErrPlt
echo "set label \"$simParams\" at 1.5,48.0 tc rgb \"black\" font \",4\" front" >> $maxRngErrPlt
#echo "set yrange [0:100]" >> $maxRngErrPlt
echo "unset key" >> $maxRngErrPlt
echo "plot '-'  with linespoints" >> $maxRngErrPlt
echo >> $maxRngErrPlt
cat $maxRngErrLog >> $maxRngErrPlt
echo "e" >> $maxRngErrPlt

###############################################################################
## Generate GNUPlot script for MinInterVehGap.pdf
###############################################################################
echo "Generating script $minInterVehGapPlt"
echo "set terminal pdf" >> $minInterVehGapPlt
echo "set output '$minInterVehGapPdf'" >> $minInterVehGapPlt
echo "set title 'Min Inter Vehicle Gap'" >> $minInterVehGapPlt
echo "set grid" >> $minInterVehGapPlt
#echo "set xtics font \"Times-Roman, 4\"" >> $minInterVehGapPlt
#echo "set ytics font \"Times-Roman, 4\"" >> $minInterVehGapPlt
#echo "set xtics 10" >> $minInterVehGapPlt
echo "set xlabel 'Vehicle Pairs'" >> $minInterVehGapPlt
echo "set ylabel 'Min Inter Vehicle Gap (meters)'" >> $minInterVehGapPlt
echo "set label \"$simParams\" at 1.5,48.0 tc rgb \"black\" font \",4\" front" >> $minInterVehGapPlt
#echo "set yrange [0:100]" >> $minInterVehGapPlt
echo "unset key" >> $minInterVehGapPlt
echo "plot '-'  with linespoints" >> $minInterVehGapPlt
echo >> $minInterVehGapPlt 
cat $minInterVehGapLog >> $minInterVehGapPlt
echo "e" >> $minInterVehGapPlt

###############################################################################
## Generate GNUPlot script for MinTimeToCol.pdf
###############################################################################
echo "Generating script $minTimeToColPlt"
echo "set terminal pdf" >> $minTimeToColPlt
echo "set output '$minTimeToColPdf'" >> $minTimeToColPlt
echo "set title 'Min Time To Collide'" >> $minTimeToColPlt
echo "set grid" >> $minTimeToColPlt
#echo "set xtics font \"Times-Roman, 4\"" >> $minTimeToColPlt
#echo "set ytics font \"Times-Roman, 4\"" >> $minTimeToColPlt
#echo "set xtics 10" >> $minTimeToColPlt
echo "set xlabel 'Vehicle Pairs'" >> $minTimeToColPlt
echo "set ylabel 'Min Time To Collide (seconds)'" >> $minTimeToColPlt
echo "set label \"$simParams\" at 1.5,48.0 tc rgb \"black\" font \",4\" front" >> $minTimeToColPlt
#echo "set yrange [0:100]" >> $minTimeToColPlt
echo "unset key" >> $minTimeToColPlt
echo "plot '-'  with linespoints" >> $minTimeToColPlt
echo >> $minTimeToColPlt 
cat $minTimeToColLog >> $minTimeToColPlt
echo "e" >> $minTimeToColPlt

###############################################################################
# Generate GNUPlot script for rangeErrTwoNorm.pdf
###############################################################################
echo "Generating script $rangeErrTwoNormPlt"
echo "set terminal pdf" >> $rangeErrTwoNormPlt
echo "set output '$rangeErrTwoNormPdf'" >> $rangeErrTwoNormPlt
echo "set title 'Range Error'" >> $rangeErrTwoNormPlt
echo "set grid" >> $rangeErrTwoNormPlt
echo "set mxtics" >> $rangeErrTwoNormPlt
#echo "set xtics font \"Times-Roman, 4\"" >> $rangeErrTwoNormPlt
#echo "set ytics font \"Times-Roman, 4\"" >> $rangeErrTwoNormPlt
#echo "set xtics 10" >> $rangeErrTwoNormPlt
echo "set xlabel 'Time (seconds)'" >> $rangeErrTwoNormPlt
echo "set ylabel '2 Norm Range Error'" >> $rangeErrTwoNormPlt
echo "set label \"$simParams\" at graph 0.03, graph 0.03 tc rgb \"black\" font \",4\" front" >> $rangeErrTwoNormPlt
#echo "set yrange [0:10]" >> $rangeErrTwoNormPlt
echo "unset key" >> $rangeErrTwoNormPlt
firstLine="plot "
if (( vehSampleInt>1 )) 
then
        echo "plot '-'  with lines" >> $rangeErrTwoNormPlt
        echo >> $rangeErrTwoNormPlt
	for (( i=1; i<=numVehicles; i++ ))
	do
		./GroupVehicle.awk lineStart=$i vehCnt=$numVehicles $rangeErrTimeLog > $tmpLog 
                awk 'BEGIN{FS=":"}{print $2}' $tmpLog | ./Calc2norm.awk >> $rangeErrTwoNormPlt
	done		
        echo "e" >> $rangeErrTwoNormPlt

else
        echo "plot '-'  with lines" >> $rangeErrTwoNormPlt
        echo >> $rangeErrTwoNormPlt
	for (( i=1; i<=numVehicles-1; i++ ))
	do
		./GroupVehicle.awk lineStart=$i vehCnt=$((numVehicles-1)) $rangeErrTimeLog > $tmpLog
                awk 'BEGIN{FS=":"}{print $2}' $tmpLog | ./Calc2norm.awk >> $rangeErrTwoNormPlt
	done
        echo "e" >> $rangeErrTwoNormPlt
fi

###############################################################################
# Generate GNUPlot script for rateErrTwoNorm.pdf
###############################################################################
echo "Generating script $rateErrTwoNormPlt"
echo "set terminal pdf" >> $rateErrTwoNormPlt
echo "set output '$rateErrTwoNormPdf'" >> $rateErrTwoNormPlt
echo "set title 'Rate Error'" >> $rateErrTwoNormPlt
echo "set grid" >> $rateErrTwoNormPlt
echo "set mxtics" >> $rateErrTwoNormPlt
#echo "set xtics font \"Times-Roman, 4\"" >> $rateErrTwoNormPlt
#echo "set ytics font \"Times-Roman, 4\"" >> $rateErrTwoNormPlt
#echo "set xtics 10" >> $rateErrTwoNormPlt
echo "set xlabel 'Time (seconds)'" >> $rateErrTwoNormPlt
echo "set ylabel '2 Norm Rate Error'" >> $rateErrTwoNormPlt
echo "set label \"$simParams\" at graph 0.03, graph 0.03 tc rgb \"black\" font \",4\" front" >> $rateErrTwoNormPlt
#echo "set yrange [0:10]" >> $rateErrTwoNormPlt
echo "unset key" >> $rateErrTwoNormPlt
firstLine="plot "
if (( vehSampleInt>1 )) 
then
        echo "plot '-'  with lines" >> $rateErrTwoNormPlt
        echo >> $rateErrTwoNormPlt
	for (( i=1; i<=numVehicles; i++ ))
	do
		./GroupVehicle.awk lineStart=$i vehCnt=$numVehicles $rangeErrTimeLog > $tmpLog 
                awk 'BEGIN{FS=":"}{print $3}' $tmpLog | ./Calc2norm.awk >> $rateErrTwoNormPlt
	done		
        echo "e" >> $rateErrTwoNormPlt

else
        echo "plot '-'  with lines" >> $rateErrTwoNormPlt
        echo >> $rateErrTwoNormPlt
	for (( i=1; i<=numVehicles-1; i++ ))
	do
		./GroupVehicle.awk lineStart=$i vehCnt=$((numVehicles-1)) $rangeErrTimeLog > $tmpLog
                awk 'BEGIN{FS=":"}{print $3}' $tmpLog | ./Calc2norm.awk >> $rateErrTwoNormPlt
	done
        echo "e" >> $rateErrTwoNormPlt
fi

###############################################################################
# Generate PDF
###############################################################################
echo "Generating Pdf $maxRngErrPdf"
gnuplot $maxRngErrPlt
echo "Generating Pdf $minInterVehGapPdf"
gnuplot $minInterVehGapPlt
echo "Generating Pdf $minTimeToColPdf"
gnuplot $minTimeToColPlt
echo "Generating Pdf $rangeErrTwoNormPdf"
gnuplot $rangeErrTwoNormPlt
echo "Generating Pdf $rateErrTwoNormPdf"
gnuplot $rateErrTwoNormPlt

# Return to the saved dir path
#cd $presentDir
echo
