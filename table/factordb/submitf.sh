#!/bin/sh

msg=`cat hogea | awk '{n=$1;b=$2;f="%%2D";if(n%2==0){f="%%2B";n/=2}for(i=3;i<=NF;i++){match($i,/[0-9]+/);p=substr($i,RSTART,RLENGTH);printf b"%%5E"n""f"1%%3D"p"%%0A"}}'`

msg='report='$msg'&format=7'

len=`echo $msg | wc -c`
body=`cat <<EONU
POST /report.php HTTP/1.1
Host: factordb.com
Content-Type: application/x-www-form-urlencoded
Content-Length: $len

$msg
EONU`

echo "$body" | nc factordb.com 80

