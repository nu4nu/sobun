#!/bin/sh

while read line; do
  name=`echo "$line" | sed 's/^.\([[:digit:]]*\) \([[:digit:]]*\) .*/\1_\2/'`
  echo "# $line" > $name.data
  printf "N " >> $name.data
  echo "$line" | cn >> $name.data
done

