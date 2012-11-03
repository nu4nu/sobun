#!/bin/sh

msieve="msieve"
name=$1
start=$2
end=$3

if [ "$end" = "" ]; then
  echo "Usage: $0 basename start end"
  exit
fi

if [ ! -f $name.data ]; then
  echo $name.data does not exist
  exit
fi

n=`sed -ne '/^N/s/N //p' $name.data`

if [ "$n" = "" ]; then
  echo invalid input file
  exit
fi

if [ $start -le 0 ]; then
  start=1
fi

$msieve -l $name.log -s $name.dat -nf $name.fb -np $start,$end $n >/dev/null

if [ $? != 0 ]; then
  echo msieve error
  exit
fi

sed -e '/^N/d' $name.data
echo n: $n
sed -ne '
/R/{
  s/.*R/Y/
  s/  */ /
  x
  /^$/!H
}
/A/{
  s/.*A/c/
  s/  */ /
  x
  /^$/!H
}
/skew/{
  s/.*skew \([0-9\.]*\),\(.*\)/skew: \1\
#\2/
  s/size/norm/
  H
}
/elapsed/{
  s/.*elapsed/# polsel/
  x
  G
  p
}
' $name.log
cat <<EONU
rlim: 
alim: 
lpbr: 27
lpba: 27
mfbr: 52
mfba: 52
rlambda: 2.6
alambda: 2.6
q0: 
qintsize: 10000
EONU

