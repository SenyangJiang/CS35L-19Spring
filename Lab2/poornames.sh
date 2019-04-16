#!/bin/sh

path=`pwd`
if [ ! -z "$1" ]
then
    path="$1"
fi

pathcheck=`echo "$path" | grep -E '^[^-]'`
if [ ! -z "$2" ]
then
    echo 'ERROR: too many arguments' 1>&2
    exit 1
elif [ -z "$pathcheck" ]
then
    echo "ERROR: argument cannot start with '-'" 1>&2
    exit 1
elif [ ! -d "$path" ]
then
    echo 'ERROR: not a directory' 1>&2
    exit 1
fi

lastcomp=`echo "$path" | grep -E '/[[:alpha:]_]{1}[[:alpha:]._-]{,13}$'`
if [ -z "$lastcomp" ]
then
    echo "$path"
    exit 0
fi

findpoor()
{
    dupl=`ls "$1" | grep -E '^[[:alpha:]_]{1}[[:alpha:]._-]{,13}$' |
 tr '[:upper:]' '[:lower:]' | sort | uniq -d`
    for s in $dupl
    do
        echo "$1/$s"
    done
    ls "$1" | while read f
    do
	if [ "$f" = '.' -o "$f" = '..' ]
        then
            continue
        fi
	namecheck=`echo $f | grep -E '^[[:alpha:]_]{1}[[:alpha:]._-]{,13}$'`
	if [ -z $namecheck ]
	then
	    echo "$1/$f"
	elif [ -d "$1/$f" ]
        then
            findpoor "$1/$f"
	fi 
    done
}

findpoor $path
