#!/bin/sh

cd `dirname $0`
dir=`pwd`
cd - >/dev/null
ncpu=`$dir/ncpu.sh`
msieve=msieve;

poly=$1
name=`echo $poly | sed -e 's/\.poly//'`
poly=$name.poly
dat=$name.dat
ini=$name.ini
fb=$name.fb
log=$name.log
cmt=$name.cmt
time=time

if [ ! -f "$poly" ]; then
  echo $poly doesn\'t exist!!
  exit 1
fi

if [ ! -f "$name.cyc" ]; then
  sed -ne 's/^n: \([0-9]*\)/\1/p' "$poly" >$ini
  sed -ne 's/^n: \([0-9]*\)/N \1/p' "$poly" >$dat
  sed -ne 's/^n: \([0-9]*\)/N \1/p; s/^skew: \([0-9\.]*\)/SKEW \1/p' "$poly" >$fb
  sed -ne 's/^m: \([0-9]*\)/R1 1\nR0 -\1/p' "$poly" >>$fb
  sed -ne 's/^Y\([0-9]\): \([0-9-]*\)/R\1 \2/p' "$poly" >>$fb
  sed -ne 's/^c\([0-9]\): \([0-9-]*\)/A\1 \2/p' "$poly" >>$fb
  sed -ne 's/^rlim: \([0-9]*\)/FRMAX \1/p' "$poly" >>$fb
  sed -ne 's/^alim: \([0-9]*\)/FAMAX \1/p' "$poly" >>$fb
  awk 'BEGIN{print "SRLPMAX " 2**'`sed -ne 's/^lpbr: \([0-9]*\)/\1/p' "$poly"`'}' >>$fb
  awk 'BEGIN{print "SALPMAX " 2**'`sed -ne 's/^lpba: \([0-9]*\)/\1/p' "$poly"`'}' >>$fb

  cat s* >>$name

  $msieve -s $name -l $log -i $ini -nf $fb -t $ncpu -nc1
  if [ ! -f "$name.cyc" ]; then
    echo more rels needed!!
    exit 1
  fi
fi

if [ ! -f "$name.dep" ]; then
  $msieve -s $name -l $log -i $ini -nf $fb -t $ncpu -nc2
  if [ ! -f "$name.dep" ]; then
    echo lanczos failed!!
    exit 1
  fi
fi

$msieve -s $name -l $log -i $ini -nf $fb -t $ncpu -nc3

if [ -f "$cmt" ]; then
  echo $cmt already exists!!
  exit 1
fi

if [ ! -f "$log" ]; then
  echo $log doesn\'t exist!!
  exit 1
fi

if [ -f $time ]; then
  exec awk -f $dir/mkcmt.awk $log $poly $time $ncpu >$cmt
fi

