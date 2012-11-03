#!/bin/sh

name=$1
spqside=$2
bits=$3
qnum=$4
limit=$5

if [ "x$limit" = x ]; then
  echo Usage: $0 name spqside bits qnum limit
  exit
fi

if [ ! -d $name ]; then
  mkdir $name
fi

if [ -f $name/total ]; then
  total=`cat $name/total`
  if [ $total -gt $limit ]; then
    exit
  fi
fi

siever='gnfs-lasieve4I'$bits'e'
poly="$name.poly"
tmpjob="t$name.$$"

qlim=`sed -ne 's/'$spqside'lim: \([0-9]*\)..../\1/p' "$poly"`

if [ $qnum -lt $qlim ]; then
  sed -e 's/'$spqside'lim.*/'$spqside'lim: '$qnum'0000/;s/q0.*/q0: '$qnum'0000/' "$poly" >"$tmpjob"
else
  sed -e 's/q0.*/q0: '$qnum'0000/' "$poly" >"$tmpjob"
fi

$siever -o $name/s$qnum -$spqside "$tmpjob"

elapse=`stat -c '%X %Y' $name/s$qnum | awk '{print$2-$1}'`
rels=`wc -l $name/s$qnum | awk '{print$1}'`

while ! mkdir $name.lock 2>/dev/null; do sleep 0.1; done

if [ -f $name/total ]; then
  total=`cat $name/total`
  total=`expr $total + $rels`
else
  total=$rels
fi
echo $total >$name/total2
mv $name/total2 $name/total

echo $bits $qnum $elapse >>$name/time

sync

rmdir $name.lock

rm "$tmpjob"

