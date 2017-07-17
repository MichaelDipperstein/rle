#!/bin/bash

if [ -f foo ]
then
    echo this script requies use of a file foo
    exit 1
fi

if [ -f bar ]
then
    echo this script requies use of a file bar
    exit 1
fi

for X in *
do
    if [ -f "$X" ]
    then
        printf "checking %s\n" $X
        filesize=$(stat -c '%s' $X)
        printf "uncompressed size:\t%d\n" $filesize
        ./sample -c -i $X -o foo
        ./sample -d -i foo -o bar
        diff $X bar
        filesize=$(stat -c '%s' foo)
        printf "rle size:\t\t%d\n" $filesize
        ./sample -c -v -i $X -o foo
        ./sample -d -v -i foo -o bar
        diff $X bar
        filesize=$(stat -c '%s' foo)
        printf "vpackbits size:\t\t%d\n\n" $filesize
        rm foo
        rm bar
    fi
done

exit 0
