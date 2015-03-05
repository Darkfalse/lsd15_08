#!/bin/bash

MAX=40
TMPFILE=/tmp/tmp.$$
RESFILE=/tmp/tmp_res.$$
scriptDir=$(dirname $0);

if [ "$3" == "" ] ; then
    echo "Usage : $0 <0|1|2|3|4|5|6> <compiler> <gpmachine>";
    exit 1;
fi;

SERIE=$(echo "$1");
COMPILER=$2;
GPM=$3;

for i in $(ls -1 $scriptDir/../P$SERIE/*.input); do
    IFN=$i;
    OFN=$(echo "$i" | sed 's/\.input$/\.output/g');
    PFN=$(echo "$i" | sed 's/\.input$/\.code/g');

    if [ -e $OFN ] && [ -e $PFN ]; then
	echo "Running test P$SERIE-$i...";
	rm -f $TMPFILE $RESFILE;
	$COMPILER < $PFN > $TMPFILE 2> $RESFILE ;
	RETVAL=$?;
	RES=$(head -n 1 $RESFILE);
	echo "RETVAL=$RETVAL  RES='$RES'";

	if [ $RETVAL == 0 ] && [ "$RES" == "OK" ]; then
	    if [ -e $IFN ]; then
		java -jar $GPM -nogui -n  $TMPFILE < $IFN > $RESFILE;
	    else
		java -jar $GPM -nogui -n  $TMPFILE > $RESFILE;
	    fi;
	    if [ "$(diff $RESFILE $OFN)" == "" ]; then
		echo "Test passed !";
	    else
		echo "Test FAILED !";
		echo "FOUND : ";
		cat $RESFILE
		echo "SHOULD HAVE BEEN :"
		cat $OFN;
	    fi;
	else
	    echo "TEST FAILED ! CANNOT COMPILE TEST (RES=$RES, CMP=$CMP)";
	    cat $RESFILE;
	    cat $TMPFILE;
	fi;
	echo "";
    fi;
done;

rm -f $TMPFILE $RESFILE;
