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
> $maxRngErrPlt
> $minInterVehGapPlt
> $minTimeToColPlt

# Output pdf file names
maxRngErrPdf="$plotsOutDir/""MaxRngErr_""r$reactT""u$updateT""t$tauT.pdf"
minInterVehGapPdf="$plotsOutDir/""MinInterVehGap_""r$reactT""u$updateT""t$tauT.pdf"
minTimeToColPdf="$plotsOutDir/""MinTimeToCol_""r$reactT""u$updateT""t$tauT.pdf"

# Log file names
maxRngErrLog="/home/rudhir/workspace/CarFollow_Git/Debug/maxRngErr.log"
minInterVehGapLog="/home/rudhir/workspace/CarFollow_Git/Debug/minInterVehGap.log"
minTimeToColLog="/home/rudhir/workspace/CarFollow_Git/Debug/minTimeToCol.log"
paramsLog="/home/rudhir/workspace/CarFollow_Git/Debug/params.log"

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
# Generate PDF
###############################################################################
echo "Generating Pdf $maxRngErrPdf"
gnuplot $maxRngErrPlt
echo "Generating Pdf $minInterVehGapPdf"
gnuplot $minInterVehGapPlt
echo "Generating Pdf $minTimeToColPdf"
gnuplot $minTimeToColPlt

# Return to the saved dir path
#cd $presentDir
echo
