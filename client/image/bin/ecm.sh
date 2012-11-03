#!/bin/sh

B1=$1
c=$2
file=$3
ix=$4

l=`sed -e $ix'!d;/C/!d' $file`

if [ "$l" = "" ]; then
  exit
fi

name=`echo $l | sed -e 's/^.\([^ ]*\) .*/\1/'`

if [ ! -d $name ]; then
  mkdir $name
fi

echo $l | ecm -cn -c $c $B1 >>$name/$ix

