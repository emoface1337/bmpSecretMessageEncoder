#!/bin/bash

if [ "$1" = "build" ]
then
    make build
elif [ "$1" = "clean" ]
then
	make clean
elif [ "$1" = "test" ]
then
	if [ -n "$2" ] && [ -n "$3" ] && [ -n "$4" ] ;
	then
		bmp_in=$2
		bmp_out=$3
		secret_message=$4
		make test bmp_in=${bmp_in} bmp_out=${bmp_out} secretMsg=${secret_message}
		echo $bmp_in $bmp_out $secret_message
	else
		echo "if you wanna test then type './test.sh test bmp_in bmp_out secret message'" && exit 1;
	fi
else
	echo "if you wanna build then type './test.sh build'"
	echo "if you wanna clean then type './test.sh clean'"
	echo "if you wanna test then type './test.sh test bmp_in bmp_out secret message'" && exit 1;
fi