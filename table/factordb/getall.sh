#!/bin/sh

pow=$1

for n in `seq 2 111 1000`; do
  sh get.sh $pow $n 111
done

