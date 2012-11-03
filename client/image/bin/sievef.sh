#!/bin/sh

cd `dirname $0`
dir=`pwd`
cd - >/dev/null

name=$1
if [ "$name" = "" ]; then
  echo Usage: $0 name [ bits limit ]
  exit
fi
if [ ! -f $name.poly ]; then
  echo $name.poly does not exist
  exit
fi

np=`$dir/ncpu.sh`

side=`sed -ne '/c[56]/p' $name.poly`
if [ "$side" != "" ]; then
  side=a
else
  side=r
fi
qlim=`sed -ne 's/'$side'lim: \([0-9]*\)..../\1/p' "$name.poly"`
start=`expr $qlim - 1`
end=1
step=-1

bits=12
if [ "$2" != "" ]; then
  bits=$2
fi
if [ ! -f $dir'/gnfs-lasieve4I'$bits'e' ]; then
  echo siever $dir'/gnfs-lasieve4I'$bits'e' does not exist
  exit
fi
limit=12400000
if [ "$3" != "" ]; then
  limit=$3
  if echo $limit | grep -q -- -; then
    start=`echo $limit | cut -d- -f1`
    end=`echo $limit | cut -d- -f2`
    if [ $start -gt $end ]; then
      start=`expr $start - 1 2>/dev/null`
    else
      end=`expr $end - 1 2>/dev/null`
      step=
    fi
    limit=999999999
  fi
fi

if [ "$4" != "" ]; then
  limit=$4
fi

for n in `seq $start $step $end`; do echo sh $dir/gglpf.sh $name $side $bits $n $limit; done | parallel $np

