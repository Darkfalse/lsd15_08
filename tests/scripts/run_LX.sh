#!/bin/bash

TMPFILE=/tmp/tmp.$$
RESFILE=/tmp/tmp_res.$$

scriptDir=$(dirname $0);

if [ "$2" == "" ] ; then
    echo "Usage : $0 <0|1|2|3|4|5|6> <compiler>";
    exit 1;
fi;

SERIE=$(echo "$1");
COMPILER=$2;

for i in $(ls -1 $scriptDir/../L$SERIE/*.input); do
    IFN=$i;
    OFN=$(echo "$i" | sed 's/\.input$/\.output/g');
    if [ -e $IFN ] && [ -e $OFN ]; then
	echo "Running test L$SERIE-$i...";
	rm -f $TMPFILE $RESFILE;
	$COMPILER < $IFN > $TMPFILE 2> $RESFILE ;
	RETVAL=$?;
	RES=$(head -n 1 $RESFILE);
	if [ $RETVAL == 0 ]; then
	    CMP=$(head -n 1 $OFN);
	    if [ "$RES" == "$CMP" ]; then
		echo "Test passed ! (RES=$RES, CMP=$CMP)";
	    else
		echo "TEST FAILED ! (RES=$RES, CMP=$CMP)";
		cat $RESFILE;
		cat $TMPFILE;
	    fi;
	else
	    echo "ERROR : compiler CRASHED ($RETVAL)";
	fi;
	echo "";
    fi;
done;

rm -f $TMPFILE $RESFILE;
