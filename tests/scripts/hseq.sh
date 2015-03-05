#!/bin/bash

strlen() {
	T=$(echo "$WORD" | wc -m | sed 's/ //g')
    let STRL=$T-1;
}

if [ "$2" == "" -o "$1" == "--help" -o "$1" == "-h" ]; then
	echo "Usage : $0 <from> <to> [<step>]";
	exit 1;
fi;

let COUNT=$1;
if [ "$3" == "" ]; then
	INC=1;
else
	let INC=$3;
fi;

WORD=$2;
strlen;
let TGTLEN=$STRL-1;

while [ $COUNT -le $2 ]; do
	WORD=$COUNT;
	strlen;
	#for i in $(seq $STRL $TGTLEN); do echo -n "0"; done
	i=$STRL;
	while [ $i -le $TGTLEN ]; do
		echo -n "0";
		let i=$i+1;
	done;
 	echo "$COUNT";
	let COUNT=$COUNT+$INC;
done;
