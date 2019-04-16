#!/bin/sh

path=`pwd`
if [ ! -z "$1" ]
then
    path="$1"
fi

pathcheck=`echo $path | grep -E '^[^-]'`
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

lastcomp=`echo $path | grep -E '/[A-za-z_]{1}[A-za-z._-]{,13}$'`
if [ -z "$lastcomp" ]
then
    echo "$path"
    exit 0
fi

findpoor()
{
    files=`ls $1`
    dupl=`ls $1 | grep -E '^[A-za-z_]{1}[A-za-z._-]{,13}$' |
 tr '[:upper:]' '[:lower:]' | sort | uniq -d`
    for s in $dupl
    do
        echo "$1/$s"
    done
    for f in $files
    do
	if [ $f = '.' -o $f = '..' ]
        then
            continue
        fi
	namecheck=`echo $f | grep -E '^[A-za-z_]{1}[A-za-z._-]{,13}$'`
	if [ -z $namecheck ]
	then
	    echo "$1/$f"
	fi
	if [ -d "$1/$f" ]
        then
            findpoor "$1/$f"
	fi 
    done
}

findpoor $path
