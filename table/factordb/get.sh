#!/bin/sh

pow=$1
if [ `expr $pow % 2` = 0 ]; then
  pow=`expr $pow / 2`
  flag=2B1
else
  flag=2D1
fi
start=$2
num=$3

printf "GET /index.php?query=b^$pow%%$flag&use=b&perpage=$num&format=3&PR=1&PRP=1&C=1&CF=1&U=1&VP=1&EV=1&OD=1&VC=1&FF=1&b=$start HTTP/1.1\r\nHost: factordb.com\r\n\r\n" | nc factordb.com 80 | sed -ne '/^[1-9].* /p'

