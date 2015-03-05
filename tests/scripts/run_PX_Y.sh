#!/bin/bash

TMPFILE=/tmp/tmp.$$
RESFILE=/tmp/tmp_res.$$

if [ "$4" == "" ] ; then
    echo "Usage : $0 <0|1|2|3|4|5|6> <id> <compiler> <gpmachine>";
    exit 1;
fi;

SERIE=$(echo "$1");
TID=$(echo "$2");
COMPILER=$3;
GPM=$4;

IFN=../P$SERIE/$TID/test.in;
OFN=../P$SERIE/$TID/test.out;
PFN=../P$SERIE/$TID/test.code;

    if [ -e $OFN ] && [ -e $PFN ]; then
	rm -f $TMPFILE $RESFILE;
	$COMPILER < $PFN > $TMPFILE 2> $RESFILE ;
	RETVAL=$?;
	RES=$(head -n 1 $RESFILE);

	if [ $RETVAL == 0 ] && [ "$RES" == "OK" ]; then
	    if [ -e $IFN ]; then
		java -jar $GPM -nogui -n  $TMPFILE < $IFN 
	    else
		java -jar $GPM -nogui -n  $TMPFILE 
	    fi;
	else
	    echo "TEST FAILED ! CANNOT COMPILE TEST (RES=$RES, CMP=$CMP)";
	    cat $RESFILE;
	    cat $TMPFILE;
	fi;
    fi;

rm -f $TMPFILE $RESFILE;
