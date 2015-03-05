#!/bin/bash

if [ $3 == "" ] ; then
    echo "Usage : $0  <compiler path> <P series count> <gpmachine path>";
    exit 1;
fi;

scriptDir=$(dirname $0);

for i in $($scriptDir/hseq.sh 0 $2); do 
    $scriptDir/run_PX.sh $i $1 $3; 
done
