#!/bin/bash

if [ "$2" == "" ] ; then
    echo "Usage : $0  <compiler path> <L series count>";
    exit 1;
fi;

scriptDir=$(dirname $0);

for i in $($scriptDir/hseq.sh 0 $2); do 
    $scriptDir/run_LX.sh $i $1; 
done
